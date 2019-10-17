//
//  vector.c
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int VECTOR_PADDING = 50;

/*
 Function that allocated the necessary memory to the vectors.
 It is usually called in create_vector;
 */
vector* construct_vector(vector* v) {
    vector* result;
    result = v;
    if(result != NULL) {
        result->content = calloc(VECTOR_PADDING, sizeof(mpz_t));
        if(result->content != NULL) {
            result->size = 0;
            result->allocated = VECTOR_PADDING;
        } else {
            result = NULL;
        }
    }
    return result;
}

void destruct_vector(vector* v){
    if(v != NULL){
        if(v->content != NULL) {
            free(v->content);
            v->content = NULL;
            v->size = v->allocated = 0;
        }
    }
}

/*
 Function that creates a vector and returns it
 */
vector* create_vector(void){
    vector* v = malloc(sizeof(vector));
    if(v != NULL) {
        if(construct_vector(v) == NULL) {
            free(v);
            v = NULL;
        }
    }
    return v;
}

void delete_vector(vector* v){
    if(v != NULL){
        destruct_vector(v);
        free(v);
    }
}

vector* enlarge_vector(vector* v){
    vector* result = v;
    if (result != NULL) {
        mpz_t* const old_content = result->content;
        result->allocated += VECTOR_PADDING;
        if( (result->content = realloc(result->content, result->allocated*sizeof(mpz_t))) == NULL)  {
            result->content = old_content;
            result->allocated -= VECTOR_PADDING;
            result = NULL;
        }
    }
    return result;
}

/*
 Insert a new element in the vector and return the new size of the vector. If the insertion failed, returns 0
 */
size_t vector_push(vector* vect, mpz_t val){
    if (vect != NULL) {
        while (vect->size >= vect->allocated) {
            if (enlarge_vector(vect) == NULL) {
                return 0;
            }
        }
        mpz_init_set(vect->content[vect->size], val);
        ++(vect->size);
        return vect->size;
    }
    return 0;
}

/*
 Insert an element at pos and return 1 if it succeeded, else return 0
 */
int vector_set(vector* vect, size_t pos, mpz_t val) {
    if (vect != NULL) {
        if (pos >= vect->size) vect->size = pos+1;
        while (vect->size >= vect->allocated) {
            if (enlarge_vector(vect) == NULL) {
                return 0;
            }
        }
        mpz_set(vect->content[pos], val);
        return 1;
    }
    return 0;
}

/*
 Returns the mpz_t vector at pos. The result is savec into the variable out
 */
void vector_get(vector* vect,size_t pos, mpz_t out){
    if (vect != NULL) {
        if (pos < vect->size) {
            mpz_set(out, vect->content[pos]);
        }
    }
}
