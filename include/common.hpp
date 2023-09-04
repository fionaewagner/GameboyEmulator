#pragma once

#include <cstdint> // For the standard integer types like uint8_t, uint16_t, etc.

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define BIT(a, n) ((a & (1 << n)) ? 1 : 0)
#define BETWEEN(a, b, c) ((a >= b) && (a <= c))

u32 get_ticks();
void delay(u32 ms);
