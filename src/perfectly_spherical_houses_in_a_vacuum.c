#include "perfectly_spherical_houses_in_a_vacuum.h"

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Functions

static char *unique_house_count(const char *input, const bool robo_santa) {
  bool seen[256][256] = {false};

  u8 santa_x = 127, santa_y = 127;
  u8 robo_x = 127, robo_y = 127;

  seen[santa_x][santa_y] = true;
  u16 unique_houses_count = 1;

  u8 *x = &santa_x, *y = &santa_y;

  bool parity = true;

  while (*input) {
    switch (*input) {
    case '^':
      (*x)--;
      break;
    case 'v':
      (*x)++;
      break;
    case '>':
      (*y)++;
      break;
    case '<':
      (*y)--;
      break;
    }

    if (!seen[*x][*y]) {
      seen[*x][*y] = true;
      unique_houses_count++;
    }

    if (robo_santa) {
      parity = !parity;
      if (parity) {
        x = &santa_x;
        y = &santa_y;
      } else {
        x = &robo_x;
        y = &robo_y;
      }
    }

    input++;
  }

  return TO_STRING("%u", unique_houses_count);
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *santa_house_count(const char *input) {
  // Only Santa delivers presents
  return unique_house_count(input, false);
}

const char *santa_and_robo_santa_house_count(const char *input) {
  // Santa and Robo-Santa deliver presents (and are very much less efficient)
  return unique_house_count(input, true);
}
