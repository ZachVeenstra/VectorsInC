#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/**
 * This is meant to check if a vector is valid or not, so that a
 * function will know how to handle a NULL pointer.
 * 
 * @param vec The address of the vector we wish to retrieve from.
 * @return true if the vector is valid
 * @return false if the vector is invalid
 */
static bool isValid(lite_vector* vec) {
    return vec != NULL;
}


lite_vector* lv_new_vec(size_t type_size){
    
    // allocate memory for the vector
    lite_vector* vector = malloc(sizeof(*vector));
    
    // if malloc did not error
    if (vector != NULL) { 
        
        // no initial elements, so length is 0
        vector->length = 0; 

        // the amount the vector can initially hold
        vector->max_capacity = 100; 
        
        // an uneccassary variable to confuse us
        vector->type_size = type_size; 
        
        // allocate enough memory for the max capacity of the vector
        vector->data = malloc(sizeof(*vector->data)
                            * vector->max_capacity);
    }
    return vector; // returns the vector, or NULL if malloc failed
}


void lv_cleanup(lite_vector* vec){
    if (isValid(vec)) {
        free(vec->data); // free the data in the vector
        free(vec); // let the vector go, it is in a better place now ;_;
    }
}


size_t lv_get_length(lite_vector* vec){

    size_t result = 0; // set to 0, in case vec isn't accessible
    
    // if the vector is accessible
    if (isValid(vec)) { 
        result = vec->length; // get its length
    }
    return result; // the length, or 0 if vec was not accessible
}


bool lv_clear(lite_vector* vec){
 
    bool result = false;

    // if the vector is accessible
    if (isValid(vec)) { 
        vec->length = 0; // reset length
        vec->max_capacity = 100; // reset capacity

        // create a new, empty data holder
        void** temp = malloc(sizeof(*temp) * vec->max_capacity);

        // if malloc allocated new memory
        if (temp != NULL) { 
            free(vec->data); // free the original data in vector
            vec->data = temp; // use new allocated memory
            result = true; // success
        }
    } 
    return result;
}


void* lv_get(lite_vector* vec, size_t index){

    void* result = NULL;

    // if the vector is acessible
    if (isValid(vec)) {
        // if the index is in bounds
        if (index < vec->length) { 
            result = vec->data[index]; // get the data at the index
        }
    }
    return result; // the data at the specified index, or NULL
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

    bool result = false;

    // if the vector is accessible
    if (isValid(vec)) {
        vec->max_capacity *= 1.67; // makes the capacity ~2/3 larger
        
        // use a new, larger space of memory
        void** temp = malloc(sizeof(*temp) * vec->max_capacity);

        // if malloc allocated new memory,
        if (temp != NULL) { 
            // loop over the elements of the vector
            for (int i = 0; i < vec->length; ++i) { 
                // put the data into the larger memory space
                temp[i] = vec->data[i]; 
            }
            free(vec->data); // free the originial data
            vec->data = temp; // use the new, larger capacity data
            result = true; // success
        }
    }
    return result;
}


bool lv_append(lite_vector* vec, void* element){
    
    bool result = false;

    // if the vector is accessible
    if (isValid(vec)) {
        // if the vector isn't full
        if (vec->length < vec->max_capacity) { 
            vec->data[vec->length] = element; // append element
            vec->length++; // and increment the length
            result = true; // success
        }
        // if the vector is full
        else { 
            // if the vector was resized
            if (lv_resize(vec)) { 
                vec->data[vec->length] = element; // append element
                vec->length++; // and increment the length
                result = true; // success
            }
        }
    }
    return result;
}
