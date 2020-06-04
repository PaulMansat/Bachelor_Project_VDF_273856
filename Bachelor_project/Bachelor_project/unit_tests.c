//
//  unit_tests.c
//  Bachelor_project
//
//  Created by Paul Mansat on 21.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//




#include "unit_tests.h"


unsigned long int s_prime1 = 5;
unsigned long int s_prime2 = 7;

// #################################################################################################
// HELPER METHODS TESTS
//#################################################################################################
void compute_power_2T_test (void) {
    mpz_t x;
    mpz_t N;
    mpz_t out;
    mpz_inits (x, N, out, NULL);
    
    mpz_set_ui (x, 5);
    mpz_set_ui (N, s_prime1*s_prime2);
    unsigned long int T1 = 4;
    compute_power_2T (x, T1, N, out);
    unsigned long int res = mpz_get_ui (out);
    unsigned long int expected_res = (unsigned long int) pow(5, 16) % (s_prime1*s_prime2);
    if (expected_res == res) {
        printf("Green : compute_power_2T working \n");
    } else {
        printf("Red : compute_power_2T not working \n");
    }
}

void compute_power_2T_opt_test (void) {
    mpz_t x;
    mpz_t N;
    mpz_t out;
    mpz_inits (x, N, out, NULL);
    
    mpz_set_ui (x, 5);
    mpz_set_ui (N, s_prime1*s_prime2);
    unsigned long int T1 = 4;
    
    vector saves;
    construct_vector(&saves);
    
    compute_power_2T_opt(x, T1, N, &saves, out);
    
    unsigned long int res = mpz_get_ui (out);
    unsigned long int expected_res = (unsigned long int) pow(5, 16) % (s_prime1*s_prime2);
    
    mpz_t save1;
    mpz_t save2;
    mpz_inits(save1, save2, NULL);
    
    unsigned long int save1_expected = (unsigned long int) pow(5, 4) % (s_prime1*s_prime2);
    unsigned long int save2_expected = (unsigned long int) pow(5, 16) % (s_prime1*s_prime2);

    vector_get(&saves, 0, save1);
    vector_get(&saves, 1, save2);
    


    if (expected_res == res && mpz_get_ui(save1) == save1_expected && mpz_get_ui(save2) == save2_expected) {
        printf("Green : compute_power_2T_opt working \n");
    } else {
        printf("Red : compute_power_2T_opt not working \n");
    }
}

void compute_s_parameter_test (void) {
    if (6 == compute_s_parameter(pow(2, 25), 100)) {
        printf("Green : compute_s_parameter working \n");
    } else {
        printf("Red : compute_s_parameter not working \n");
    }
}

void exponentiation_for_proof_test (void) {
    mpz_t x;
    mpz_t N;
    mpz_t out;
    mpz_inits (x, N, out, NULL);
    
    mpz_set_ui (x, 5);
    mpz_set_ui (N, s_prime1*s_prime2);
    unsigned long int T1 = 4;
    
    vector saves;
    construct_vector(&saves);
    
    compute_power_2T_opt(x, T1, N, &saves, out);
    
    mpz_t exp1;
    mpz_t exp2;
    mpz_t exp3;
    mpz_t exp4;
    mpz_t exp5;
    mpz_t exp6;
    mpz_init_set_ui(exp1, 3);
    mpz_init_set_ui(exp2, 4);
    mpz_init_set_ui(exp3, 6);
    mpz_init_set_ui(exp4, 16);
    mpz_init_set_ui(exp5, 23);
    mpz_init_set_ui(exp6, 129);
    
    
    unsigned long int exp_res1 = (unsigned long int) pow(5, 3) % (s_prime1*s_prime2);
    unsigned long int exp_res2 = (unsigned long int) pow(5, 4) % (s_prime1*s_prime2);
    unsigned long int exp_res3 = (unsigned long int) pow(5, 6) % (s_prime1*s_prime2);
    unsigned long int exp_res4 = (unsigned long int) pow(5, 16) % (s_prime1*s_prime2);
    unsigned long int exp_res5 = 10;
    unsigned long int exp_res6 = 20;
    
    mpz_t res1;
    mpz_t res2;
    mpz_t res3;
    mpz_t res4;
    mpz_t res5;
    mpz_t res6;
    mpz_inits(res1, res2, res3, res4, res5, res6, NULL);

    exponentiation_for_proof(x, T1, N, exp1, &saves, res1);
    printf("expected 1 is : %lu \n", exp_res1);
    printf("save 1 is : %lu \n", mpz_get_ui(res1));
    exponentiation_for_proof(x, T1, N, exp2, &saves, res2);
    printf("expected 2 is : %lu \n", exp_res2);
    printf("save 2 is : %lu \n", mpz_get_ui(res2));
    exponentiation_for_proof(x, T1, N, exp3, &saves, res3);
    printf("expected 3 is : %lu \n", exp_res3);
    printf("save 3 is : %lu \n", mpz_get_ui(res3));
    exponentiation_for_proof(x, T1, N, exp4, &saves, res4);
    printf("expected 4 is : %lu \n", exp_res4);
    printf("save 4 is : %lu \n", mpz_get_ui(res4));
    exponentiation_for_proof(x, T1, N, exp5, &saves, res5);
    printf("expected 5 is : %lu \n", exp_res5);
    printf("save 5 is : %lu \n", mpz_get_ui(res5));
    exponentiation_for_proof(x, T1, N, exp6, &saves, res6);
    printf("expected 6 is : %lu \n", exp_res6);
    printf("save 6 is : %lu \n", mpz_get_ui(res6));
    
    
   
    


    
    if (exp_res1 == mpz_get_ui(res1) && exp_res2 == mpz_get_ui(res2) && exp_res3 == mpz_get_ui(res3)
        && exp_res4 == mpz_get_ui(res4) && exp_res5 == mpz_get_ui(res5)
        && exp_res6 == mpz_get_ui(res6)) {
        printf("Green : exponentiation_for_proof working \n");
    } else {
        printf("Red : exponentiation_for_proof not working \n");
    }
    
    // do recursive now
}

void greatest_bit_position_test (void) {
    unsigned long int res1 = greatest_bit_position(32);
    unsigned long int res2 = greatest_bit_position(68);
    unsigned long int exp_res1 = 5;
    unsigned long int exp_res2 = 6;
    
    if (res1 == exp_res1 && res2 == exp_res2) {
        printf("Green : greatest_bit_position working \n");
    } else {
        printf("Red : greatest_bit_position not working \n");
    }
}

void test_all_helper (void) {
    compute_power_2T_test();
    compute_power_2T_opt_test();
    exponentiation_for_proof_test();
    greatest_bit_position_test();
}

// #################################################################################################
// COMPUTE PROOF METHODS TESTS
//##################################################################################################
void compute_x_i_test (void) {
    mpz_t x;
    mpz_t mu;
    mpz_t res;
    mpz_t N;
    mpz_t r;
    mpz_inits(x, mu, res, N, r, NULL);
    mpz_set_ui(N, s_prime1*s_prime2);
    mpz_set_ui(mu, 25);
    mpz_set_ui(r, 7);
    mpz_set_ui(x, 5);
    
    compute_x_i(x, mu, res, N, r);
    
    unsigned long int exp_res = (unsigned long int) pow(5, 7) * 25 % (s_prime1*s_prime2);
    
    if (mpz_get_ui(res) == exp_res) {
        printf("Green : compute_x_i working \n");
    } else {
        printf("Red : compute_x_i not working \n");
    }
}

void compute_y_i_test (void) {
    mpz_t y;
    mpz_t mu;
    mpz_t res;
    mpz_t N;
    mpz_t r;
    mpz_inits(y, mu, res, N, r, NULL);
    mpz_set_ui(N, s_prime1*s_prime2);
    mpz_set_ui(mu, 25);
    mpz_set_ui(r, 7);
    mpz_set_ui(y, 5);
    
    compute_y_i(y, mu, res, N, r);
    
    unsigned long int exp_res = (unsigned long int) pow(25, 7) * 5 % (s_prime1*s_prime2);
    
    if (mpz_get_ui(res) == exp_res) {
        printf("Green : compute_y_i working \n");
    } else {
        printf("Red : compute_y_i not working \n");
    }
}

void compute_proof_brute_force_test (void) {
    // computing proof of x^(2^8)
    mpz_t x1;
    mpz_t y1;
    mpz_t T1;
    mpz_t mu1;
    mpz_t r1;
    mpz_inits(x1, y1, T1, mu1, r1, NULL);
    mpz_set_ui(x1, 5);
    mpz_set_ui(y1, 30);
    mpz_set_ui(mu1, 30);
    mpz_set_ui(T1, 8);
    hash_function(x1, T1, y1, mu1, r1);
    
    mpz_t x2;
    mpz_t y2;
    mpz_t T2;
    mpz_t mu2;
    mpz_t r2;
    mpz_inits(x2, y2, T2, mu2, r2, NULL);
    mpz_set_ui(x2, 30);
    mpz_set_ui(y2, 30);
    mpz_set_ui(mu2, 30);
    mpz_set_ui(T2, 4);
    hash_function(x2, T2, y2, mu2, r2);
    
    mpz_t mu3;
    mpz_init_set_ui(mu3, 25);
    
    vector pi;
    construct_vector(&pi);
    mpz_t N;
    mpz_init_set_ui(N, s_prime2*s_prime1);
    
    compute_proof_brute_force(x1, y1, &pi, 8, N);
    
    mpz_t res1;
    mpz_t res2;
    mpz_t res3;
    mpz_inits(res1, res2, res3, NULL);
    vector_get(&pi, 0, res1);
    vector_get(&pi, 1, res2);
    vector_get(&pi, 2, res3);
    //printf("%d \n", mpz_get_ui(res2));
    //printf("%d \n", mpz_get_ui(mu2));

    
    
    if (mpz_get_ui(res1) == mpz_get_ui(mu1) && mpz_get_ui(res2) == mpz_get_ui(mu2) &&
        mpz_get_ui(res3) == mpz_get_ui(mu3)) {
        printf("Green : compute_proof_brute_force working \n");
    } else {
        printf("Red : compute_proof_brute_force not working \n");
    }
        
}

void compute_proof_opt_test(void) {
    vector saves;
    construct_vector(&saves);
    
    mpz_t x;
    mpz_t y;
    mpz_t N;
    unsigned long int T = 8;
    mpz_inits(x, y, N, NULL);
    mpz_set_ui(x, 5);
    mpz_set_ui(N, s_prime1*s_prime2);
    compute_power_2T_opt(x, T, N, &saves, y);
    
    vector pi;
    construct_vector(&pi);
    
    compute_proof_opt(x, y, &pi, T, N, &saves);
    
    mpz_t res1;
    mpz_t res2;
    mpz_t res3;
    mpz_inits(res1, res2, res3, NULL);
    vector_get(&pi, 0, res1);
    vector_get(&pi, 1, res2);
    vector_get(&pi, 2, res3);
    
    unsigned long int exp_res1 = 30;
    unsigned long int exp_res2 = 30;
    unsigned long int exp_res3 = 25;
    
    if (mpz_get_ui(res1) == exp_res1 && mpz_get_ui(res2) == exp_res2 &&
        mpz_get_ui(res3) == exp_res3) {
        printf("Green : compute_proof_opt working \n");
    } else {
        printf("Red : compute_proof_opt not working \n");
    }

}


void test_all_compute_proof(void) {
    compute_x_i_test();
    compute_y_i_test();
    compute_proof_brute_force_test();
    compute_proof_opt_test();
}


 
