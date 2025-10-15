#include "fixedpoint.h"
#include <stdint.h>

fixed32_t fixedAdd32(fixed32_t x1, fixed32_t x2){
	return x1 + x2;
}

ufixed32_t ufixedAdd32(ufixed32_t x1, ufixed32_t x2){
	return x1 + x2;
}

fixed64_t fixedAdd64(fixed64_t x1, fixed64_t x2){
	return x1 + x2;
}

ufixed64_t ufixedAdd64(ufixed64_t x1, ufixed64_t x2){
	return x1 + x2;
}

fixed32_t fixedAddScalar32(fixed32_t x1, int32_t x2, int8_t scale){
	fixed32_t f2 = convertIntToF32(x2, scale);
	return x1 + f2;
}

ufixed32_t ufixedAddScalar32(ufixed32_t x1, uint32_t x2, int8_t scale){
	ufixed32_t f2 = convertIntToUF32(x2, scale);
	return x1 + f2;
}

fixed64_t fixedAddScalar64(fixed64_t x1,  int64_t x2, int8_t scale){
	fixed64_t f2 = convertIntToF64(x2, scale);
	return x1 + f2;
}

ufixed64_t ufixedAddScalar64(ufixed64_t x1, uint64_t x2, int8_t scale){
	ufixed64_t f2 = convertIntToUF64(x2, scale);
	return x1 + f2;
}
