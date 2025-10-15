#ifndef FIXED_ATAN2_H
#define FIXED_ATAN2_H

#include "../fixedpoint.h"

fixed32_t abstractAtan2CORDIC32(ufixed32_t y, ufixed32_t x);

fixed64_t abstractAtan2CORDIC64(ufixed64_t y, ufixed64_t x);

#endif // FIXED_ATAN2_H
