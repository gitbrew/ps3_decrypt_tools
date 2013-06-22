/*
* Copyright (c) 2011-2012 by ps3dev.net
* This file is released under the GPLv2.
*/

#include "types.h"
#include "keys.h"
#include "util.h"

u8 *eid_root_key = {0};

u8 syscon_key_seed[INDIV_SIZE] =
{
	0x63, 0xDC, 0xA7, 0xD3, 0xFE, 0xE4, 0x7F, 0x74, 0x9A, 0x40, 0x83, 0x63, 0xF1, 0x10, 0x4E, 0x8F,
	0x4D, 0x10, 0x09, 0x43, 0x24, 0x00, 0x9C, 0xC8, 0xE6, 0xB6, 0x9C, 0x70, 0x32, 0x8E, 0x34, 0xC5,
	0xD9, 0x79, 0x49, 0xBA, 0xD8, 0xDA, 0x69, 0xD0, 0xE0, 0x1B, 0xF3, 0x15, 0x23, 0x73, 0x28, 0x32,
	0xC9, 0xD1, 0xDD, 0x3C, 0xE2, 0x7E, 0x35, 0x66, 0x97, 0xE2, 0x6C, 0x12, 0xA7, 0xB3, 0x16, 0xA8,
	0x72, 0xFF, 0x4C, 0x7F, 0xD2, 0xA5, 0x90, 0x8D, 0x6C, 0x9C, 0x3F, 0xD3, 0xC0, 0x37, 0xFE, 0xEB,
	0xFA, 0x8D, 0x08, 0x3C, 0x05, 0x20, 0x80, 0xD4, 0xA1, 0x94, 0x53, 0x45, 0x2E, 0x17, 0x9A, 0x44,
	0x35, 0xF8, 0x42, 0x12, 0x95, 0xCB, 0xF4, 0x84, 0xE0, 0x6A, 0x17, 0xFA, 0x2F, 0xB9, 0x86, 0x86,
	0xC2, 0xF3, 0x68, 0x5E, 0x7E, 0xF4, 0x97, 0x68, 0x33, 0x7B, 0x79, 0xFD, 0xBC, 0x82, 0x65, 0xBE,
	0xC6, 0xE1, 0x93, 0x31, 0xFC, 0x6D, 0x75, 0xD1, 0xC2, 0x80, 0x09, 0x13, 0xD1, 0x79, 0x3C, 0x7E,
	0x77, 0x1A, 0x75, 0x5F, 0x40, 0x2D, 0x51, 0x96, 0xD0, 0x2A, 0x0D, 0x09, 0x2B, 0xEF, 0xE0, 0x1E,
	0xB1, 0x17, 0x01, 0x62, 0x9E, 0xD2, 0xFA, 0x91, 0x8F, 0x9F, 0x4D, 0x8B, 0x78, 0xD7, 0x2D, 0x74,
	0x19, 0x93, 0x0D, 0xE0, 0xB6, 0xFD, 0xCF, 0xFC, 0x7B, 0xA6, 0x30, 0xB8, 0x2D, 0x53, 0x04, 0x31,
	0x44, 0x20, 0xED, 0x72, 0x2F, 0xEA, 0x35, 0x02, 0x19, 0x55, 0xAB, 0x40, 0xC7, 0x8E, 0xE6, 0xDF,
	0x3E, 0x67, 0xC2, 0xD9, 0x43, 0x2E, 0x15, 0xD0, 0x9B, 0xEF, 0x0E, 0x6C, 0x64, 0x92, 0x45, 0x5D,
	0x5F, 0xA6, 0xAF, 0x2B, 0xB0, 0x7F, 0x72, 0xE2, 0xAB, 0xF8, 0x0B, 0x4E, 0xF6, 0xDA, 0x98, 0xE0,
	0x8C, 0xB7, 0x82, 0xE5, 0x3E, 0x8A, 0xEB, 0x8A, 0x76, 0x8D, 0x36, 0x65, 0x98, 0x28, 0x1B, 0x9B,
};

u8 common_indiv_seed[INDIV_SEED_SIZE] =
{
	0x59, 0x30, 0x21, 0x45, 0xAC, 0x09, 0xB1, 0xEF, 0xE6, 0x9E, 0x9B, 0x7A, 0x25, 0xFF, 0x8F, 0x86,
    	0xE9, 0xF6, 0x81, 0x4D, 0x37, 0xDE, 0x20, 0x4D, 0x29, 0x72, 0x9B, 0x84, 0x16, 0xBA, 0xED, 0xE4,
    	0x22, 0x70, 0x98, 0x65, 0x7F, 0x29, 0x8C, 0xDB, 0x6A, 0x9B, 0x5E, 0x59, 0xE4, 0xA4, 0xBA, 0x2F,
    	0x8E, 0x6A, 0x74, 0x0E, 0x1F, 0xC1, 0xE3, 0xE9, 0x35, 0xDD, 0xD2, 0xF6, 0x6C, 0xDE, 0xDD, 0x6B
};

u8 eid0_indiv_seed[INDIV_SEED_SIZE] =
{
	0xAB, 0xCA, 0xAD, 0x17, 0x71, 0xEF, 0xAB, 0xFC, 0x2B, 0x92, 0x12, 0x76, 0xFA, 0xC2, 0x13, 0x0C,
	0x37, 0xA6, 0xBE, 0x3F, 0xEF, 0x82, 0xC7, 0x9F, 0x3B, 0xA5, 0x73, 0x3F, 0xC3, 0x5A, 0x69, 0x0B,
	0x08, 0xB3, 0x58, 0xF9, 0x70, 0xFA, 0x16, 0xA3, 0xD2, 0xFF, 0xE2, 0x29, 0x9E, 0x84, 0x1E, 0xE4,
	0xD3, 0xDB, 0x0E, 0x0C, 0x9B, 0xAE, 0xB5, 0x1B, 0xC7, 0xDF, 0xF1, 0x04, 0x67, 0x47, 0x2F, 0x85
};

u8 eid1_indiv_seed[INDIV_SEED_SIZE] =
{
	0xB0, 0xD6, 0x55, 0x76, 0x4C, 0x3B, 0x44, 0xB3, 0x38, 0xF3, 0x2D, 0xD1, 0xD0, 0x99, 0x9B, 0x66,
    	0x48, 0xA3, 0x5A, 0x2C, 0xEB, 0x15, 0xE2, 0x8E, 0xEC, 0xDC, 0x2D, 0xC0, 0xB4, 0xC7, 0xEB, 0x05,
    	0xDC, 0x82, 0x25, 0xC0, 0xD5, 0x78, 0x9D, 0xBB, 0x2E, 0x89, 0xA2, 0x4A, 0x78, 0x58, 0x58, 0x00,
    	0x72, 0x36, 0x38, 0x34, 0xEE, 0x1A, 0x11, 0x6C, 0x2C, 0xD2, 0x5E, 0x58, 0xEE, 0x67, 0x63, 0xF7
};

u8 eid2_indiv_seed[INDIV_SEED_SIZE] =
{
	0x74, 0x92, 0xE5, 0x7C, 0x2C, 0x7C, 0x63, 0xF4, 0x49, 0x42, 0x26, 0x8F, 0xB4, 0x1C, 0x58, 0xED,
	0x66, 0x83, 0x41, 0xF9, 0xC9, 0x7B, 0x29, 0x83, 0x96, 0xFA, 0x9D, 0x82, 0x07, 0x51, 0x99, 0xD8,
	0xBC, 0x1A, 0x93, 0x4B, 0x37, 0x4F, 0xA3, 0x8D, 0x46, 0xAF, 0x94, 0xC7, 0xC3, 0x33, 0x73, 0xB3,
	0x09, 0x57, 0x20, 0x84, 0xFE, 0x2D, 0xE3, 0x44, 0x57, 0xE0, 0xF8, 0x52, 0x7A, 0x34, 0x75, 0x3D
};

u8 eid3_indiv_seed[INDIV_SEED_SIZE] =
{
    	0x01, 0xD0, 0x49, 0x6A, 0x3B, 0xAD, 0xD1, 0x73, 0x55, 0x70, 0xCB, 0x29, 0xE1, 0x6F, 0xA2, 0x31,
    	0x4F, 0xA9, 0xFD, 0x1A, 0xBA, 0x19, 0xA1, 0xC6, 0x9E, 0xEA, 0x2F, 0x4A, 0xA6, 0x07, 0xA7, 0x1C,
    	0x6F, 0xE2, 0x3E, 0xF8, 0xDF, 0xBB, 0x0F, 0x2D, 0x9D, 0x45, 0x2C, 0xD5, 0xFA, 0xD5, 0x8B, 0x74,
    	0x5B, 0xF8, 0xA4, 0xA5, 0x0D, 0x8B, 0xDB, 0x29, 0xB2, 0xF4, 0xBF, 0x14, 0xC4, 0x4A, 0xDD, 0x76
};

u8 eid4_indiv_seed[INDIV_SEED_SIZE] =
{
	0x3E, 0xC2, 0x0C, 0x17, 0x02, 0x19, 0x01, 0x97, 0x8A, 0x29, 0x71, 0x79, 0x38, 0x29, 0xD3, 0x08,
	0x04, 0x29, 0xFA, 0x84, 0xE3, 0x3E, 0x7F, 0x73, 0x0C, 0x1D, 0x41, 0x6E, 0xEA, 0x25, 0xCA, 0xFB,
	0x3D, 0xE0, 0x2B, 0xC0, 0x05, 0xEA, 0x49, 0x0B, 0x03, 0xE9, 0x91, 0x98, 0xF8, 0x3F, 0x10, 0x1F,
	0x1B, 0xA3, 0x4B, 0x50, 0x58, 0x94, 0x28, 0xAD, 0xD2, 0xB3, 0xEB, 0x3F, 0xF4, 0xC3, 0x1A, 0x58
};

u8 eid0_keyseed_0[EID0_KEYSEED_SIZE] =
{
	0x2E, 0xD7, 0xCE, 0x8D, 0x1D, 0x55, 0x45, 0x45, 0x85, 0xBF, 0x6A, 0x32, 0x81, 0xCD, 0x03, 0xAF
};

u8 eid0_keyseed_6[EID0_KEYSEED_SIZE] =
{
	0x3A, 0xB0, 0xE6, 0xC4, 0xAC, 0xFF, 0xB6, 0x29, 0x36, 0x2F, 0xFB, 0xBB, 0xDB, 0xC8, 0x54, 0xBC
};

u8 eid0_keyseed_A[EID0_KEYSEED_SIZE] =
{
	0x30, 0xB0, 0x39, 0x5D, 0xC5, 0x83, 0x5A, 0xAA, 0x3A, 0x79, 0x86, 0xB4, 0x4A, 0xFA, 0xE6, 0x84
};

u8 eid3_keyseed[EID3_KEYSEED_SIZE] = 
{
	0x5F, 0xFF, 0x3F, 0xD8, 0x1E, 0x18, 0xB9, 0x56, 0xDA, 0xE4, 0xE6, 0xD3, 0x36, 0x82, 0x97, 0xEF
};

u8 eid3_static_key[EID3_STATIC_KEY_SIZE] = 
{
	0xD9, 0x94, 0x06, 0xCA, 0x4B, 0xF3, 0x07, 0x50, 0x43, 0x6A, 0x45, 0x47, 0x36, 0x83, 0x45, 0x89
};

u8 eid2_des_key[EID2_DES_KEY_SIZE] = 
{
	0x6C, 0xCA, 0xB3, 0x54, 0x05, 0xFA, 0x56, 0x2C
};

u8 eid2_des_iv[EID2_DES_IV_SIZE] = 
{
	0x98, 0x9A, 0x95, 0x5E, 0xFD, 0xE7, 0xA7, 0x48
};