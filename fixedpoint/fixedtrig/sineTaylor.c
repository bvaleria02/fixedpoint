#include "../fixedpoint.h"
#include "../fixedconstants.h"
#include "../utils/fixedlimits.h"
#include "fixedsine.h"
#include <stdio.h>
#include <stdint.h>

fixed32_t abstractSineTaylor32(ufixed32_t x){
	ufixed32_t normalized = x % (F32_PI << 1);
	//ufixed32_t normalized = x;
	uint8_t octant = getOctant32(normalized);
	normalized = normalized % (F32_PI >> (DIVIDE_BY_4));

#ifdef DEBUG_MODE
	double a = convertF32ToDouble(normalized);
	printf("norm: %lf\toct: %i\n", a, octant);
#endif

	ufixed32_t sin_x = 0;
	ufixed32_t cos_x = 0;

	ufixed32_t accS = 0;
	ufixed32_t accC = 0;

	ufixed32_t acc2 = F32_ONE;
	ufixed32_t acc3 = 0;
	
	for(uint8_t i = 0; i < RECIPROCAL_FACT_F32_COUNT; i++){
		if(i == 0){
			acc2 = F32_ONE;
			acc3 = F32_ONE;
#ifdef DEBUG_EXTRA_MODE
			a = convertF32ToDouble(acc2);
			printf("acc2: %lf\n", a);
#endif
		} else {
			acc2 = ufixedMul32(acc2, normalized);
			acc3 = ufixedMul32(acc2, reciprocalFactF32[i-1]);
#ifdef DEBUG_EXTRA_MODE
			a = convertF32ToDouble(acc2);
			printf("acc2: %lf\n", a);
#endif
		}


		switch(i & 0x3){
			case 0:	accC = ufixedAdd32(accC, acc3);
					break;
			case 1:	accS = ufixedAdd32(accS, acc3);
					break;
			case 2: accC = ufixedSub32(accC, acc3);
					break;
			case 3: accS = ufixedSub32(accS, acc3);
					break;
			default:
					break;
		};

#ifdef DEBUG_EXTRA_MODE
		printf("== %i ==\n", i);
		a = convertF32ToDouble(accC);
		printf("cos: %lf\n", a);
		a = convertF32ToDouble(accS);
		printf("sin: %lf\n", a);
#endif
	}
	sin_x = accS;
	cos_x = accC;

	fixed32_t result = 0;
	switch(octant & 0x3){
		case 0:	// sin(x)
				// r = sin(x)
				result = sin_x;
				break;
		case 1:	// sin(x + pi/4)
				// r = sin(x)*cos(pi/4) + cos(x)*sin(pi/4)
				// cos(pi/4) = sqrt(2)/2
				// sin(pi/4) = sqrt(2)/2
				// r = sin(x)*sqrt(2)/2 + cos(x)*sqrt(2)/2
				// F32_SQRT_2 >> 1 = sqrt(2)/2
				result = fixedAdd32(sin_x, cos_x);
				result = fixedMul32(result, F32_SQRT_2 >> 1);
				break;
		case 2:	// sin(x + pi/2)
				// r = sin(x)*cos(pi/2) + cos(x)*sin(pi/2)
				// cos(pi/2) = 0
				// sin(pi/2) = 1
				// r = sin(x)*0 + cos(x)*1
				// r = cos(x)
				result = cos_x;
				break;
		case 3:	// sin(x + 3pi/2)
				// r = sin(x)*cos(3pi/4) + cos(x)*sin(3pi/4)
				// cos(3pi/4) = -sqrt(2)/2
				// sin(3pi/4) = sqrt(2)/2
				// r = sin(x)*-sqrt(3pi/4) + cos(x)*sqrt(3pi/4)
				// F32_SQRT_2 >> 1 = sqrt(2)/2
				result = fixedSub32(cos_x, sin_x);
				result = fixedMul32(result, F32_SQRT_2 >> 1);
				break;
	}

	if(octant & 0x4){
		result = result * -1;
	}
	return result;
}

fixed64_t abstractSineTaylor64(ufixed64_t x){
	ufixed64_t normalized = x % (F64_PI << 1);
	//ufixed32_t normalized = x;
	uint8_t octant = getOctant64(normalized);
	normalized = normalized % (F64_PI >> (DIVIDE_BY_4));

#ifdef DEBUG_MODE
	double a = convertF64ToDouble(normalized);
	printf("norm: %lf\toct: %i\n", a, octant);
#endif

	ufixed64_t sin_x = 0;
	ufixed64_t cos_x = 0;

	ufixed64_t accS = 0;
	ufixed64_t accC = 0;

	ufixed64_t acc2 = F64_ONE;
	ufixed64_t acc3 = 0;
	
	for(uint8_t i = 0; i < RECIPROCAL_FACT_F64_COUNT; i++){
		if(i == 0){
			acc2 = F64_ONE;
			acc3 = F64_ONE;
#ifdef DEBUG_EXTRA_MODE
			a = convertF64ToDouble(acc2);
			printf("acc2: %lf\n", a);
#endif
		} else {
			acc2 = ufixedMul64(acc2, normalized);
			acc3 = ufixedMul64(acc2, reciprocalFactF64[i-1]);
#ifdef DEBUG_EXTRA_MODE
			a = convertF64ToDouble(acc2);
			printf("acc2: %lf\n", a);
#endif
		}


		switch(i & 0x3){
			case 0:	accC = ufixedAdd64(accC, acc3);
					break;
			case 1:	accS = ufixedAdd64(accS, acc3);
					break;
			case 2: accC = ufixedSub64(accC, acc3);
					break;
			case 3: accS = ufixedSub64(accS, acc3);
					break;
			default:
					break;
		};

#ifdef DEBUG_EXTRA_MODE
		printf("== %i ==\n", i);
		a = convertF64ToDouble(accC);
		printf("cos: %lf\n", a);
		a = convertF64ToDouble(accS);
		printf("sin: %lf\n", a);
#endif
	}
	sin_x = accS;
	cos_x = accC;

	fixed64_t result = 0;
	switch(octant & 0x3){
		case 0:	// sin(x)
				// r = sin(x)
				result = sin_x;
				break;
		case 1:	// sin(x + pi/4)
				// r = sin(x)*cos(pi/4) + cos(x)*sin(pi/4)
				// cos(pi/4) = sqrt(2)/2
				// sin(pi/4) = sqrt(2)/2
				// r = sin(x)*sqrt(2)/2 + cos(x)*sqrt(2)/2
				// F64_SQRT_2 >> 1 = sqrt(2)/2
				result = fixedAdd64(sin_x, cos_x);
				result = fixedMul64(result, F64_SQRT_2 >> 1);
				break;
		case 2:	// sin(x + pi/2)
				// r = sin(x)*cos(pi/2) + cos(x)*sin(pi/2)
				// cos(pi/2) = 0
				// sin(pi/2) = 1
				// r = sin(x)*0 + cos(x)*1
				// r = cos(x)
				result = cos_x;
				break;
		case 3:	// sin(x + 3pi/2)
				// r = sin(x)*cos(3pi/4) + cos(x)*sin(3pi/4)
				// cos(3pi/4) = -sqrt(2)/2
				// sin(3pi/4) = sqrt(2)/2
				// r = sin(x)*-sqrt(3pi/4) + cos(x)*sqrt(3pi/4)
				// F64_SQRT_2 >> 1 = sqrt(2)/2
				result = fixedSub64(cos_x, sin_x);
				result = fixedMul64(result, F64_SQRT_2 >> 1);
				break;
	}

	if(octant & 0x4){
		result = result * -1;
	}

	if(result > F64_ONE){
		result = fixedSub64(result, F64_ONE);
	} else if(result < (F64_ONE * -1)){
		result = fixedAdd64(result, F64_ONE);
	}
	return result;
}

