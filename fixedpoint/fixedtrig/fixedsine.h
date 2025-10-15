#ifndef FIXED_SINE_H
#define FIXED_SINE_H

#include "../fixedpoint.h"

#define F32_HALF_PI (F32_PI >> 1) 
#define F64_HALF_PI (F64_PI >> 1) 

fixed32_t abstractSineTaylor32(ufixed32_t x);

fixed64_t abstractSineTaylor64(ufixed64_t x);

fixed32_t abstractSineCORDIC32(ufixed32_t x);

fixed64_t abstractSineCORDIC64(ufixed64_t x);

#endif // FIXED_SINE_H
