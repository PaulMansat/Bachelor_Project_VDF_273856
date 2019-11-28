//
//  main.c
//  Bachelor_project
//
//  Created by Paul Mansat on 16.10.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//



#include "benchmarking.h"

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
    //printf("VERIFIER \n");
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
        mpz_set_ui(r, 0);
        vector_get(pi, i, mu);
        
        
        //printf("-------- \n");
        //printf("mu in ver computation : %lu \n", mpz_get_ui(mu));
        //printf("exponent in ver computation : %lu \n", mpz_get_ui(exp_mpz));
         
        
        if (check_quatratic_residue(mu, N) == 1) return 0;
       
        hash_function(x_next, exp_mpz, y_next, mu, r);

        compute_x_i(x_next, mu, x_next, N, r);
        compute_y_i(y_next, mu, y_next, N, r);
        
        
        //printf("x in ver computation : %lu \n", mpz_get_ui(x_next));
        //printf("y in ver computation : %lu \n", mpz_get_ui(y_next));
        //printf("hash in ver computation : %lu \n", mpz_get_ui(r));
        


        mpz_cdiv_q_ui(exp_mpz, exp_mpz, 2);
    }

    mpz_powm_ui(x_next, x_next, 2, N);
    //printf("%lu \n", mpz_get_ui(x_next));

    //printf("%lu \n", mpz_get_ui(y_next));


    if (mpz_cmp(x_next, y_next) == 0) {
        return 1;
    } else {
        return 0;
    }
    return 0;
}

/*
 * Function:  benchmark_verification
 * --------------------
 *  beznchmarks the verificaiton process.
 *
 *  x: the number that was given to the prover
 *  T: the sub-exponent given to the prover
 *  N: the product of two safe primes
 *  pi: the proof made by the verifier
 *
 *  returns: 0 if the proof is incorrect and 1 if the proof is correct
 */
void benchmark_verification (void) {
    mpz_t x;
    mpz_t N;
    mpz_t y;
    mpz_inits(x, N, y, NULL);
    mpz_set_ui(x, 123456);
    mpz_set_str(N, "16158503035655503650357438344334975980222051334857742016065172713762327569433945446598600705761456731844358980460949009747059779575245460547544076193224141560315438683650498045875098875194826053398028819192033784138396109321309878080919047169238085235290822926018152521443787945770532904303776199561965642282844350721009131075592574364243695880618860889291860118718196676371399528079340206559035126612674866232053943452084332329067399812414572508105263197679145256552814549607319534463349117382246918962235483023376108551954504056221074590325455782931366628146267643957799255048569835849362555689794934167531092723509", 10);
    
    char * filename_ver = "verification.csv";
    printf("Creating %s file \n",filename_ver);
    FILE *fp_ver;
    
    fp_ver=fopen(filename_ver,"w+");
    
    fprintf(fp_ver,"T,time");
    
    for (int t = 13; t < 20; t++){
        printf("at iteration : %d \n", t);
        unsigned long int T = pow(2, t);
        vector saves;
        construct_vector(&saves);
        compute_power_2T_opt(x, T, N, &saves, y);
        mpz_mod (y, y, N);
        vector pi;
        construct_vector(&pi);
        
        compute_proof_opt(x, y, &pi, T, N, &saves);

        fprintf(fp_ver,"\n%lu",T);
        
        clock_t time;
        time = clock();
        VDF_Ver(x, T, N, y, &pi);
        time = clock() - time;
        fprintf(fp_ver,",%f ", (double) time/CLOCKS_PER_SEC);

    }
    fclose(fp_ver);
    
    
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
    //mpz_set_ui(N, 35);
    mpz_set_str(N, "16158503035655503650357438344334975980222051334857742016065172713762327569433945446598600705761456731844358980460949009747059779575245460547544076193224141560315438683650498045875098875194826053398028819192033784138396109321309878080919047169238085235290822926018152521443787945770532904303776199561965642282844350721009131075592574364243695880618860889291860118718196676371399528079340206559035126612674866232053943452084332329067399812414572508105263197679145256552814549607319534463349117382246918962235483023376108551954504056221074590325455782931366628146267643957799255048569835849362555689794934167531092723509", 10);
    unsigned long int T = pow(2,20);
    vector pi;
    construct_vector(&pi);
    
    VDF_Sol(x, T, y, N, &pi);
    if(VDF_Ver(x, T, N, y, &pi)) {
        printf("Green : VDF_Ver working \n");
    } else {
        printf("Red : VDF_Ver not working \n");
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //test_all_helper();
    //test_all_compute_proof();
    //VDF_test();
    
    //benchmark_multiplication_bruteforce();
    //benchmark_multiplication_opt();
    //benchmark_proof_bruteforce();
    //benchmark_proof_opt();
    //benchmark_verification();
    
    //printf("s param is : %lu \n", compute_s_parameter(pow(2, 25), 100));
    //benchmark_both_proof();
    
    
    mpz_t safe_prime;
    mpz_init(safe_prime);
    generate_safeprime(1024, safe_prime);
    
    
    
    /*
    mpz_t N;
    mpz_init(N);
    mpz_set_str(N, "622508016097411244439761737392416325553332376060386097641057707287735055303924775370444497742993919891589684328516458697581692371705394041823221085279874642396220161984177201792600246913045294001429059109375816432086923550995143584650550477", 10);
    int res = 0;
    int prob = mpz_probab_prime_p(N, res);
    printf("Prob. is : %d", prob);
     */
    
    /*
    mpz_t N;
    mpz_init(N);
    mpz_set_str(N, "16158503035655503650357438344334975980222051334857742016065172713762327569433945446598600705761456731844358980460949009747059779575245460547544076193224141560315438683650498045875098875194826053398028819192033784138396109321309878080919047169238085235290822926018152521443787945770532904303776199561965642282844350721009131075592574364243695880618860889291860118718196676371399528079340206559035126612674866232053943452084332329067399812414572508105263197679145256552814549607319534463349117382246918962235483023376108551954504056221074590325455782931366628146267643957799255048569835849362555689794934167531092723509", 10);
    printf("Size of N : %lu", mpz_sizeinbase(N, 2));
    */
    
    /*
    mpz_t safe1;
    mpz_t safe2;
    mpz_t N;
    mpz_inits(safe1, safe2, N, NULL);
    
    mpz_set_str(safe1, "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624225795083", 10);
    mpz_set_str(safe2, "89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812113740223", 10);
    mpz_mul(N, safe1, safe2);
    
    gmp_printf ("%s is an mpz %Zd\n", "here", N);
     */
    
    return 0;
}
