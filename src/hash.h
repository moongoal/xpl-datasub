#include <vcruntime.h>
#ifndef HASH_H
#define HASH_H

#include <stdint.h>

/**
 * Hash a string.
 *
 * @param s The string to hash.
 *
 * @return A 64-bit hash.
 */
uint64_t hash_str(const char * const s);

/**
 * Hash a string of known length.
 *
 * @param s The string to hash.
 *
 * @return A 64-bit hash.
 */
uint64_t hash_str2(const char * const s, size_t s_len);

#endif // HASH_H
