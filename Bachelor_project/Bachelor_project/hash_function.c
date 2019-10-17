//
//  hash_function.c
//  Bachelor_project
//
//  Created by Paul Mansat on 17.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "hash_function.h"

//#################################################################################################
void string_to_mpz(const unsigned char chars[],  int chars_len, mpz_t binary_representation, int lambda_param) {
    if(chars == NULL) {
        return;
    }
    
    int number_chars_used = lambda_param / 8 + lambda_param % 8;
    
    mpz_t temp;
    mpz_init(temp);
    
    int counter = 0;
    
    for (int i = 0; i < number_chars_used; ++i) {
        for(int j = 0; j < 8; j++) {
            if (chars[i] & 1 << j) {
                mpz_ui_pow_ui(temp, 2, counter);
                mpz_add(binary_representation, binary_representation, temp);
            }
            ++counter;
        }
    }
    
    return;
}

//#################################################################################################
void hash_function(const mpz_t x_i, const mpz_t T, const mpz_t y_i, const mpz_t u_i, mpz_t out) {
    // FIRST  : get the hash value
    
    // mpz_get_str -> IT WILL BE THE ONE WE WILL BE USING
    // SIZE OF THE STRING mpz_sizeinbase (op, base) + 2

    // we set lambda to be 80 bits
    
    
    size_t x_data_size = __gmpz_sizeinbase(x_i, 10);
    size_t T_data_size = __gmpz_sizeinbase(y_i, 10);
    size_t y_data_size =__gmpz_sizeinbase(T, 10);
    size_t u_data_size = __gmpz_sizeinbase(u_i, 10);
    size_t total_data_size = x_data_size + T_data_size + y_data_size + u_data_size + 1;
    
    char x_data[x_data_size];
    char T_data[T_data_size];
    char y_data[y_data_size];
    char u_data[u_data_size];
    mpz_get_str(x_data, 10, x_i);
    mpz_get_str(T_data, 10, T);
    mpz_get_str(y_data, 10, y_i);
    mpz_get_str(u_data, 10, u_i);
    
    unsigned char data[total_data_size];
    strcpy(data, "a");
    strcat(data, x_data);
    strcat(data, T_data);
    strcat(data, y_data);
    strcat(data, u_data);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(data, total_data_size, hash);
    //printf("%s \n", hash);
    
    
    string_to_mpz(hash, SHA256_DIGEST_LENGTH, out, 64);
    
    return;
}
