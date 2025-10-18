#include "../fixedpoint.h"
#include "fixedasine.h"
#include <stdint.h>
#include <stdlib.h>
#include "fixedatan2.h"
#include "../utils/atan2utils.h"
#include "../utils/fixedlimits.h"
#include <stdio.h>

fixed32_t abstractAsin32CORDIC(fixed32_t x){
	/*
		arcsin(x) = atan(x / sqrt(1 - x^2))

		rsqrt(x) = 1 / sqrt(x)
		atan(x)  = atan2(x, 1)

		arcsin(x) = atan2(x * rsqrt(1 - x^2), 1)
	*/

	// Special case, asin(x) is undefined above x=1 and below x=-1
	if(abs(x) > F32_ONE){
		fixedSetErrno(FP_ERROR_OUTOFRANGE);
		return F32_ERROR_VALUE;
	}

	// Special case to avoid calculating the reciprocal of 0
	// (it cause the output to overflow)
	if(x == F32_ONE){
		return F32_PI >> 1;
	} else if(x == fixedNeg32(F32_ONE)){
		return fixedNeg32(F32_PI >> 1);
	}


	ufixed32_t denominator 	= F32_ONE - fixedMul32(x, x);
	ufixed32_t rsqrt	   	= ufixedRSqrt32(denominator);
	fixed32_t  y_o			= fixedMul32(x, rsqrt);
	fixed32_t  x_o			= F32_ONE;

	int8_t quadrant 	= getQuadrant32(&y_o, &x_o);
	fixed32_t angle		= abstractAtan2CORDIC32(y_o, x_o);
	return angleQuadrantAtan32(quadrant, angle);
}

fixed32_t abstractAcos32CORDIC(fixed32_t x){
	/*
		acos(x) = pi/2 - asin(x)
	*/
	fixed32_t value = abstractAsin32CORDIC(x);
		
	if(value == F32_ERROR_VALUE){
		return F32_ERROR_VALUE;
	}

	return (F32_PI >> 1) - value;
}

fixed64_t abstractAsin64CORDIC(fixed64_t x){
	/*
		arcsin(x) = atan(x / sqrt(1 - x^2))

		rsqrt(x) = 1 / sqrt(x)
		atan(x)  = atan2(x, 1)

		arcsin(x) = atan2(x * rsqrt(1 - x^2), 1)
	*/

	// Special case, asin(x) is undefined above x=1 and below x=-1
	if(x > F64_ONE || x < fixedNeg64(F64_ONE)){
		fixedSetErrno(FP_ERROR_OUTOFRANGE);
		return F64_ERROR_VALUE;
	}

	// Special case to avoid calculating the reciprocal of 0
	// (it cause the output to overflow)
	if(x == F64_ONE){
		return F64_PI >> 1;
	} else if(x == fixedNeg64(F64_ONE)){
		return fixedNeg64(F64_PI >> 1);
	}

	// We used the unsigned mul, the signed is buggy and don't work well
	// Also, the unsigned also works for signed
	ufixed64_t denominator 	= F64_ONE - ufixedMul64(x, x);
	ufixed64_t rsqrt	   	= ufixedRSqrt64(denominator);
	fixed64_t  y_o			= ufixedMul64(x, rsqrt);
	fixed64_t  x_o			= F64_ONE;

	int8_t quadrant 	= getQuadrant64(&y_o, &x_o);
	fixed64_t angle		= abstractAtan2CORDIC64(y_o, x_o);
	return angleQuadrantAtan64(quadrant, angle);
}

fixed64_t abstractAcos64CORDIC(fixed64_t x){
	/*
		acos(x) = pi/2 - asin(x)
	*/
	fixed64_t value = abstractAsin64CORDIC(x);
		
	if(value == F64_ERROR_VALUE){
		return F64_ERROR_VALUE;
	}

	return (F64_PI >> 1) - value;
}
