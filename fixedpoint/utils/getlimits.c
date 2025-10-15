#include <stdio.h>
#include <stdint.h>
#include "../fixedpoint.h"
#include "../fixedconstants.h"
#include "fixedlimits.h"

#define BLOCK_MASK 0xFF

#define F32_BLOCK_COUNT 4
#define F64_BLOCK_COUNT 8

const uint8_t blockOffset[F64_BLOCK_COUNT] = {
	0, 8, 16, 24, 32, 40, 48, 56
};

uint8_t getBiggestOne32(ufixed32_t x){
	uint8_t block 	 = 0;
	uint8_t offset	 = 0;

	for(uint8_t i = 0; i < F32_BLOCK_COUNT; i++){
		offset = blockOffset[F32_BLOCK_COUNT - i - 1];
		block  = (x >> offset) & BLOCK_MASK;

		if(block != 0){
			return (F32_SIZE - offset - bitLengthLUT[block] - 1);
		}
	}

	return F32_SIZE;
}

uint8_t getBiggestOne64(ufixed64_t x){
	uint8_t block 	 = 0;
	uint8_t offset	 = 0;

	for(uint8_t i = 0; i < F64_BLOCK_COUNT; i++){
		offset = blockOffset[F64_BLOCK_COUNT - i - 1];
		block  = (x >> offset) & BLOCK_MASK;

		if(block != 0){
			return (F64_SIZE - offset - bitLengthLUT[block] - 1);
		}
	}

	return F64_SIZE;
}

uint8_t getLowestOne32(ufixed32_t x){
	uint8_t block 	 = 0;
	uint8_t offset	 = 0;

	for(uint8_t i = 0; i < F32_BLOCK_COUNT; i++){
		offset = blockOffset[i];
		block  = (x >> offset) & BLOCK_MASK;

		if(block != 0){
			return (offset + lowestBitLUT[block]);
		}
	}

	return F32_SIZE;
}

uint8_t getLowestOne64(ufixed64_t x){
	uint8_t block 	 = 0;
	uint8_t offset	 = 0;

	for(uint8_t i = 0; i < F64_BLOCK_COUNT; i++){
		offset = blockOffset[i];
		block  = (x >> offset) & BLOCK_MASK;

		if(block != 0){
			return (offset + lowestBitLUT[block]);
		}
	}

	return F64_SIZE;
}
