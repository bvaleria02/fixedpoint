#ifndef FIXED_LIMITS_H
#define FIXED_LIMITS_H

#include <stdint.h>
#include "../fixedpoint.h"

#define OCTANT_ITER 8
#define DIVIDE_BY_4 2

// src/fixedpoint/utils/getoctant.c
uint8_t getOctant32(ufixed32_t x);
uint8_t getOctant64(ufixed64_t x);

// src/fixedpoint/utils/getquadrant.c
int8_t getQuadrant32(fixed32_t *y, fixed32_t *x);
int8_t getQuadrant64(fixed64_t *y, fixed64_t *x);

// src/fixedpoint/utils/getlimits.c
uint8_t getBiggestOne32(ufixed32_t x);
uint8_t getBiggestOne64(ufixed64_t x);
uint8_t getLowestOne32(ufixed32_t x);
uint8_t getLowestOne64(ufixed64_t x);

// src/fixedpoint/utils/exponent.c
int8_t getExponent32(ufixed32_t x);
int8_t getExponent64(ufixed64_t x);

#endif // FIXED_LIMITS_H
