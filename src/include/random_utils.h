#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> // IWYU pragma: keep for sprintf

// ------------------------------------------------------------------------------------------------
// Types

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// ------------------------------------------------------------------------------------------------
// Macros

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define TO_STRING(format, x)                                                   \
  ({                                                                           \
    static char buffer[32];                                                    \
    sprintf(buffer, format, x);                                                \
    buffer;                                                                    \
  })

#define PARSE_INT(input, var)                                                  \
  ({                                                                           \
    while ('0' <= *input && *input <= '9') {                                   \
      var *= 10;                                                               \
      var += *input - '0';                                                     \
      input++;                                                                 \
    }                                                                          \
  })
