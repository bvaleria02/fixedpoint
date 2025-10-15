#ifndef FIXED_TAN_H
#define FIXED_TAN_H

#include <stdint.h>
#include "../fixedpoint.h"

fixed32_t abstractTanLUT32(fixed32_t angle);
fixed64_t abstractTanLUT64(fixed64_t angle);

#endif // FIXED_TAN_H
