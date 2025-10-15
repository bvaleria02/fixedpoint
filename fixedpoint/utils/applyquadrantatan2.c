#include <stdio.h>
#include <stdint.h>
#include "../fixedpoint.h"
#include "atan2utils.h"

fixed32_t angleQuadrantAtan32(int8_t quadrant, fixed32_t angle){
	switch(quadrant){
		case 1: 
				break;
		case 2: angle = fixedSub32(F32_PI, angle);
				break;
		case 3: angle = fixedSub32(F32_PI, angle);
				angle = fixedNeg32(angle);
				break;
		case 4: 
				angle = fixedNeg32(angle);
				break;
	}
	return angle;
}

fixed64_t angleQuadrantAtan64(int8_t quadrant, fixed64_t angle){
	switch(quadrant){
		case 1: 
				break;
		case 2: angle = fixedSub64(F64_PI, angle);
				break;
		case 3: angle = fixedSub64(F64_PI, angle);
				angle = fixedNeg64(angle);
				break;
		case 4: 
				angle = fixedNeg64(angle);
				break;
	}
	return angle;
}
