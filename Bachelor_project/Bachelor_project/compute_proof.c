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
    mpz_t res;
    mpz_init(res);
    mpz_powm(res, x_in, r, N);
    mpz_mul(x_out, res, mu_i);
    mpz_mod(x_out, x_out, N);
}

//#################################################################################################
void compute_y_i(mpz_t y_in, mpz_t mu_i, mpz_t y_out, mpz_t N, mpz_t r) {
    mpz_t res;
    mpz_init(res);
    mpz_powm(res, mu_i, r, N);
    mpz_mul(y_out, res, y_in);
    mpz_mod (y_out, y_out, N);
}

//#################################################################################################
void compute_proof_brute_force (const mpz_t x, const mpz_t y, vector* pi, unsigned long int T, mpz_t N) {
    printf("PROVER \n");
    unsigned long int t = greatest_bit_position(T);
    printf("T is : %lu \n", T);
    unsigned long int exp = T;
    mpz_t mu;
    mpz_t x_next;
    mpz_t y_next;
    mpz_t exp_mpz;
    mpz_t r;
    mpz_inits(mu, x_next, y_next, r, exp_mpz, NULL);
    mpz_set(x_next, x);
    mpz_set(y_next, y);
    for (int i = 0; i < t; ++ i) {
        mpz_set_ui(r, 0);
        printf("-------- \n");
        mpz_set_d(exp_mpz, exp);
        exp = exp/2;
        compute_power_2T(x_next, exp, N, mu);
        
        printf ("mu in proof comp : %lu \n", mpz_get_ui(mu));
        printf ("exponent in proof comp : %lu \n", mpz_get_ui(exp_mpz));

        hash_function(x_next, exp_mpz, y_next, mu, r);
        compute_x_i(x_next, mu, x_next, N, r);
        compute_y_i(y_next, mu, y_next, N, r);
        printf("x in ver computation : %lu \n", mpz_get_ui(x_next));
        printf("y in ver computation : %lu \n", mpz_get_ui(y_next));
        printf("hash in ver computation : %lu \n", mpz_get_ui(r));

        vector_push(pi, mu);
    }
}

//#################################################################################################
void compute_proof_opt (const mpz_t x, const mpz_t y, vector* pi, unsigned long int T, mpz_t N, vector* saves) {
    
    mpz_t mu;
    mpz_t x_next;
    mpz_t y_next;
    mpz_t exp_mu;
    mpz_t exp_x;
    mpz_t r;
    mpz_t T_mpz;
    mpz_inits(mu, x_next, y_next, exp_mu, exp_x, r, T_mpz, NULL);
    mpz_set(x_next, x);
    mpz_set(y_next, y);
    mpz_set_d(exp_x, 1);
    mpz_set_d(exp_mu, 0);
    mpz_set_ui(T_mpz, T);
    for (unsigned long int i = T/2; i >= 1; i = i/2) {
        //printf("-------- \n");
        mpz_setbit(exp_mu, i);
        mpz_mul(exp_mu, exp_x, exp_mu);
        exponentiation_for_proof(x, T, N, exp_mu, saves, mu);
        
        //printf ("mu in proof comp : %lu \n", mpz_get_ui(mu));
        //printf ("exponent in proof comp : %lu \n", mpz_get_ui(T_mpz));
        
        hash_function(x_next, T_mpz, y_next, mu, r);
        mpz_mul(exp_x, exp_x, r);
        mpz_add(exp_x, exp_x, exp_mu);
        mpz_set_ui(T_mpz, i);
        vector_push(pi, mu);
        compute_x_i(x_next, mu, x_next, N, r);
        compute_y_i(y_next, mu, y_next, N, r);
       
        

        //printf("x in ver computation : %lu \n", mpz_get_ui(x_next));
        //printf("y in ver computation : %lu \n", mpz_get_ui(y_next));
        //printf("hash in ver computation : %lu \n", mpz_get_ui(r));
        mpz_set_ui(exp_mu, 0);
        mpz_set_ui(r, 0);
    }
    
    
    /*if (mpz_cmp_d(T, 1) == 0) {
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
    */
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

