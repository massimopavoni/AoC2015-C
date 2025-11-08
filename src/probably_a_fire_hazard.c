#include "probably_a_fire_hazard.h"

#include <string.h>

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Types

enum Operation { TURN_OFF, TURN_ON, TOGGLE };

// ------------------------------------------------------------------------------------------------
// Functions

static void light_off_on(u8 *light, const enum Operation op) {
  *light = op == TURN_OFF ? 0 : (op == TURN_ON ? 1 : !(*light));
}

static void light_brightness(u8 *light, const enum Operation op) {
  *light += op == TURN_OFF ? (*light > 0 ? -1 : 0) : (op == TURN_ON ? 1 : 2);
}

const char *result_after_light_instructions(const char *input,
                                            bool off_on_or_brightness) {
  u8 lights[1000][1000] = {0};
  enum Operation op;
  u16 rectangle_coords[4];
  u8 current_coord;
  u16 x, y;

  while (*input) {
    if (input[1] == 'o') {
      op = TOGGLE;
      input += 7;
    } else if (input[6] == 'n') {
      op = TURN_ON;
      input += 8;
    } else {
      op = TURN_OFF;
      input += 9;
    }

    memset(rectangle_coords, 0, sizeof(rectangle_coords));
    current_coord = 0;

    while (*input != '\n') {
      if (*input == ',') {
        current_coord++;
        input++;
      } else if (*input == ' ') {
        current_coord++;
        input += 9;
      }

      while ('0' <= *input && *input <= '9') {
        rectangle_coords[current_coord] *= 10;
        rectangle_coords[current_coord] += *input - '0';
        input++;
      }
    }

    for (x = rectangle_coords[0]; x <= rectangle_coords[2]; x++)
      for (y = rectangle_coords[1]; y <= rectangle_coords[3]; y++) {
        off_on_or_brightness ? light_off_on(&(lights[x][y]), op)
                             : light_brightness(&(lights[x][y]), op);
      }

    input++;
  }

  u32 result = 0;

  for (u16 x = 0; x < 1000; x++)
    for (u16 y = 0; y < 1000; y++)
      result += lights[x][y];

  return TO_STRING("%u", result);
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *lights_on_count(const char *input) {
  // Just turning off and on lights
  return result_after_light_instructions(input, true);
}

const char *lights_total_brightness(const char *input) {
  // Dialing down or up lights brightness
  return result_after_light_instructions(input, false);
}
