//
//  hash_function.h
//  Bachelor_project
//
//  Created by Paul Mansat on 17.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#ifndef hash_function_h
#define hash_function_h

#include <openssl/sha.h>
#include "helper.h"



/*
 * Function:  string_to_mpz
 * --------------------
 *  converts a hash value (i.e a string) to a mpz number of lambda_param bits
 *
 *  chars[]: the hash produced by SHA258
 *  chars_len: the size of the hash produced by SHA258
 *  binary_representation: the result of the converstion of the chars[] to its binary representation
 *  lambda: numbers of bits we want @binary_representation to be
 */
void string_to_mpz(const unsigned char chars[],  int chars_len, mpz_t binary_representation, int lambda_param);

/*
 * Function:  compute_x_i
 * --------------------
 *  computes the value of x_(i+1) = x^r * mu_i
 *
 *  x_i: the current value x_i computed during the proof
 *  T: the current value of T/2^i
 *  y_i: the current value y_i computed during the proof
 *  u_i: the current value y_i computed during the proof
 *  out: result of the hash
 */
void hash_function(const mpz_t x_i, const mpz_t T, const mpz_t y_i, const mpz_t u_i, mpz_t out);
   
#endif /* hash_function_h */
