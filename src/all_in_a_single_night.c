#include "all_in_a_single_night.h"

#include <stdint.h>
#include <string.h>

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Functions

static inline void best_path_test(u16 location_distances[676][676],
                                  u16 locations[10], u16 locations_count,
                                  u16 *best, bool shortest_or_longest) {
  u16 cost = 0;

  for (u8 l = 1; l < locations_count; l++)
    cost += location_distances[locations[l - 1]][locations[l]];

  *best = shortest_or_longest ? MIN(*best, cost) : MAX(*best, cost);
}

static const char *travelling_santa_distance(const char *input,
                                             bool shortest_or_longest) {
  u16 location_distances[676][676];
  memset(location_distances, 0xFF, sizeof(location_distances));

  u16 locations[10] = {0};
  u16 first_location = 0, location1, location2, distance, locations_count = 0;

  while (*input) {
    location1 = (*input - 'A') * 26;
    input++;
    location1 += *input - 'a';

    while (*input < 'A' || *input > 'Z')
      input++;

    location2 = (*input - 'A') * 26;
    input++;
    location2 += *input - 'a';

    while (*input < '0' || *input > '9')
      input++;

    distance = 0;
    PARSE_INT(input, distance);

    location_distances[location1][location2] = distance;
    location_distances[location2][location1] = distance;

    if (first_location == 0) {
      locations[locations_count++] = location1;
      first_location = location1;
    }

    if (first_location == location1)
      locations[locations_count++] = location2;

    input++;
  }

  u16 best = shortest_or_longest ? UINT16_MAX : 0;

  u16 control[locations_count];
  for (u8 l = 0; l < locations_count; l++)
    control[l] = 0;

  best_path_test(location_distances, locations, locations_count, &best,
                 shortest_or_longest);

  // Brute-force TSP by generating all possible locations permutations
  // (Heap's algorithm)
  u16 swap;
  u8 l = 0;
  while (l < locations_count) {
    if (control[l] < l) {

      if (l % 2 == 0) {
        swap = locations[0];
        locations[0] = locations[l];
        locations[l] = swap;
      } else {
        swap = locations[control[l]];
        locations[control[l]] = locations[l];
        locations[l] = swap;
      }

      best_path_test(location_distances, locations, locations_count, &best,
                     shortest_or_longest);

      control[l]++;
      l = 0;
    } else {
      control[l] = 0;
      l++;
    }
  }

  return TO_STRING("%u", best);
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *travelling_santa_shortest_distance(const char *input) {
  // Find shortest travelling santa problem path
  return travelling_santa_distance(input, true);
}

const char *travelling_santa_longest_distance(const char *input) {
  // Find longest travelling santa problem path
  return travelling_santa_distance(input, false);
}
