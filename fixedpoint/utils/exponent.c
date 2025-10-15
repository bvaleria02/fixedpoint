#include <stdint.h>
#include "../fixedpoint.h"
#include "fixedlimits.h"

int8_t getExponent32(ufixed32_t x){
	uint8_t n 		= getBiggestOne32(x);
	int8_t shift 	= (F32_SIZE >> 1) - n - 1;
	return shift;
}

int8_t getExponent64(ufixed64_t x){
	uint8_t n 		= getBiggestOne64(x);
	int8_t shift 	= (F64_SIZE >> 1) - n - 1;
	return shift;
}
