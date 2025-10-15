#include "../fixedpoint.h"
#include "../fixedconstants.h"
#include "fixedmagnitude.h"
#include "fixedsinehyper.h"
#include <stdio.h>
#include <stdint.h>

fixed32_t abstractMagnitudeCORDIC32(ufixed32_t _x, ufixed32_t _y, fixed32_t *arctan){
	fixed32_t x = _x;
	fixed32_t y = _y;
	fixed32_t z = F32_ZERO;

	fixed32_t dx;
	fixed32_t dy;
	
	for(uint8_t i = 0; i < ARCTAN_F32_COUNT; i++){
		dx = x;
		dy = y;

		//printf("x: %lf\ny: %lf\nz: %lf\n\n", convertF32ToDouble(x), convertF32ToDouble(y), convertF32ToDouble(z));
		if(y < F32_ZERO){
			x = dx - fixedRShift32(dy, i);
			y = dy + fixedRShift32(dx, i);
			z = z  - arctanF32[i];
		} else {
			x = dx + fixedRShift32(dy, i);
			y = dy - fixedRShift32(dx, i);
			z = z  + arctanF32[i];
		}
		
	}

	x = fixedMul32(x, CORDIC_CONST_F32);

	if(arctan != NULL){
		(*arctan) = z;
	}

	return x;
}

fixed64_t abstractMagnitudeCORDIC64(ufixed64_t _x, ufixed64_t _y, fixed64_t *arctan){
	fixed64_t x = _x;
	fixed64_t y = _y;
	fixed64_t z = F64_ZERO;

	fixed64_t dx;
	fixed64_t dy;
	
	for(uint8_t i = 0; i < ARCTAN_F64_COUNT; i++){
		dx = x;
		dy = y;

		//printf("x: %lf\ny: %lf\nz: %lf\n\n", convertF64ToDouble(x), convertF64ToDouble(y), convertF64ToDouble(z));
		if(y < F64_ZERO){
			x = dx - fixedRShift64(dy, i);
			y = dy + fixedRShift64(dx, i);
			z = z  - arctanF64[i];
		} else {
			x = dx + fixedRShift64(dy, i);
			y = dy - fixedRShift64(dx, i);
			z = z  + arctanF64[i];
		}
		
	}

	x = fixedMul64(x, CORDIC_CONST_F64);

	if(arctan != NULL){
		(*arctan) = z;
	}

	return x;
}

fixed32_t abstractMagnitudeHyperCORDIC32(ufixed32_t _x, ufixed32_t _y, fixed32_t *arctanh){
	fixed32_t x = _x;
	fixed32_t y = _y;
	fixed32_t z = F32_ZERO;

	fixed32_t dx;
	fixed32_t dy;
	
	for(uint8_t i = 1; i < ARCTAN_F32_COUNT; i++){
		dx = x;
		dy = y;

		// printf("x: %lf\ny: %lf\nz: %lf\n\n", convertF32ToDouble(x), convertF32ToDouble(y), convertF32ToDouble(z));
		if(y < F32_ZERO){
			x = dx + fixedRShift32(dy, i);
			y = dy + fixedRShift32(dx, i);
			z = z  - arctanF32[i];
		} else {
			x = dx - fixedRShift32(dy, i);
			y = dy - fixedRShift32(dx, i);
			z = z  + arctanF32[i];
		}
		
	}

	x = fixedMul32(x, F32_SINH_CORDIC_CONST);

	if(arctanh != NULL){
		(*arctanh) = z;
	}

	return x;
}

fixed64_t abstractMagnitudeHyperCORDIC64(ufixed64_t _x, ufixed64_t _y, fixed64_t *arctanh){
	fixed64_t x = _x;
	fixed64_t y = _y;
	fixed64_t z = F64_ZERO;

	fixed64_t dx;
	fixed64_t dy;
	
	for(uint8_t i = 1; i < ARCTAN_F64_COUNT; i++){
		dx = x;
		dy = y;

		//printf("x: %lf\ny: %lf\nz: %lf\n\n", convertF64ToDouble(x), convertF64ToDouble(y), convertF64ToDouble(z));
		if(y < F64_ZERO){
			x = dx + fixedRShift64(dy, i);
			y = dy + fixedRShift64(dx, i);
			z = z  - arctanF64[i];
		} else {
			x = dx - fixedRShift64(dy, i);
			y = dy - fixedRShift64(dx, i);
			z = z  + arctanF64[i];
		}
		
	}

	x = fixedMul64(x, F64_SINH_CORDIC_CONST);

	if(arctanh != NULL){
		(*arctanh) = z;
	}

	return x;
}

