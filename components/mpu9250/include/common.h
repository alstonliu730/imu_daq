#ifndef __COMMON_H__
#define __COMMON_H__

#include "esp_types.h"

// Bit manipulation techniques
#define LSHIFT(val, n)              ((uint64_t)(val) << (n))
#define RSHIFT(val, n)              ((uint64_t)(val) >> (n))
#define BIT(n)                      (1ULL << (n))
#define CLR_BIT(n)                  (~BIT((n)))
#define BIT_MASK(msb, lsb)          ((BIT((msb) - (lsb) + 1) - 1) << lsb)
#define CLR_MASK(msb, lsb)          (~ BIT_MASK((msb), (lsb)))
#define BITS(val, msb, lsb)         (((val) & BIT_MASK(msb, lsb)) >> lsb)

#endif /* __COMMON_H__*/