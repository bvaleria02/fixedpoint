#include <stdint.h>
#include <stdio.h>
#include "../fixedpoint.h"
#include "fixedtan.h"
#include "../fixedconstants.h"

#define TAN_F32_FRACT_MASK 0x3F

fixed32_t abstractTanLUT32(fixed32_t angle){
	// tan(0) = 0
	if(angle == F32_ZERO){
		return F32_ZERO;
	}

	/*
		Adjusts the incoming angle between -pi/2 and pi/2

	 	Step 1: adds pi/2 so:
			-pi/2 -> 0
			0 -> pi/2
			pi/2 -> pi

		Step 2: Modulo, angle now is in between 0 and pi

		Step 3: subs pi/2 so:
			pi -> pi/2
			pi/2 -> 0
			0 -> -pi/2

	*/

	// Step 1: add pi/2
	fixed32_t result = 0;
	angle = fixedAdd32(angle, F32_PI >> 1);

	// Step 2: modulo
	angle = fixedMod32(angle, F32_PI);

	// Step 3: subs pi/2
	angle = fixedSub32(angle, (F32_PI >> 1));

	// Converts negative angles into positive: tan(-x) = -tan(x)
	uint8_t sign = 0;
	if(angle < 0){
		sign = 1;
		angle = fixedNeg32(angle);
	}

	// Special case: If angle == pi/2, tan(pi/2) is undefined.
	// Returns max fixed32_t value (I32_MANTISSA)
	// If sign is negative, return negative max value
	if(angle == (F32_PI >> 1)){
		result = I32_MANTISSA;
		if(sign){
			result = fixedNeg32(result);
		}
		return result;
	}

	/*
		Index is calculated by round(angle * 1024) because:
		between 0.0 and 1.0 there are 1024 samples, so 1608 total samples (pi/2 * 1024)

		F32_RSHIFT = 16, and TAN_F32_SHIFT = 10, so this is a shift by 6
		Remember, 1.0 = (1 << 16), but we "multiply" it by 1024 so 1/1024 -> 1.0
		by subtracting TAN_F32_SHIFT to the shift.

		Then shift it by 16 to convert it from fixed to integer using the F32_RSHIFT.
	*/

	uint16_t index0 = angle >> (F32_RSHIFT - TAN_F32_SHIFT);
	uint16_t index1 = index0 + 1;

	// If (for some reason) the index is greater than the element count, return the last one
	if(index0 >= TAN_F32_COUNT){
		index0 = TAN_F32_COUNT - 1;
	}

	if(index1 >= TAN_F32_COUNT){
		index1 = TAN_F32_COUNT - 1;
	}

	/*
		Gets the fractional part of the index by shifting left the angle, and then masking.

		Step 1: Masking
			MASK : (0bXXXXXXXX XXXXXXXX XXXXXXXX XX111111)
				 : 111111 -> 0x3F (TAN_F32_FRACT_MASK)

		Step 2: multiply by 1024
			1/1024   (0b0000000 0000000 00000000 01000000) -> 1.0
			1/4096   (0b0000000 0000000 00000000 00010000) -> 0.25
			1/16384  (0b0000000 0000000 00000000 00000100) -> 0.0625
			1/65536  (0b0000000 0000000 00000000 00000001) -> 0.015625
	*/

	ufixed32_t x = angle & TAN_F32_FRACT_MASK;
	x = x << TAN_F32_SHIFT;

	/*
		Linear interpolation
		fixedLerp32(y0: initial point, y1: final point, x: fractional part)
	*/
	fixed32_t y0 = tanLUTF32[index0];

	// Uses the max value for fixed32_t if both index are equal to the LUT count
	fixed32_t y1;
	if(index1 >= (TAN_F32_COUNT - 1) && index0 >= (TAN_F32_COUNT - 1)){
		y1 = I32_MANTISSA;
	} else {
		y1 = tanLUTF32[index1];
	};
 	
	// x = 0;


	result = fixedLerp32(y0, y1, x);

	// printf("\ty0: %lf\n\ty1: %lf\n\tx: %lf\n", convertF32ToDouble(y0), convertF32ToDouble(y1), convertF32ToDouble(x));

	// Handles the sign: tan(-x) = -tan(x)
	if(sign){
		result = fixedNeg32(result);
	}

    return result;
}

fixed64_t abstractTanLUT64(fixed64_t angle){
	if(angle == 0){
		return 0;
	}

	fixed64_t result = 0;
	angle = fixedAdd64(angle, F64_PI >> 1);
	angle = angle % (F64_PI);

	uint8_t sign = 0;
	angle = fixedSub64(angle, (F64_PI >> 1));
	if(angle < 0){
		sign = 1;
		angle = fixedNeg64(angle);
	}
	
	if(angle == (F64_PI >> 1)){
		result = I64_MANTISSA;
		if(sign){
			result = fixedNeg64(result);
		}
		return result;
	}

	uint16_t index = angle >> (F64_RSHIFT - TAN_F64_SHIFT);
	if(index >= TAN_F64_COUNT){
		index = TAN_F64_COUNT - 1;
	}

	result = tanLUTF64[index];
#ifdef DEBUG_MODE
	printf("index: %i\tvalue: %016lx\n", index, result);
#endif

	if(sign){
		result = fixedNeg64(result);
	}
    return result;
}
