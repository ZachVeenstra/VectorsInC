#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

lite_vector* lv_new_vec(size_t type_size){
    lite_vector* vector = malloc(sizeof(lite_vector)); //allocate memory for the vector
    if (vector != NULL) { //if malloc did not error
        vector->length = 0; //the vector doesn't have any elements, so length is 0
        vector->max_capacity = 10; //an arbitrary amount
        vector->type_size = type_size; //an uneccassary variable to confuse us
        vector->data = malloc(sizeof(*vector->data) * vector->max_capacity); //allocate enough memory for the max capacity
    }
    return vector; //returns the vector, or NULL if malloc failed
}

void lv_cleanup(lite_vector* vec){
    free(vec->data); //free the data in the vector
    free(vec); //set the vector free, it is in a better place now ;_;
}

size_t lv_get_length(lite_vector* vec){
    if (vec != NULL) { //if the vector is accessible
        return vec->length; //get its length
    }
    return 0; //the vector wasn't accessible
}

bool lv_clear(lite_vector* vec){
    if (vec != NULL) { //if the vector is accessible
        vec->length = 0; //reset length
        vec->max_capacity = 100; //reset capacity
        void** temp = malloc(sizeof(*temp) * vec->max_capacity);
        if (temp != NULL) { //if malloc allocated new memory
            free(vec->data); //free the original data in vector
            vec->data = temp; //use new allocated memory
            return true; //success
        }
        free(temp);
    }
    return false; //the vector wasn't accessible or malloc errored
}

void* lv_get(lite_vector* vec, size_t index){
    if (index < vec->length) { //if the index is in bounds
        return vec->data[index]; //get the data at the index
    }
    return NULL; //index out of bounds
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
    vec->max_capacity *= 1.67; //makes the capacity ~2/3 larger
    void** temp = malloc(sizeof(*temp) * vec->max_capacity); //create a new, larger space of memory
    if (temp != NULL) { //if malloc allocated new memory,
        for (int i=0;i<vec->length;++i) { //loop over the vector
            temp[i] = vec->data[i]; //and put the data into the larger memory space
            if (temp[i] != vec->data[i]) { //and check if the data was copied in that loop
                return false; //the data wasn't copied`
            }
        }
        free(vec->data);
        vec->data = temp; //use the new, larger capacity data
        return true;
    }
    return false;
}

bool lv_append(lite_vector* vec, void* element){
    if (vec->length < vec->max_capacity) { //if the vector isn't full
        vec->data[vec->length] = element; //append element
        vec->length++; //and increment the length
        return true;
    }
    else { //if the vector is full
        if (lv_resize(vec)) { //attempt a resize
            vec->data[vec->length] = element; //and append element
            vec->length++; //and increment the length
            return true;
        }
        else { //resize failed
            return false;
        }
    }
}
