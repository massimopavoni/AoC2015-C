#pragma once

#include <stdio.h>

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
