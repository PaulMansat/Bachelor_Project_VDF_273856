//
//  main.c
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//



#include "compute_proof.h"




int VDF_Ver(mpz_t x, const mpz_t T, const mpz_t N, mpz_t y, vector* pi) {
    // verify that x and y are in QR
    
    mpz_t x_next;
    mpz_t y_next;
    mpz_t mu_current;
    mpz_t temp;
    mpz_t T_next;
    mpz_t r;
    mpz_inits(x_next, y_next, mu_current, temp, T_next, r, NULL);
    
    // set x_next to x ... same for y and T_next
    mpz_set(x_next, x);
    mpz_set(y_next, y);
    mpz_set(T_next, T);
    
    // check that x and y are in QR+
    if ( (check_quatratic_residue(x, N) == 1) || (check_quatratic_residue(y, N) == 1) ) return 1;
    
    for (int i = 0; i < pi->size; ++i) {
        if(mpz_odd_p(T) > 0) mpz_add_ui(T_next, T_next, 1);
        mpz_cdiv_q_ui(T_next, T_next, 2);
        
        // get the mu_current from the proof vector
        vector_get(pi, i, mu_current);
        
        // check that mu_i is in QR+
        if ( check_quatratic_residue(mu_current, N) == 1) return 1;
        
        // compute the exponent r
        hash_function(x_next, T_next, y_next, mu_current, r);
        
        //**********************
        // COMPUTATION OF X AND Y TO BE CHECKED
        //**********************
        
        // computation of x_next
        mpz_powm(x_next, x_next, r, N);
        mpz_mul(x_next, x_next, mu_current);
        
        // computation of y_next
        mpz_powm(temp, mu_current, r, N);
        mpz_mul(y_next, y_next, temp);
        
        // comparaison of y_next and x_next
        if(mpz_odd_p(T) > 0) mpz_mul(y_next, y_next, y_next);
        
    }
    
    mpz_t x_next_square;
    mpz_init(x_next_square);
    mpz_mul(x_next_square, x_next, x_next);
    mpz_mod(x_next_square, x_next_square, N);
    
    if( mpz_cmp(y_next, x_next_square ) == 0 ) return 0;
    else return 1;
}

void VDF_Sol(mpz_t x, mpz_t T, mpz_t y, mpz_t N, vector* pi) {

    compute_power_2T(x, T, N, y);
    //printf("%lu \n", mpz_get_ui (y));
    
    mpz_mod (y, y, N);
    
    //printf("%lu \n", mpz_get_ui (T));
    compute_proof_brute_force(x, y, pi, T, N);
    
}

void VDF_Sol_opt(mpz_t x, mpz_t T, mpz_t y, mpz_t N, vector* pi, vector* saves, mpz_t step) {
    mpz_t x_square;
    mpz_init(x_square);
    mpz_mul(x_square, x, x);
    
    // TO DO
    /*
    compute_power_2T_opt(x, T, N, saves, <#const __mpz_struct *exp_space_between_value#>, <#__mpz_struct *out#>)
    squaring_sol_opt(x, T, y, N, x_square, saves, step);
    //printf("%lu \n", mpz_get_ui (y));
    
    mpz_mod (y, y, N);
    
    //printf("%lu \n", mpz_get_ui (T));
    mpz_t initial_e_x;
    mpz_init_set_ui(initial_e_x, 1);
    mpz_t initial_e_mu;
    mpz_init_set_ui(initial_e_mu, 1);
    mpz_t step_power;
    mpz_init(step_power);
    shift_left(initial_e_x, step, step_power); // we give e_x because equal to 1 but could be any mpz number equal to 1
    
    
    compute_proof_opt(x, y, x, pi, T, N, initial_e_x, initial_e_mu, saves, step_power);
     */
}



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
