#include <string.h>
#include <XPLM/XPLMDataAccess.h>
#include "drefs.h"
// TODO: Hashes should be used when comparing datarefs

// Number of dataref slots to allocate when growing memory.
#define DREF_CHUNK_SZ 256

char **sub_datarefs = NULL; // Subscribed datarefs
size_t n_sub_datarefs = 0; // sub_datarefs length

char **get_free_dref_slot() {
    if (sub_datarefs) {
        for(size_t i = 0; i < n_sub_datarefs; ++i) {
            if(!sub_datarefs[i]) {
                return &sub_datarefs[i];
            }
        }
    }

    return NULL;
}

void grow_sub_datarefs_array() {
    // Realloc memory
    n_sub_datarefs += DREF_CHUNK_SZ;
    sub_datarefs = realloc(sub_datarefs, sizeof(char *) * n_sub_datarefs);

    // Clean memory
    memset(&sub_datarefs[n_sub_datarefs - DREF_CHUNK_SZ], 0, sizeof(char *) * DREF_CHUNK_SZ);
}

void add_sub_dataref(const char * const dref) {
    if(!is_dref_subscribed(dref)) {
        char **dref_slot = get_free_dref_slot();

        if(!dref_slot) {
            const size_t next_free_slot = n_sub_datarefs ? n_sub_datarefs + 1 : 0;

            grow_sub_datarefs_array();

            dref_slot = &sub_datarefs[next_free_slot];
        }

        // At this point, a dataref slot is always available
        size_t dref_len = strlen(dref);
        *dref_slot = malloc((dref_len + 1) * sizeof(char));
        strncpy(*dref_slot, dref, dref_len);

        dref_slot[dref_len] = 0;
    }
}

void compact_sub_datarefs() {
    int has_gaps = 0; // Should we compact?
    size_t n_datarefs = n_sub_datarefs && sub_datarefs[0]; // Number of real datarefs

    for(size_t i = 1; i < n_sub_datarefs; ++i) {
        if(sub_datarefs[i]) {
            n_datarefs++;

            if(!n_sub_datarefs[i - 1]) {
                has_gaps = 1;
            }
        }
    }

    if(has_gaps) {
        // Needs to be compacted
        char **old_sub_datarefs = sub_datarefs;
        size_t old_n_sub_datarefs = n_sub_datarefs;

        sub_datarefs = malloc(sizeof(char *) * (n_datarefs / DREF_CHUNK_SZ + (n_datarefs % DREF_CHUNK_SZ > 0) * DREF_CHUNK_SZ));
        n_sub_datarefs = n_datarefs;

        for(size_t i = 0, j = 0; i < old_n_sub_datarefs; ++i) {
            if(old_sub_datarefs[i]) {
                sub_datarefs[j++] = old_sub_datarefs[i];
            }
        }
    }
}

void remove_sub_dref(const char * const dref) {
    for(size_t i = 0; i < n_sub_datarefs; ++i) {
        if(sub_datarefs[i] && !strcmp(dref, sub_datarefs[i])) {
            free(sub_datarefs[i]);
            sub_datarefs[i] = NULL;
        }
    }
}

int is_dref_subscribed(const char * const dref) {
    for(size_t i = 0; i < n_sub_datarefs; ++i) {
        if(sub_datarefs[i] && !strcmp(dref, sub_datarefs[i])) {
            return 1;
        }
    }

    return 0;
}

void free_sub_drefs() {
    for(size_t i = 0; i < n_sub_datarefs; ++i) {
        if(sub_datarefs[i]) {
            free(sub_datarefs[i]);
        }
    }

    if(sub_datarefs) {
        free(sub_datarefs);
        n_sub_datarefs = 0;
    }
}
