#include "../fixedpoint.h"
#include "../fixedconstants.h"
#include "../utils/fixedlimits.h"
#include "fixedsinehyper.h"
#include <stdio.h>
#include <stdint.h>

void abstractSineHyperbolicCORDIC32(fixed32_t angle, fixed32_t *sinh, fixed32_t *cosh){
	fixed32_t x = F32_SINH_CORDIC_CONST;
	fixed32_t y = F32_ZERO;
	fixed32_t z = angle;

	fixed32_t dx;
	fixed32_t dy;

	for(uint8_t i = 1; i < ARCTAN_F32_COUNT; i++){

		for(uint8_t j = 0; j < 2; j++){
			dx = x;
			dy = y;

			// printf("x: %lf\ny: %lf\nz: %lf\n\n", convertF32ToDouble(x), convertF32ToDouble(y), convertF32ToDouble(z));
			if(z < F32_ZERO){
				x = dx - fixedRShift32(dy, i);
				y = dy - fixedRShift32(dx, i);
				z = z + arctanF32[i];
			} else {
				x = dx + fixedRShift32(dy, i);
				y = dy + fixedRShift32(dx, i);
				z = z - arctanF32[i];
			}
		
			if(!(i == 4 || i == 13)){
				break;
			}
		}
	}

	// sinh = (y - 0.073537) * 479/512
	// cosh =  (x - 1.00075) * 420/512 + 1

	y = y - F32_SINH_CORRECTION;
	x = x - F32_COSH_CORRECTION;

	// 479 = 480 - 1
	// 479 = 256 + 128 + 64 + 32 - 1
	y = (y << 8) + (y << 7) + (y << 6) + (y << 5) - y;
	y = (y >> 9);

	// 420 = 256 + 128 + 32 + 4
	x = (x << 8) + (x << 7) + (x << 5) + (x << 2);
	x = x >> 9;
	x = x + F32_ONE;

	(*sinh) = y;
	(*cosh) = x;
}

void abstractSineHyperbolicCORDIC64(fixed64_t angle, fixed64_t *sinh, fixed64_t *cosh){
	fixed64_t x = F64_SINH_CORDIC_CONST;
	fixed64_t y = F64_ZERO;
	fixed64_t z = angle;

	fixed64_t dx;
	fixed64_t dy;

	for(uint8_t i = 1; i < ARCTAN_F64_COUNT; i++){

		for(uint8_t j = 0; j < 2; j++){
			dx = x;
			dy = y;

			// printf("x: %lf\ny: %lf\nz: %lf\n\n", convertF64ToDouble(x), convertF64ToDouble(y), convertF64ToDouble(z));
			if(z < F64_ZERO){
				x = dx - fixedRShift64(dy, i);
				y = dy - fixedRShift64(dx, i);
				z = z + arctanF64[i];
			} else {
				x = dx + fixedRShift64(dy, i);
				y = dy + fixedRShift64(dx, i);
				z = z - arctanF64[i];
			}
		
			if(!(i == 4 || i == 13)){
				break;
			}
		}
	}

	// sinh = (y - 0.073537) * 479/512
	// cosh =  (x - 1.00075) * 420/512 + 1

	y = y - F64_SINH_CORRECTION;
	x = x - F64_COSH_CORRECTION;

	// 479 = 480 - 1
	// 479 = 256 + 128 + 64 + 32 - 1
	y = (y << 8) + (y << 7) + (y << 6) + (y << 5) - y;
	y = (y >> 9);

	// 420 = 256 + 128 + 32 + 4
	x = (x << 8) + (x << 7) + (x << 5) + (x << 2);
	x = x >> 9;
	x = x + F64_ONE;

	(*sinh) = y;
	(*cosh) = x;
}
