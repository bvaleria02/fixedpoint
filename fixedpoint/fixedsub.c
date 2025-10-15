#include "fixedpoint.h"
#include <stdint.h>

fixed32_t fixedSub32(fixed32_t x1, fixed32_t x2){
	return x1 - x2;
}

ufixed32_t ufixedSub32(ufixed32_t x1, ufixed32_t x2){
	return x1 - x2;
}

fixed64_t fixedSub64(fixed64_t x1, fixed64_t x2){
	return x1 - x2;
}

ufixed64_t ufixedSub64(ufixed64_t x1, ufixed64_t x2){
	return x1 - x2;
}

fixed32_t fixedSubScalar32(fixed32_t x1, int32_t x2, int8_t scale){
	fixed32_t f2 = convertIntToF32(x2, scale);
	return x1 - f2;
}

ufixed32_t ufixedSubScalar32(ufixed32_t x1, uint32_t x2, int8_t scale){
	ufixed32_t f2 = convertIntToUF32(x2, scale);
	return x1 - f2;
}

fixed64_t fixedSubScalar64(fixed64_t x1,  int64_t x2, int8_t scale){
	fixed64_t f2 = convertIntToF64(x2, scale);
	return x1 - f2;
}

ufixed64_t ufixedSubScalar64(ufixed64_t x1, uint64_t x2, int8_t scale){
	ufixed64_t f2 = convertIntToUF64(x2, scale);
	return x1 - f2;
}
