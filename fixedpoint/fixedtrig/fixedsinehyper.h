#ifndef FIXED_SINE_HYPER_H
#define FIXED_SINE_HYPER_H

#include "../fixedpoint.h"

/*
	Defined by
	mul from i=1 to 40 {sqrt{1 - 2^{-2i}}} approx 0.829
	sinh const = 1/0.829 approx 1.20514
*/
#define F32_SINH_CORDIC_CONST 0x00013484
#define F64_SINH_CORDIC_CONST 0x000000013483d0fc 


// These are equal to sinh(0) without any linear correction, just the raw output
#define F32_SINH_CORRECTION 0x000012d5
#define F32_COSH_CORRECTION 0x00010032

// These are equal to cosh(0) without any linear correction, just the raw output
#define F64_SINH_CORRECTION 0x0000000012d3561d
#define F64_COSH_CORRECTION 0x0000000100312e6d

void abstractSineHyperbolicCORDIC32(fixed32_t angle, fixed32_t *sinh, fixed32_t *cosh);

void abstractSineHyperbolicCORDIC64(fixed64_t angle, fixed64_t *sinh, fixed64_t *cosh);

#endif // FIXED_SINE_HYPER_H
