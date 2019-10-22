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
void string_to_mpz(const char chars[],  int chars_len, mpz_t binary_representation, int lambda_param);

/*
 * Function:  sha256_string
 * --------------------
 *  helper function of the function hash_function.
 *  all the openssl methods where implemented in this method.
 *
 *  string: the data on which we a hash will be computed
 *  output_buffer: the table where the hash is to be saved
 */
void sha256_string(char *string, char outputBuffer[65]);


/*
 * Function:  hash_function
 * --------------------
 *  computes a hash given the input of the VDF.
 *  The hash functon used is SHA256. 
 *
 *  x_i: the current value x_i computed during the proof
 *  T: the current value of T/2^i
 *  y_i: the current value y_i computed during the proof
 *  u_i: the current value y_i computed during the proof
 *  out: result of the hash
 */
void hash_function(const mpz_t x_i, const mpz_t T, const mpz_t y_i, const mpz_t u_i, mpz_t out);
   
#endif /* hash_function_h */
