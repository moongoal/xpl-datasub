#include <stdlib.h>
#include <string.h>
#include "dsarray.h"

void alloc_array(DSArray * const array, const size_t elem_size, const size_t len, array_free_f const free_function) {
    array->ptr = malloc(elem_size * len);
    array->elem_size = elem_size;
    array->len = len;
    array->free_function = free_function;
}

void resize_array(DSArray* const array, const size_t new_array_len) {
    if(array->free_function && new_array_len < array->len) {
        // Need to free some items
        for(size_t i = array->len - new_array_len; i < array->len; ++i) {
            array->free_function(array + i * array->elem_size, array->elem_size);
        }
    } else if(new_array_len == array->len) {
        return;
    }

    array->ptr = realloc(array->ptr, new_array_len * array->elem_size);

    if(new_array_len > array->len) {
        memset(array->ptr + array->len * array->elem_size, 0, (new_array_len - array->len) * array->elem_size);
    }

    array->len = new_array_len;
}

void free_array(DSArray* const array) {
    if(array->ptr) {
        if(array->free_function) {
            // Finalize each element

            for(size_t i = 0; i < array->len; ++i) {
                array->free_function(array + i * array->elem_size, array->elem_size);
            }
        }

        free(array->ptr);
        array->ptr = NULL;
        array->len = 0;
    }
}
