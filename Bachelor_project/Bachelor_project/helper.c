//
//  helper.c
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "helper.h"

const unsigned long int STEP = 8;

//#################################################################################################
void compute_exponentiation(mpz_t x, const mpz_t exp, const mpz_t N, mpz_t out) {
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
void compute_power_2T (mpz_t x, const unsigned long int T, const mpz_t N, mpz_t out){
    if (T == 0) {
        mpz_set(out, x);
    } else {
        mpz_t exp;
        mpz_init(exp);
        mpz_setbit(exp, T);
        mpz_powm(out, x, exp, N);
    }
}

//#################################################################################################
void compute_power_2T_opt (mpz_t x, const unsigned long int T, const mpz_t N, vector* saves, mpz_t out) {
    unsigned long int power_2STEP = pow(2, STEP);
    unsigned long int exp_space_between_values = T/power_2STEP;
    
    mpz_t res;
    mpz_init(res);
    compute_power_2T(x, exp_space_between_values, N, res);
    vector_push(saves, res);
    
    for (int i = 0; i < power_2STEP - 1; ++i) {
        compute_power_2T(res, exp_space_between_values, N, res);
        if ( !vector_push(saves, res) ) {
            printf("Unable to save intermediate computation");
        }
    }
    mpz_set(out, res);
}


//#################################################################################################
void exponentiation_for_proof (const mpz_t x, unsigned long int T, mpz_t N, mpz_t exp, vector* saves, mpz_t out) {
    
    unsigned long int power_2STEP = pow(2, STEP);
    unsigned long int exp_space_between_values = T/power_2STEP;
    unsigned long int number_ones = mpz_popcount(exp);
    mpz_t exp_copy;
    mpz_init_set(exp_copy, exp);
  
    mpz_t res;
    mpz_init_set_ui(res, 1);
    
    for (unsigned long int i = 0 ; i < number_ones ; ++i) {
        unsigned long int q = mpz_sizeinbase(exp_copy, 2) - 1;
        
        
        if (q < exp_space_between_values) {
            mpz_t temp;
            mpz_init(temp);
            mpz_powm(temp, x, exp_copy, N);
            mpz_mul(res, res, temp);
            break;
        } else {
            mpz_t saved_value;
            mpz_init(saved_value);
            mpz_clrbit(exp_copy, q);
            //exponentiation_for_proof(x, T, N, exp_copy, saves, rest);
            
            unsigned long int k = q/exp_space_between_values;
            unsigned long int rest_exp = q % exp_space_between_values;
            
            if (k <= power_2STEP) { //|| (k == power_2STEP && mpz_cmp_ui(exp_copy, 0) == 0)) {
                if (k <= saves->size) {
                    vector_get(saves, k - 1, saved_value);
                    
                } else {
                    printf("Index given too big, unable to reach correct saved value. \n");
                }
            } else {
                unsigned long int alpha = k/power_2STEP;
                unsigned long int beta = k % power_2STEP;
                
                vector_get(saves, power_2STEP - 1, saved_value);
                compute_power_2T(saved_value, T*(alpha -1), N, saved_value);
                compute_power_2T(saved_value, exp_space_between_values * beta, N, saved_value);
                
            }
            compute_power_2T(saved_value, rest_exp, N, saved_value);
            
            mpz_mul(res, res, saved_value);
        }

    }
    mpz_mod(out, res, N);

    return;

}
/*void exponentiation_for_proof (const mpz_t x, unsigned long int T, mpz_t N, mpz_t exp, vector* saves, mpz_t out) {
    
    unsigned long int power_2STEP = pow(2, STEP);
    unsigned long int exp_space_between_values = T/power_2STEP;
    mpz_t exp_copy;
    mpz_init_set(exp_copy, exp);
    unsigned long int q = mpz_sizeinbase(exp, 2) - 1;

    
    if (q < exp_space_between_values) {
        mpz_powm(out, x, exp, N);
        return;
    } else {
        mpz_t rest;
        mpz_t saved_value;
        mpz_inits(rest, saved_value, NULL);
        mpz_clrbit(exp_copy, q);
        mpz_powm(rest, x, exp_copy, N);
        //exponentiation_for_proof(x, T, N, exp_copy, saves, rest);

        unsigned long int k = q/exp_space_between_values;
        unsigned long int rest_exp = q % exp_space_between_values;

        if (k <= power_2STEP) { //|| (k == power_2STEP && mpz_cmp_ui(exp_copy, 0) == 0)) {
            if (k <= saves->size) { 
                vector_get(saves, k - 1, saved_value);

            } else {
                printf("Index given too big, unable to reach correct saved value. \n");
            }
        } else {
            unsigned long int alpha = k/power_2STEP;
            unsigned long int beta = k % power_2STEP;

            vector_get(saves, power_2STEP - 1, saved_value);
            compute_power_2T(saved_value, T*(alpha -1), N, saved_value);
            compute_power_2T(saved_value, exp_space_between_values * beta, N, saved_value);

        }
        compute_power_2T(saved_value, rest_exp, N, saved_value);

        mpz_mul(out, rest, saved_value);
        mpz_mod(out, out, N);
        return;
    }
    
}*/

//#################################################################################################
int check_quatratic_residue(const mpz_t var, const mpz_t N) {
    if( (var < 0) && (mpz_jacobi(var, N) != 1) )  {
        return 1;

    } else {
       return 0;
    }
}

//#################################################################################################
unsigned long int greatest_bit_position(unsigned long int num) {
    if (num == 0) {
        printf("Num is zero, greatest bit doesn't exists");
        return 0;
    }
    unsigned long int m;
    m = num;
    m = m | m >> 1;
    m = m | m >> 2;
    m = m | m >> 4;
    m = m | m >> 8;
    m = m | m >> 16;
    m = m | m >> 32;
    m = m & ((~m >> 1)); //^0x8000000000000000);

    unsigned long int res = 0;
    
    while ( m != 0) {
        m = m >> 1;
        res++;
    }
    return res - 1 ;

}
