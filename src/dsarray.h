#ifndef DSARRAY_H
#define DSARRAY_H

#include <stdlib.h>

/**
 * Get an element in the array.
 *
 * @param type The type to cast the element to.
 * @param array The array to get the element from.
 * @param index The index in the array where at which the element is located.
 */
#define array_at(type, array, index) (*(type*)array_element_ptr(array, index))

/**
 * Get a pointer to an element in the array.
 *
 * @param array The array to get the element from.
 * @param index The index in the array where at which the element is located.
 */
#define array_element_ptr(array, index) ((array)->ptr + (index) * (array)->elem_size)

/**
 * Definition of empty array.
 */
#define EMPTY_ARRAY { NULL, 0, 0, NULL }

/**
 * Return true if an array is empty, false if not.
 */
#define array_is_empty(array) (!(array)->ptr || !(array)->len)

/**
 * Return the length of an array.
 */
#define array_length(array) ((array)->len)

/**
 * An item finalizer function. A finalizer function is called whenever an array element is finalized.
 *
 * @param elem A pointer to the element to be finalized.
 * @param elem_size Size of the element being finalized.
 */
typedef void (*array_free_f)(void * const elem, const size_t elem_size);

struct DSArray {
  void *ptr;
  size_t elem_size;
  size_t len;
  array_free_f free_function;
};

typedef struct DSArray DSArray;

/**
 * Annotated DsArray type name to show the name of the element type.
 */
#define DSArrayWithType(elem_type) DSArray

/**
 * Allocate a new array.
 *
 * @param array Pointer to the array object to initialize.
 * @param elem_size The size of the element in the array.
 * @param len The length of the array to be allocated.
 * @param free_function The optional element finalizer function.
 */
void alloc_array(DSArray * const array, const size_t elem_size, const size_t len, array_free_f const free_function);
void resize_array(DSArray* const array, const size_t new_array_len);
void free_array(DSArray* const array);

#endif // DSARRAY_H
