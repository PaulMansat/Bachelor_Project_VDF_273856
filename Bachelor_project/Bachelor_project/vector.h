//
//  vector.h
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <gmp.h>

typedef struct {
    size_t size;
    unsigned int allocated;
    mpz_t * content;
} vector;

vector* construct_vector(vector* v);

void destruct_vector(vector* v);

vector* create_vector(void);

void delete_vector(vector* v);

vector* enlarge_vector(vector* v);

size_t vector_push(vector* vect, mpz_t val);

int vector_set(vector* vect, size_t pos, mpz_t val);

void vector_get(vector* vect,size_t pos, mpz_t out);

#endif /* vector_h */
