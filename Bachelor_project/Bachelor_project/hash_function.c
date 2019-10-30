//
//  hash_function.c
//  Bachelor_project
//
//  Created by Paul Mansat on 17.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "hash_function.h"

//#################################################################################################
void string_to_mpz(const char chars[],  int chars_len, mpz_t binary_representation, int lambda_param) {
    
    if(chars == NULL) {
        return;
    }
    
    mpz_t res;
    mpz_init(res);
    int number_chars_used = lambda_param / 8 + lambda_param % 8;
    mpz_t temp;
    mpz_init(temp);
    
    int counter = 0;
    
    for (int i = 0; i < number_chars_used; ++i) {
        for(int j = 0; j < 8; j++) {
            if (chars[i] & 1 << j) {
                mpz_ui_pow_ui(temp, 2, counter);
                mpz_add(res, res, temp);
            }
            ++counter;
        }
    }
    mpz_set(binary_representation, res);
    return;
}

//#################################################################################################
void sha256_string(char *string, char outputBuffer[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

//#################################################################################################
void hash_function(const mpz_t x_i, const mpz_t T, const mpz_t y_i, const mpz_t u_i, mpz_t out) {
    // FIRST  : get the hash value
    
    // mpz_get_str -> IT WILL BE THE ONE WE WILL BE USING
    // SIZE OF THE STRING mpz_sizeinbase (op, base) + 2

    // we set lambda to be 80 bits
    

    
    
    char* x_data = mpz_get_str(NULL, 10, x_i);

    char* T_data = mpz_get_str(NULL, 10, T);

    char* y_data = mpz_get_str(NULL, 10, y_i);

    char* u_data = mpz_get_str(NULL, 10, u_i);

    
    size_t total_data_size = strlen(x_data) + strlen(T_data) + strlen(y_data) + strlen(u_data) + 1;
    
    char data[total_data_size];
    strcpy(data, "a");
    strcat(data, x_data);
    strcat(data, T_data);
    strcat(data, y_data);
    strcat(data, u_data);
    
    char outputBuffer[65] = "";

    sha256_string(data, outputBuffer);

    
    string_to_mpz(outputBuffer, 65, out, 64);
    
    
    return;
}
