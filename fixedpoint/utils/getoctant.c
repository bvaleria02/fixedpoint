#include <stdint.h>
#include "../fixedpoint.h"
#include "fixedlimits.h"

uint8_t getOctant32(ufixed32_t x){
	uint8_t octant = 0;
	ufixed32_t oct_pi = F32_PI >> (DIVIDE_BY_4);
	for(uint8_t i = 0; i < OCTANT_ITER; i++){
		if(x < (oct_pi * (i + 1))){
			octant = i;
			break;
		}
	}
	return octant;
}

uint8_t getOctant64(ufixed64_t x){
	uint8_t octant = 0;
	ufixed64_t oct_pi = F64_PI >> (DIVIDE_BY_4);
	for(uint8_t i = 0; i < OCTANT_ITER; i++){
		if(x < (oct_pi * (i + 1))){
			octant = i;
			break;
		}
	}
	return octant;
}
