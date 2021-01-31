#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "dsstring.h"

void make_string(DSString * const s, const char * const raw) {
    s->len = strlen(raw);
    s->ptr = malloc(sizeof(char) * s->len);
    s->hash = hash_str2(raw, s->len);

    memcpy(s->ptr, raw, s->len);
}

void free_string(DSString * const s) {
    if(s->ptr) {
        free(s->ptr);
        s->ptr = NULL;
    }
}

int string_equals(const DSString * const s1, DSString * const s2) {
    return s1->hash == s2->hash;
}
