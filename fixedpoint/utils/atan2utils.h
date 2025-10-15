#ifndef ATAN_2_UTILS_H
#define ATAN_2_UTILS_H

#include <stdint.h>
#include "../fixedpoint.h"

// src/fixedpoint/utilsi/applyquadrantatan2.c
fixed32_t angleQuadrantAtan32(int8_t quadrant, fixed32_t angle);
fixed64_t angleQuadrantAtan64(int8_t quadrant, fixed64_t angle);

#endif // ATAN_2_UTILS_H
