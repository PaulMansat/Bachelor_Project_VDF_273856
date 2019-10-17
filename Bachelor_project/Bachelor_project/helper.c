//
//  helper.c
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "helper.h"

const unsigned long int STEP;

//#################################################################################################
void compute_exponentiation(const mpz_t x, const mpz_t exp, const mpz_t N, mpz_t out) {
    // tests if odd or not ?
    // if T > 1, then recursive operations
    if ( mpz_cmp_ui(exp, 1) > 0 ) {
        mpz_t temp;
        mpz_t new_exp;
        mpz_inits(temp, new_exp, NULL);
        
        // If T is odd, compute using T/2-1
        if(mpz_odd_p(exp) > 0) {
            mpz_sub_ui(new_exp, exp, 1);
            mpz_cdiv_q_ui(new_exp, new_exp, 2);
            compute_exponentiation(x, new_exp, N, temp);
            // temp put allready in modulo
            mpz_mul(out,temp,temp);
            mpz_mul(out, out, x);
            
        } else {
            mpz_cdiv_q_ui(new_exp, exp, 2);
            compute_exponentiation(x, new_exp, N, temp);
            mpz_mul(out, temp,temp);
        }
        // if T = 1, do nothing and simply return y = x
    } else {
        mpz_set(out, x);
    }
}

//#################################################################################################
void compute_power_2T (const mpz_t x, const mpz_t T, const mpz_t N, mpz_t out){
    if (mpz_cmp_ui(T, 0) == 0) {
        mpz_set(out, x);
        return;
    } else {
        mpz_t new_T;
        mpz_inits(new_T, NULL);
        mpz_sub_ui(new_T, T, 1);
        compute_power_2T(x, new_T, N, out);
        mpz_mul(out, out, out);
    }
    return;
}

//#################################################################################################
void compute_power_2T_opt (const mpz_t x, const mpz_t T, const mpz_t N, vector* saves, const mpz_t exp_space_between_value, mpz_t out) {
    if (mpz_cmp_ui(T, 0) == 0) {
        mpz_set(out, x);
        return;
    } else {
        mpz_t new_T;
        mpz_t mod;
        mpz_inits(new_T, mod, NULL);
        mpz_sub_ui(new_T, T, 1);
        compute_power_2T_opt(x, new_T, N, saves, exp_space_between_value, out);
        mpz_mul(out, out, out);
        
        // verify if we need to save result or not :
        mpz_mod(mod, T, exp_space_between_value);
        if(mpz_cmp_ui(mod, 0) == 0) {
            vector_push(saves, out);
        }
        
    }
    return;
}

//#################################################################################################
void get_space_between_values (const mpz_t T, mpz_t out) {
    mpz_t divisor;
    unsigned long int divisor_int = pow(2, STEP);
    mpz_init_set_ui(divisor, divisor_int);
    mpz_cdiv_q(out, T, divisor);
}

//#################################################################################################
void exponentiation_for_proof (mpz_t x, mpz_t T, mpz_t N, mpz_t exp, vector* saves, mpz_t exp_space_between_value, mpz_t out) {
    // initialisation of the variables
    mpz_t div;
    mpz_t q;
    mpz_t r;
    mpz_t partial_result;
    unsigned long int sub_exponent;
    mpz_t k;
    unsigned long int k_;
    mpz_inits(div, q, r, partial_result, k, NULL);
    unsigned long int power_2STEP = pow(2, STEP);
    
    
    mp_bitcnt_t exp_space_between_value_ = mpz_get_ui (exp_space_between_value);
    mpz_setbit(div, exp_space_between_value_);
    mpz_cdiv_qr(q, r, exp, div);
    
    /***
     code here :
     ASSUMPTION IS : T IS CODED ON NO MORE THAN 64 BITS
    ***/
    // because we made the assumption that T =< 64 bits, r is less than or equalt to 64 bits and can be conveted to unsigned long without any loss
    unsigned long int r_ = mpz_get_ui(r);
    mpz_pow_ui(partial_result, x, r_);
    mpz_mul(q, q, div);
    sub_exponent = mpz_sizeinbase(q, 2) - 1;
    k_ = sub_exponent / power_2STEP;
    mpz_set_ui(k, k_);
    /***
     code here :
     END OF THE ASSUMPTION
     ***/
    
    if (mpz_cmp_ui(k,power_2STEP) <= 0 ){
        k_ = mpz_get_ui(k);
        if (k_ > saves->size > 0) {
            printf("Invalid Index");
            return;
        }
        vector_get(saves, k_ , out);
    } else {
        mpz_t alpha;
        mpz_t lambda;
        mpz_t temp;
        mpz_t last_x;
        mpz_t partial_exponent_1;
        mpz_t partial_exponent_2;
        mpz_inits(alpha, lambda, temp, last_x, partial_exponent_1, partial_exponent_2, NULL);
        mpz_cdiv_qr_ui(alpha, lambda, k, power_2STEP);
        vector_get(saves, saves->size - 1, last_x);
        mpz_sub_ui(partial_exponent_1, alpha, 1);
        mpz_mul(partial_exponent_1, partial_exponent_1, T);
        compute_power_2T(last_x, partial_exponent_1, N, temp);
        mpz_mul(partial_exponent_2, k, exp_space_between_value);
        compute_power_2T(temp, partial_exponent_2, N, out);
    }
    mpz_mul(out, out, partial_result);
}

//#################################################################################################
int check_quatratic_residue(const mpz_t var, const mpz_t N) {
    if( (var < 0) && (mpz_jacobi(var, N) != 1) )  {
        return 1;

    } else {
       return 0;
    }
}
