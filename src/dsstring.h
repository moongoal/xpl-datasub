#ifndef DSSTRING_H
#define DSSTRING_H

#include <stdint.h>

typedef struct DSString {
    char *ptr;
    uint64_t hash;
    size_t len;
} DSString;

/**
 * Make a new DSString from a raw string. The DSString will have its own allocated storage.
 *
 * @param s The DSString object to populate.
 * @param raw The raw, NUL terminated string.
 */
void make_string(DSString * const s, const char * const raw);

/**
 * Free any allocated memory associated with a DSString object.
 *
 * @param s The DSString object to free.
 */
void free_string(DSString * const s);

/**
 * Return 1 if the two input strings are equal, 0 if they are not.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 *
 * @note Equality is defined as the contents of the string being equal byte by byte.
 */
int string_equals(const DSString * const s1, DSString * const s2);

#endif // DSSTRING_H
