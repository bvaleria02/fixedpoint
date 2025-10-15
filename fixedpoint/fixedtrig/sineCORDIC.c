#include "../fixedpoint.h"
#include "../fixedconstants.h"
#include "../utils/fixedlimits.h"
#include "fixedsine.h"
#include <stdio.h>
#include <stdint.h>

fixed32_t abstractSineCORDIC32(ufixed32_t x){
	ufixed32_t normalized = x % (F32_PI << 1);
	uint8_t octant = getOctant32(normalized);
	normalized = normalized % (F32_PI >> 1);

	fixed32_t _x = CORDIC_CONST_F32;
	fixed32_t _y = 0;
	fixed32_t _z = normalized;

	fixed32_t dx = 0;
	fixed32_t dy = 0;
	
	for(uint8_t i = 0; i < ARCTAN_F32_COUNT; i++){
		dx = _x;
		dy = _y;

		_x = dy;
		if(_z < 0){
			_x = fixedNeg32(_x);
		}
		_x = _x >> i;
		_x = fixedSub32(dx, _x);

		_y = dx;
		if(_z < 0){
			_y = fixedNeg32(_y);
		}
		_y = _y >> i;
		_y = fixedAdd32(dy, _y);

		if(_z >= 0){
			_z = fixedSub32(_z, arctanF32[i]);
		} else {
			_z = fixedAdd32(_z, arctanF32[i]);
		}
	}

	fixed32_t result = 0;
	
	switch(octant & 0x6){
		case 0: result = _y;
				break;
		case 2: result = _x;
				break;
		case 4: result = fixedNeg32(_y);
				break;
		case 6: result = fixedNeg32(_x);
				break;
	}
	return result;
}


fixed64_t abstractSineCORDIC64(ufixed64_t x){
	ufixed64_t normalized = x % (F64_PI << 1);
	uint8_t octant = getOctant64(normalized);
	normalized = normalized % (F64_PI >> 1);

	fixed64_t _x = CORDIC_CONST_F64;
	fixed64_t _y = 0;
	fixed64_t _z = normalized;

	fixed64_t dx = 0;
	fixed64_t dy = 0;
	
	for(uint8_t i = 0; i < ARCTAN_F64_COUNT; i++){
		dx = _x;
		dy = _y;

		_x = dy;
		if(_z < 0){
			_x = fixedNeg64(_x);
		}
		_x = _x >> i;
		_x = fixedSub64(dx, _x);

		_y = dx;
		if(_z < 0){
			_y = fixedNeg64(_y);
		}
		_y = _y >> i;
		_y = fixedAdd64(dy, _y);

		if(_z >= 0){
			_z = fixedSub64(_z, arctanF64[i]);
		} else {
			_z = fixedAdd64(_z, arctanF64[i]);
		}
	}

	fixed64_t result = 0;
	
	switch(octant & 0x6){
		case 0: result = _y;
				break;
		case 2: result = _x;
				break;
		case 4: result = fixedNeg64(_y);
				break;
		case 6: result = fixedNeg64(_x);
				break;
	}
	return result;
}
