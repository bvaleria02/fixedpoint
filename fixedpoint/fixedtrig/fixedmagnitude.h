#ifndef FIXED_MAGNITUDE_H
#define FIXED_MAGNITUDE_H

#include "../fixedpoint.h"

fixed32_t abstractMagnitudeCORDIC32(ufixed32_t x, ufixed32_t y, fixed32_t *arctan);
fixed64_t abstractMagnitudeCORDIC64(ufixed64_t x, ufixed64_t y, fixed64_t *arctan);

fixed32_t abstractMagnitudeHyperCORDIC32(ufixed32_t x, ufixed32_t y, fixed32_t *arctanh);
fixed64_t abstractMagnitudeHyperCORDIC64(ufixed64_t x, ufixed64_t y, fixed64_t *arctanh);

#endif // FIXED_MAGNITUDE_H
