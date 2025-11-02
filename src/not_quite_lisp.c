#include "not_quite_lisp.h"
#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Exports

char *LastFloor(const char *input) {
  i16 floor = 0;

  // Simply go up and down
  while (*input) {
    if (*input == '(')
      floor++;
    else if (*input == ')')
      floor--;

    input++;
  }

  return TO_STRING("%d", floor);
}

char *BasementPosition(const char *input) {
  i16 floor = 0;
  u16 position = 0;

  // Stop as soon as basement is reached
  while (*input) {
    position++;

    if (*input == '(')
      floor++;
    else if (*input == ')')
      floor--;

    if (floor == -1)
      return TO_STRING("%d", position);

    input++;
  }

  return NULL;
}
