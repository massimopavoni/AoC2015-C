#include "i_was_told_there_would_be_no_math.h"

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Parsers

static u32 parse_presents(const char *input, u32 presents[1024][3]) {
  u32 present = 0, dimension;

  while (*input) {
    dimension = 0;

    while (dimension < 3 && *input) {
      presents[present][dimension] = 0;

      while ('0' <= *input && *input <= '9') {
        presents[present][dimension] *= 10;
        presents[present][dimension] += *input - '0';
        input++;
      }

      dimension++;
      input++;
    }

    present++;
  }

  return present;
}

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
  u32 presents[1024][3];
  const u32 presents_total = parse_presents(input, presents);
  u32 total = 0;

  // Sum up all costs
  for (u16 p = 0; p < presents_total; p++)
    total += wrapping_or_ribbon
                 ? wrapping_paper_cost(presents[p][0], presents[p][1],
                                       presents[p][2])
                 : ribbon_cost(presents[p][0], presents[p][1], presents[p][2]);

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
