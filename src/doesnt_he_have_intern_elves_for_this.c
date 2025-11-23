#include "doesnt_he_have_intern_elves_for_this.h"

#include <string.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include "pcre2.h"

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Functions

static const char *matching_strings_count(const char *input,
                                          const char *pattern) {
  int error_code;
  PCRE2_SIZE error_offset;
  pcre2_code *regex = pcre2_compile((PCRE2_SPTR)pattern, PCRE2_ZERO_TERMINATED,
                                    0, &error_code, &error_offset, NULL);
  pcre2_match_data *match_data =
      pcre2_match_data_create_from_pattern(regex, NULL);

  u16 count = 0;
  char *next;
  u8 len;

  while (*input) {
    next = strchr(input, '\n');
    len = next == NULL ? strlen(input) : (size_t)(next - input);

    if (pcre2_match(regex, (PCRE2_SPTR)input, len, 0, 0, match_data, NULL) >= 0)
      count++;

    if (next == NULL)
      break;

    input += len + 1;
  }

  pcre2_code_free(regex);
  pcre2_match_data_free(match_data);

  return TO_STRING("%u", count);
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *nice_strings_count(const char *input) {
  // Nice strings have 3 vowels, twice in a row letter, no forbidden pairs
  return matching_strings_count(
      input, "^(?=(?:.*[aeiou]){3,})(?=.*(.)\\1)(?!.*(?:ab|cd|pq|xy)).*$");
}

const char *fixed_nice_strings_count(const char *input) {
  // Nice strings have non overlapping repeated pair, single letter separated
  // same letter
  return matching_strings_count(input, "^(?=.*(.{2}).*\\1)(?=.*(.).\\2).*$");
}
