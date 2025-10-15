#include "../fixedpoint.h"
#include "../fixedconstants.h"
#include "../utils/fixedlimits.h"
#include "fixedsine.h"
#include <stdio.h>
#include <stdint.h>

fixed32_t abstractAtan2CORDIC32(ufixed32_t y, ufixed32_t x){
	fixed32_t angle = 0;

	fixed32_t xo = x;
	fixed32_t yo = y;

	fixed32_t xn = 0;
	fixed32_t yn = 0;

	fixed32_t xa = 0;
	fixed32_t ya = 0;

	if(x == 0 && y == 0){
		// undefined case, usign 0 as a failback.
		return 0;
	}

	for(uint8_t i = 0; i < ARCTAN_F32_COUNT; i++){
		if(xo < 0){
			xa = fixedNeg32(xo);
			xa = xa >> i;
			xa = fixedNeg32(xa);
		} else {
			xa = xo >> i;
		}

		if(yo < 0){
			ya = fixedNeg32(yo);
			ya = ya >> i;
			ya = fixedNeg32(ya);
		} else {
			ya = yo >> i;
		}

		if(yo > 0){
			xn = fixedAdd32(xo, ya); 
			yn = fixedSub32(yo, xa); 
			angle = fixedAdd32(angle, arctanF32[i]);
		} else {
			xn = fixedSub32(xo, ya); 
			yn = fixedAdd32(yo, xa); 
			angle = fixedSub32(angle, arctanF32[i]);
		}

		xo = xn;
		yo = yn;
	}

	return angle;
}

fixed64_t abstractAtan2CORDIC64(ufixed64_t y, ufixed64_t x){
	fixed64_t angle = 0;

	fixed64_t xo = x;
	fixed64_t yo = y;

	fixed64_t xn = 0;
	fixed64_t yn = 0;

	fixed64_t xa = 0;
	fixed64_t ya = 0;

	if(x == 0 && y == 0){
		// undefined case, usign 0 as a failback.
		return 0;
	}

	for(uint8_t i = 0; i < ARCTAN_F64_COUNT; i++){
		if(xo < 0){
			xa = fixedNeg64(xo);
			xa = xa >> i;
			xa = fixedNeg64(xa);
		} else {
			xa = xo >> i;
		}

		if(yo < 0){
			ya = fixedNeg64(yo);
			ya = ya >> i;
			ya = fixedNeg64(ya);
		} else {
			ya = yo >> i;
		}

		if(yo > 0){
			xn = fixedAdd64(xo, ya); 
			yn = fixedSub64(yo, xa); 
			angle = fixedAdd64(angle, arctanF64[i]);
		} else {
			xn = fixedSub64(xo, ya); 
			yn = fixedAdd64(yo, xa); 
			angle = fixedSub64(angle, arctanF64[i]);
		}

		xo = xn;
		yo = yn;
	}

	return angle;
}
