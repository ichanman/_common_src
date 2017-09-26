/*
 * bitNBytes.c
 *
 *  Created on: Apr 1, 2017
 *      Author: Lenovo
 */

#include "Data_bit_bytes.h"

c_byteArray c_bitToBytes(c_bitArray bitArray)
{
	c_byteArray res;
	res.size = (bitArray.size) / 8;
	int b;
	memset(res.bytes,0,res.size);
	for(b=0;b<bitArray.size;b++){
		res.bytes[b/8] = (res.bytes[b/8] | ((bitArray.bit[b]?1:0)<<(7-(b%8))));
	}
	return res;
}
c_bitArray c_bytesTobits(c_byteArray byteArray){
	int i,b;
	c_bitArray resbit;
	resbit.size = byteArray.size * 8;
	for(i=0;i<resbit.size;i++){
		//printf("%X\n",bytes[i]);
		for(b=0;b<8;b++){
			int res = 0;
			resbit.bit[(i*8) + b] = ((byteArray.bytes[i] & (1<<(7-b)))?TRUE:FALSE);
		}
	}
	return resbit;
}
