//
//  compute_proof.c
//  Bachelor_project
//
//  Created by Paul Mansat on 17.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "compute_proof.h"

//#################################################################################################
void compute_x_i(mpz_t x_in, mpz_t mu_i, mpz_t x_out, mpz_t N, mpz_t r){
    mpz_powm(x_out, x_in, r, N);
    mpz_mul(x_out, x_out, mu_i);
    mpz_mod(x_out, x_out, N);
}

//#################################################################################################
void compute_y_i(mpz_t y_in, mpz_t mu_i, mpz_t y_out, mpz_t N, mpz_t r) {
    mpz_powm(y_out, mu_i, r, N);
    mpz_mul(y_out, y_out, y_in);
    mpz_mod (y_out, y_out, N);
}

//#################################################################################################
void compute_proof_brute_force(mpz_t x_in, mpz_t y_in, vector* pi, mpz_t T, mpz_t N){
    if (mpz_cmp_d(T, 1) == 0) {
        return;
    }
    
    mpz_t mu_i;
    mpz_t x_out;
    mpz_t y_out;
    mpz_t new_T;
    mpz_t exponent;
    mpz_t r;
    mpz_inits(x_out, y_out, mu_i, new_T, exponent, r, NULL);
    
    
    // computation of the necessary variables mu, x, y
    mpz_set(new_T, T);
    
    if(mpz_odd_p(T) > 0) {
        mpz_add_ui(new_T, new_T, 1);
    }
    
    mpz_cdiv_q_ui(new_T, new_T, 2);
    compute_power_2T(x_in, new_T, N, mu_i);
    vector_push(pi, mu_i);
    
    hash_function(x_in, new_T, y_in, mu_i, r);
    compute_x_i(x_in, mu_i, x_out, N, r);
    compute_y_i(y_in, mu_i, y_out, N, r);
    
    // compute the next step of values
    if (mpz_odd_p(T) > 0) {
        mpz_mul(y_out, y_out, y_out);
    }
    
    compute_proof_brute_force(x_out, y_out, pi, new_T, N);
    
    return;
}

//#################################################################################################
void compute_proof_opt(mpz_t x_in, mpz_t y_in, mpz_t x, vector* pi, mpz_t T, mpz_t N, mpz_t e_x, mpz_t e_mu, vector* saves, mpz_t step_power)  {
    if (mpz_cmp_d(T, 1) == 0) {
        return;
    }
    // don't think its necessary to give e_mu as parameter ...
    mpz_t mu_i;
    mpz_t mu_square;
    mpz_t x_out;
    mpz_t y_out;
    mpz_t new_T;
    mpz_t exponent;
    mpz_t r;
    mpz_t e_y;
    mpz_inits(x_out, y_out, mu_i, mu_square, new_T, exponent, r, e_y, NULL);
    
    // UNDER CONSTRUCTION
    
    // computation of the necessary variables mu, x, y
    
    /*
    mpz_set(new_T, T);
    
    if(mpz_odd_p(T) > 0) mpz_add_ui(new_T, new_T, 1);
    
    mpz_cdiv_q_ui(new_T, new_T, 2);
    
    
    shift_left(e_x, new_T, e_mu);
    squaring_for_proof(x, N, e_mu, saves, step_power, mu_i);
    vector_push(pi, mu_i);
    
    hash_function(x_in, new_T, y_in, mu_i, r);
    
    mpz_mul(e_x, e_x, r);
    squaring_for_proof(x, N, e_x, saves, step_power, x_out);
    mpz_add(e_x, e_x, e_mu);
    mpz_mul(x_out, x_out, mu_i);
    
    mpz_mul(e_y, e_mu, r);
    
    squaring_for_proof(x, N, e_y, saves, step_power, y_out);
    mpz_mul(y_out, y_out, mu_i); // to be checked, but I believe works well until here
    
    // compute the next step of values
    if (mpz_odd_p(T) > 0) mpz_mul(y_out, y_out, y_out);
    
    compute_proof_opt(x_out, y_out, x, pi, new_T, N, e_x, e_mu, saves, step_power);
    */
    return;
}

//#################################################################################################

