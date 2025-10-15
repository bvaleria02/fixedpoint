#include <stdio.h>
#include <stdint.h>
#include "../fixedpoint.h"
#include "fixedlimits.h"

int8_t getQuadrant32(fixed32_t *y, fixed32_t *x){
	if(*x >= 0 && *y < 0){
		// 270° to 0°
		(*y) = fixedNeg32(*y);
		return 4;
	} else if(*x < 0 && *y < 0){
		// 180° to 270°
		(*x) = fixedNeg32(*x);
		(*y) = fixedNeg32(*y);
		return 3;
	} else if(*x < 0 && *y >= 0){
		// 90° to 180°
		(*x) = fixedNeg32(*x);
		return 2;
	}

	return 1;
}

int8_t getQuadrant64(fixed64_t *y, fixed64_t *x){
	if(*x >= 0 && *y < 0){
		// 270° to 0°
		(*y) = fixedNeg64(*y);
		return 4;
	} else if(*x < 0 && *y < 0){
		// 180° to 270°
		(*x) = fixedNeg64(*x);
		(*y) = fixedNeg64(*y);
		return 3;
	} else if(*x < 0 && *y >= 0){
		// 90° to 180°
		(*x) = fixedNeg64(*x);
		return 2;
	}

	return 1;
}
