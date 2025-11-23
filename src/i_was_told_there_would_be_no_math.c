#include "i_was_told_there_would_be_no_math.h"

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Functions

static inline u32 wrapping_paper_cost(const u32 a, const u32 b, const u32 c) {
  const u32 area_1 = a * b;
  const u32 area_2 = a * c;
  const u32 area_3 = b * c;

  return 2 * (area_1 + area_2 + area_3) + MIN(MIN(area_1, area_2), area_3);
}

static inline u32 ribbon_cost(const u32 a, const u32 b, const u32 c) {
  return 2 * (a + b + c - MAX(a, MAX(b, c))) + a * b * c;
}

static char *total_cost(const char *input, bool wrapping_or_ribbon) {
  u32 dimensions[3];
  u32 dimension, total = 0;

  while (*input) {
    dimension = 0;

    while (dimension < 3) {
      dimensions[dimension] = 0;

      PARSE_INT(input, dimensions[dimension]);

      dimension++;
      input++;
    }

    total +=
        wrapping_or_ribbon
            ? wrapping_paper_cost(dimensions[0], dimensions[1], dimensions[2])
            : ribbon_cost(dimensions[0], dimensions[1], dimensions[2]);
  }

  return TO_STRING("%u", total);
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *total_wrapping_paper(const char *input) {
  // Surface area + minimum area
  return total_cost(input, true);
}

const char *total_ribbon(const char *input) {
  // Shortest perimeter + volume
  return total_cost(input, false);
}
