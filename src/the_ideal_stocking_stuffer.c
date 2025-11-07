#include "the_ideal_stocking_stuffer.h"

#include <omp.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "md5.h"

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Functions

static bool check_hash_prefix(const unsigned char *hash, const u8 zeros) {
  return (hash[0] == 0x00 && hash[1] == 0x00 &&
          (zeros == 5 ? (hash[2] & 0xF0) == 0x00 : hash[2] == 0x00));
}

static const char *find_hash_nonce(const char *input, const u8 zeros) {
  const size_t base_len = strlen(input);
  _Atomic u32 answer = 0;

#pragma omp parallel
  {
    char string[64];
    unsigned char hash[16];
    MD5_CTX ctx;

    memcpy(string, input, base_len);

    const u32 step = omp_get_num_threads();
    u32 nonce = omp_get_thread_num();
    u32 best;
    size_t len;

    while (1) {
      best = atomic_load_explicit(&answer, memory_order_relaxed);

      if (best && nonce >= best)
        break;

      nonce += step;

      len = base_len + sprintf(string + base_len, "%u", nonce);
      MD5_Init(&ctx);
      MD5_Update(&ctx, string, len);
      MD5_Final(hash, &ctx);

      if (check_hash_prefix(hash, zeros)) {
        u32 expected = best;
        while ((!expected || nonce < expected) &&
               !atomic_compare_exchange_weak_explicit(&answer, &expected, nonce,
                                                      memory_order_relaxed,
                                                      memory_order_relaxed)) {
          if (expected && nonce >= expected)
            break;
        }
        break;
      }
    }
  }

  return TO_STRING("%u", atomic_load(&answer));
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *five_zeros_hash_nonce(const char *input) {
  // Find nonce with hash starting with five zeros
  return find_hash_nonce(input, 5);
}

const char *six_zeros_hash_nonce(const char *input) {
  // Find nonce with hash starting with six zeros
  return find_hash_nonce(input, 6);
}
