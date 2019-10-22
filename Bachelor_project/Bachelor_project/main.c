//
//  main.c
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//



#include "unit_tests.h"

/*
 * Function:  VDF_Ver
 * --------------------
 *  checks that the given proof @pi is correct
 *
 *  x: the number that was given to the prover
 *  T: the sub-exponent given to the prover
 *  N: the product of two safe primes
 *  pi: the proof made by the verifier
 *
 *  returns: 0 if the proof is incorrect and 1 if the proof is correct 
 */
int VDF_Ver (mpz_t x, unsigned long T,  mpz_t N, mpz_t y, vector* pi) {
    // verify that x and y are in QR
    if ( (check_quatratic_residue(x, N) == 1) || (check_quatratic_residue(y, N) == 1) ) return 0;

    mpz_t r;
    mpz_t x_next;
    mpz_t y_next;
    mpz_t mu;
    mpz_t exp_mpz;
    mpz_inits (r, x_next, y_next, mu, exp_mpz, NULL);
    mpz_set (x_next, x);
    mpz_set (y_next, y);
    mpz_set_ui(exp_mpz, T);
    
    for (int i = 0; i < pi->size; ++i) {
        vector_get(pi, i, mu);
        if (check_quatratic_residue(mu, N) == 1) return 0;
        hash_function(x_next, exp_mpz, y_next, mu, r);
        compute_x_i(x_next, mu, x_next, N, r);
        compute_y_i(y_next, mu, y_next, N, r);
        mpz_cdiv_q_ui(exp_mpz, exp_mpz, 2);
    }
    
    mpz_mul(x_next, x_next, x_next);
    mpz_mod(x_next, x_next, N);
    
    if (mpz_cmp(x_next, y_next) == 0) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

/*
 * Function:  VDF_Sol
 * --------------------
 *  computes the given challenge (i.e x^(2^T)) and build a proof on the result.
 *  the proof is computed brute force (no previous calculations are re-used).
 *
 *  x: the number that was given to the prover
 *  T: the sub-exponent given to the prover
 *  N: the product of two safe primes
 *  pi: the proof made by the verifier
 */
void VDF_Sol(mpz_t x, unsigned long int T, mpz_t y, mpz_t N, vector* pi) {
    compute_power_2T(x, T, N, y);    
    mpz_mod (y, y, N);
    compute_proof_brute_force(x, y, pi, T, N);
    
}

/*
 * Function:  VDF_Sol_opt
 * --------------------
 *  computes the given challenge (i.e x^(2^T)) and build a proof on the result.
 *  the proof is computed by re-using previously computed results.
 *
 *  x: the number that was given to the prover
 *  T: the sub-exponent given to the prover
 *  N: the product of two safe primes
 *  pi: the proof made by the verifier
 */
void VDF_Sol_opt(mpz_t x, unsigned long int T, mpz_t y, mpz_t N, vector* pi) {
    vector saves;
    construct_vector(&saves);
    compute_power_2T_opt(x, T, N, &saves, y);
    mpz_mod(y, y, N);
    compute_proof_opt(x, y, pi, T, N, &saves);
   
}

/*
 * Function:  VDF_test
 * --------------------
 *  non-exhaustive test of the verifier.
 *  Important note : the test relies on the the prover to compute a correct proof
 */
void VDF_test(void) {
    mpz_t x;
    mpz_t y;
    mpz_t N;
    mpz_inits (x, y, N, NULL);
    mpz_set_ui(x, 5);
    mpz_set_ui(N, 35);
    unsigned long int T = 8;
    vector pi;
    construct_vector(&pi);
    
    
    VDF_Sol_opt(x, T, y, N, &pi);
    if(VDF_Ver(x, T, N, y, &pi)) {
        printf("Green : VDF_Ver working \n");
    } else {
        printf("Red : VDF_Ver not working \n");

    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    test_all_helper();
    test_all_compute_proof();
    VDF_test();
    
    return 0;
}
