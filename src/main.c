#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "random_utils.h"

#include "doesnt_he_have_intern_elves_for_this.h"
#include "i_was_told_there_would_be_no_math.h"
#include "not_quite_lisp.h"
#include "perfectly_spherical_houses_in_a_vacuum.h"
#include "the_ideal_stocking_stuffer.h"

// ------------------------------------------------------------------------------------------------
// Resources

#include "resources.h"

static char *PUZZLE_ANSWERS[25][3];
static int PUZZLE_COUNT = 0;

static int compare_puzzle_names(const void *a, const void *b) {
  return strcmp(((const char **)a)[0], ((const char **)b)[0]);
}

static void initialize_resources() {
  char *line_ctx, *token_ctx;

  char *puzzle_answers = strdup(RESOURCES[0]);
  char *puzzle = strtok_r(puzzle_answers, "\n", &line_ctx);

  while (puzzle != NULL) {
    PUZZLE_ANSWERS[PUZZLE_COUNT][0] = strtok_r(puzzle, " ", &token_ctx);
    PUZZLE_ANSWERS[PUZZLE_COUNT][1] = strtok_r(NULL, " ", &token_ctx);
    PUZZLE_ANSWERS[PUZZLE_COUNT++][2] = strtok_r(NULL, " ", &token_ctx);

    puzzle = strtok_r(NULL, "\n", &line_ctx);
  }

  qsort(PUZZLE_ANSWERS, PUZZLE_COUNT, sizeof(PUZZLE_ANSWERS[0]),
        compare_puzzle_names);
}

static int get_puzzle_index(const char *name) {
  const char *key[3] = {(char *)name, NULL, NULL};

  char *(*resource)[3] =
      bsearch(&key, PUZZLE_ANSWERS, PUZZLE_COUNT, sizeof(PUZZLE_ANSWERS[0]),
              compare_puzzle_names);

  if (!resource)
    return -1;

  return resource - PUZZLE_ANSWERS;
}

// ------------------------------------------------------------------------------------------------
// Functions

static void pretty_solution(const char *puzzle, const u8 part,
                            const char *(*const solution)(const char *),
                            const char *input, const char *answer) {
  const char *solution_result = solution(input);

  if (strcmp(solution_result, answer) != 0) {
    fprintf(stderr, "Wrong solution for %s part %d: expected %s, but got %s\n",
            puzzle, part, answer, solution_result);
    exit(EXIT_FAILURE);
  }

  printf("%d -> %s\n", part, answer);
}

static void pretty_solution_2(const u8 day, const char *puzzle,
                              const char *(*const solution1)(const char *),
                              const char *(*const solution2)(const char *)) {
  printf("Day %d: %s\n", day, puzzle);

  const int resource_index = get_puzzle_index(puzzle);
  const char *input = RESOURCES[resource_index + 1];
  char **answers = PUZZLE_ANSWERS[resource_index];

  pretty_solution(puzzle, 1, solution1, input, answers[1]);

  if (solution2 != NULL)
    pretty_solution(puzzle, 2, solution2, input, answers[2]);

  printf("\n");
}

// ------------------------------------------------------------------------------------------------
// Exports

int main() {
  initialize_resources();

  printf("AoC 2015 - C\n\n");

  pretty_solution_2(1, "NotQuiteLisp", last_floor, basement_position);

  pretty_solution_2(2, "IWasToldThereWouldBeNoMath", total_wrapping_paper,
                    total_ribbon);

  pretty_solution_2(3, "PerfectlySphericalHousesInAVacuum", santa_house_count,
                    santa_and_robo_santa_house_count);

  pretty_solution_2(4, "TheIdealStockingStuffer", five_zeros_hash_nonce,
                    six_zeros_hash_nonce);

  pretty_solution_2(5, "DoesntHeHaveInternElvesForThis", nice_strings_count,
                    fixed_nice_strings_count);

  return EXIT_SUCCESS;
}
