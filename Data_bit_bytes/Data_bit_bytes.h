/***********************  I n c l u d e  -  F i l e  ************************/
/*!
 *        \file  Data_bit_bytes.h
 *
 *      \author  Lenovo
 *
 *  	 \brief  Header file for MTCS demo application.
 *
 * (c) Copyright 2017 by PT. LRS, Bandung, Indonesia
 ****************************************************************************/
#ifndef DATA_BIT_BYTES_H_
#define DATA_BIT_BYTES_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_BYTES_ARRAY 200
#define MAX_BIT_ARRAY	MAX_BYTES_ARRAY * 8
#define TRUE  1U
#define FALSE 0U
typedef struct{
	unsigned char bytes[MAX_BYTES_ARRAY];
	uint16_t size;
}c_byteArray;

typedef struct{
	uint8_t bit[MAX_BIT_ARRAY];
	uint16_t size;
}c_bitArray;

c_byteArray c_bitToBytes(c_bitArray bitArray);
c_bitArray c_bytesTobits(c_byteArray byteArray);

#endif /* DATA_BIT_BYTES_H_ */
