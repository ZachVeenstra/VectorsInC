#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size){
    lite_vector* vector = malloc(sizeof(lite_vector)); //allocate memory for the vector
    vector->length = 0; //the vector doesn't have any elements, so length is 0
    vector->max_capacity = 100; //an arbitrary amount
    vector->type_size = type_size; //an uneccassary variable to confuse us
    vector->data = malloc(sizeof(vector->data) * vector->max_capacity); //allocate enough memory for the max capacity
    return vector; //TODO: return null upon failure
}

void lv_cleanup(lite_vector* vec){
    free(vec->data); //free the data in the vector
    free(vec); //set the vector free, it is in a better place now ;_;
}

size_t lv_get_length(lite_vector* vec){
    return vec->length; //TODO: if this fails, return 0
}

bool lv_clear(lite_vector* vec){
    free(vec->data);
    free(vec);

    return true; //TODO: check if memory can be freed before return.
}

void* lv_get(lite_vector* vec, size_t index){
    if (index < vec->length) {
        return vec->data[index];
    }
    return NULL;
}

/**
 * lv_resize is essentially private since we marked it static.
 * The job of this function is to attempt to resize the vector.
 * There may be functions you can call to do this for you, or
 * you may write it yourself.  Either way it isn't too hard.
 * With everything though, check to make sure the code worked
 * and return appropriately.  Do NOT destroy the data if the code
 * fails.  If the resize cannot complete, the original vector
 * must remain unaffected.
 */
static bool lv_resize(lite_vector* vec){
    return true;
}

bool lv_append(lite_vector* vec, void* element){
    return true;
}
