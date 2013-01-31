/*
* Copyright (c) 2011-2012 by ps3dev.net
* This file is released under the GPLv2.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <polarssl/aes.h>

#include "util.h"
#include "keys.h"
#include "eid.h"
#include "hdd.h"
#include "kgen.h"
#include "types.h"
#include "indiv.h"

void decrypt_hdd()
{
    u8 ata_k1[0x20], ata_k2[0x20], edec_k1[0x20], edec_k2[0x20];
	u32 size;

	//Fetching eid_root_key
	u8 *eid_root_key = _read_buffer((s8*)"data/eid_root_key", NULL);
	//Assuming sectors start with sector 0.
	u8 *sectors = _read_buffer((s8*)"data/sectors", &size);

	//Generate keys.
	generate_ata_keys(eid_root_key, eid_root_key + 0x20, ata_k1, ata_k2);
	generate_encdec_keys(eid_root_key, eid_root_key + 0x20, edec_k1, edec_k2);

	_hexdump(stdout, "ATA-DATA-KEY    ", 0, ata_k1, 0x20, 0);
	_hexdump(stdout, "ATA-TWEAK-KEY   ", 0, ata_k2, 0x20, 0);
	_hexdump(stdout, "ENCDEC-DATA-KEY ", 0, edec_k1, 0x20, 0);
	_hexdump(stdout, "ENCDEC-TWEAK-KEY", 0, edec_k2, 0x20, 0);

	//Decrypt all sectors.
	decrypt_sectors(sectors, 0, size, ata_k1, ata_k2, 1);
	//Decrypt VFLASH sectors starting at sector 8.
	decrypt_sectors(sectors+8*SECTOR_SIZE, 8, size - 8*SECTOR_SIZE, edec_k1, edec_k2, 0);

	_write_buffer((s8*)"data/sectors_decrypted", sectors, size);

}

void decrypt_eid()
{
    	//decrypting eEID
	eid_unpack((s8*)"eid/eid");

	eid0_decrypt((s8*)"eid/eid0",(s8*)"eid/eid0decrypted");
	eid1_decrypt((s8*)"eid/eid1",(s8*)"eid/eid1decrypted");
	eid2_generate_block((s8*)"eid/eid2",EID2_BLOCKTYPE_P,(s8*)"eid/eid2pblock");
	eid2_generate_block((s8*)"eid/eid2",EID2_BLOCKTYPE_S,(s8*)"eid/eid2sblock");
	eid4_decrypt((s8*)"eid/eid4",(s8*)"eid/eid4decrypted");
}

void encrypt_hdd()
{
    	u8 ata_k1[0x20], ata_k2[0x20], edec_k1[0x20], edec_k2[0x20];
	u32 size;

	//Fetching eid_root_key
	u8 *eid_root_key = _read_buffer((s8*)"data/eid_root_key", NULL);
	//Assuming sectors start with sector 0.
	u8 *sectors = _read_buffer((s8*)"data/sectors_decrypted", &size);

	//Generate keys.
	generate_ata_keys(eid_root_key, eid_root_key + 0x20, ata_k1, ata_k2);
	generate_encdec_keys(eid_root_key, eid_root_key + 0x20, edec_k1, edec_k2);

	_hexdump(stdout, "ATA-DATA-KEY    ", 0, ata_k1, 0x20, 0);
	_hexdump(stdout, "ATA-TWEAK-KEY   ", 0, ata_k2, 0x20, 0);
	_hexdump(stdout, "ENCDEC-DATA-KEY ", 0, edec_k1, 0x20, 0);
	_hexdump(stdout, "ENCDEC-TWEAK-KEY", 0, edec_k2, 0x20, 0);
	
	//Encrypt all sectors.
	encrypt_sectors(sectors, 0, size, ata_k1, ata_k2, 1);

	//Encrypt VFLASH sectors starting at sector 8.
	encrypt_sectors(sectors+8*SECTOR_SIZE, 8, size - 8*SECTOR_SIZE, edec_k1, edec_k2, 0);

	_write_buffer((s8*)"data/sectors_encrypted", sectors, size);

}

void syscon_auth()
{
	_write_buffer((s8*)"syscon/syscon_key_seed", syscon_key_seed, INDIV_SIZE);
	aes_context aes_ctxt;
	u8 indiv[0x40];
	u8 indiv_key[0x20];
	u8 zero_iv[0x10]={0x0};
	u8 enc_key_seed[INDIV_SIZE];

	_write_buffer((s8*)"syscon/syscon_indiv_seed", eid1_indiv_seed, 0x40);
	//Generate individuals.
	indiv_gen(eid1_indiv_seed, NULL, NULL, NULL, indiv);
	_write_buffer((s8*)"syscon/indiv", indiv, 0x40);
	
	
	//Generate seeds
	memcpy(indiv_key,indiv + 0x20,0x20);
	aes_setkey_enc(&aes_ctxt, indiv_key, KEY_BITS(0x20));
	aes_crypt_cbc(&aes_ctxt, AES_ENCRYPT, INDIV_SIZE, zero_iv, syscon_key_seed, enc_key_seed);
	              	

	_write_buffer((s8*)"syscon/enc_key_seed", enc_key_seed, INDIV_SIZE);

}

void decrypt_all()
{
	u8 ata_k1[0x20], ata_k2[0x20], edec_k1[0x20], edec_k2[0x20];
	u32 size;

	//Fetching eid_root_key
	u8 *eid_root_key = _read_buffer((s8*)"data/eid_root_key", NULL);
	//Assuming sectors start with sector 0.
	u8 *sectors = _read_buffer((s8*)"data/sectors", &size);

	//Generate keys.
	generate_ata_keys(eid_root_key, eid_root_key + 0x20, ata_k1, ata_k2);
	generate_encdec_keys(eid_root_key, eid_root_key + 0x20, edec_k1, edec_k2);

	_hexdump(stdout, "ATA-DATA-KEY    ", 0, ata_k1, 0x20, 0);
	_hexdump(stdout, "ATA-TWEAK-KEY   ", 0, ata_k2, 0x20, 0);
	_hexdump(stdout, "ENCDEC-DATA-KEY ", 0, edec_k1, 0x20, 0);
	_hexdump(stdout, "ENCDEC-TWEAK-KEY", 0, edec_k2, 0x20, 0);

	//Decrypt all sectors.
	decrypt_sectors(sectors, 0, size, ata_k1, ata_k2, 1);
	//Decrypt VFLASH sectors starting at sector 8.
	decrypt_sectors(sectors+8*SECTOR_SIZE, 8, size - 8*SECTOR_SIZE, edec_k1, edec_k2, 0);

	_write_buffer((s8*)"data/sectors_decrypted", sectors, size);

	//decrypting eEID
	eid_unpack((s8*)"eid/eid");

	eid0_decrypt((s8*)"eid/eid0",(s8*)"eid/eid0decrypted");
	eid1_decrypt((s8*)"eid/eid1",(s8*)"eid/eid1decrypted");
	eid2_generate_block((s8*)"eid/eid2",EID2_BLOCKTYPE_P,(s8*)"eid/eid2pblock");
	eid2_generate_block((s8*)"eid/eid2",EID2_BLOCKTYPE_S,(s8*)"eid/eid2sblock");
	eid4_decrypt((s8*)"eid/eid4",(s8*)"eid/eid4decrypted");
}

int main()
{
    int i;
    printf("Select an option\n1-Decrypt HDD\n2-Decrypt eEID(0,1,2,4 ONLY)\n3-Decrypt ALL\n4-Encrypt HDD\n5-Generate Syscon AUTH seeds(WARNING! DANGEROUS!)\n0-Exit\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1:
            decrypt_hdd();
            break;
        case 2:
            decrypt_eid();
            break;
        case 3:
            decrypt_all();
	    break;
        case 4:
	    encrypt_hdd();
	    break;
	case 5:
	    syscon_auth();
	    break;
	case 0:
            break;
        default:
            printf("Incorrect Option Selected! Try Again.");
            break;
    }
    return 0;
}
