#include <stdint.h>
#include <string.h>
#include <xxhash.h>
#include "hash.h"

#define HASH_SEED 2147483647

uint64_t hash_str(const char * const s) {
    return hash_str2(s, strlen(s));
}

uint64_t hash_str2(const char * const s, size_t s_len) {
    return (uint64_t)XXH64(s, s_len * sizeof(char), HASH_SEED);
}
