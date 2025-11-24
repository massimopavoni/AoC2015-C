#include "matchsticks.h"

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Exports

const char *code_chars_minus_memory_chars(const char *input) {
  u16 code = 0, memory = 0;

  // Count code and memory char and return subtraction
  while (*input) {
    switch (*input) {
    case '\n':
      memory -= 2;
      input++;
      break;
    case '\\':
      code++;
      input++;
      if (*input == 'x') {
        code += 2;
        input += 2;
      }
      /* fallthrough */
    default:
      code++;
      memory++;
      input++;
      break;
    }
  }

  return TO_STRING("%u", code - memory);
}

const char *encoded_chars_minus_code_chars(const char *input) {
  u16 encoded = 0, code = 0;

  // Count encoded and code chars and return subtraction
  while (*input) {
    switch (*input) {
    case '\n':
      encoded += 2;
      input++;
      break;
    case '\\':
    case '"':
      encoded++;
      /* fallthrough */
    default:
      encoded++;
      code++;
      input++;
      break;
    }
  }

  return TO_STRING("%u", encoded - code);
}
