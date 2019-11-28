//
//  benchmarking.c
//  Bachelor_project
//
//  Created by Paul Mansat on 06.11.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#include "benchmarking.h"

void benchmark_multiplication_bruteforce(void) {
    mpz_t x;
    mpz_t N;
    mpz_t out;
    mpz_inits(x, N, out, NULL);
    mpz_set_ui(x, 450003);
    mpz_set_str(N, "622508016097411244439761737392416325553332376060386097641057707287735055303924775370444497742993919891589684328516458697581692371705394041823221085279874642396220161984177201792600246913045294001429059109375816432086923550995143584650550477", 10);
    
    // creation of the csv file to save result
    char * filename = "bruteforce_multiplication.csv";
    printf("Creating %s file \n",filename);
    FILE *fp;
    
    fp=fopen(filename,"w+");
    clock_t time;

    fprintf(fp,"sub_exponent,time");
    for (int t = 20; t < 21; t++){
        unsigned long int T = pow(2, t);
        fprintf(fp,"\n%lu",T);
        
        time = clock();
        compute_power_2T(x, T, N, out);
        time = clock() - time;
        printf("time is %f\n", (double) time/CLOCKS_PER_SEC);

        fprintf(fp,",%lu",time);
        
    }
    fclose(fp);
    
    printf("%s file created \n",filename);
}

void benchmark_multiplication_opt(void) {
    mpz_t x;
    mpz_t N;
    mpz_t out;
    mpz_inits(x, N, out, NULL);
    mpz_set_ui(x, 350003);
    mpz_set_str(N, "622508016097411244439761737392416325553332376060386097641057707287735055303924775370444497742993919891589684328516458697581692371705394041823221085279874642396220161984177201792600246913045294001429059109375816432086923550995143584650550477", 10);
    
    // creation of the csv file to save result
    char * filename = "opt_multiplication.csv";
    printf("Creating %s file \n",filename);
    FILE *fp;
    
    fp=fopen(filename,"w+");
    
    fprintf(fp,"sub_exponent, time");
    for (int t = 0; t < 30; t++){
        unsigned long int T = pow(2, t);
        fprintf(fp,"\n%lu",T);
        vector saves;
        construct_vector(&saves);
        
        clock_t time;
        time = clock();
        compute_power_2T_opt(x, T, N, &saves, out);
        time = clock() - time;
        printf("time is %lu \n", time);

        double time_taken = ((double)time);
        
        fprintf(fp,",%f ",time_taken);
        
    }
    fclose(fp);

    
    printf("%s file created \n",filename);
}

void benchmark_proof_bruteforce (void) {
    mpz_t x;
    mpz_t N;
    mpz_t y;
    mpz_inits(x, N, y, NULL);
    mpz_set_ui(x, 350003);
    mpz_set_str(N, "622508016097411244439761737392416325553332376060386097641057707287735055303924775370444497742993919891589684328516458697581692371705394041823221085279874642396220161984177201792600246913045294001429059109375816432086923550995143584650550477", 10);
    
    // creation of the csv file to save result
    char * filename = "bruteforce_proof.csv";
    printf("Creating %s file \n",filename);
    FILE *fp;
    
    fp=fopen(filename,"w+");
    
    fprintf(fp,"sub_exponent,time");
    for (int t = 13; t < 30; t++){
        printf("at iteration : %d \n", t);
        unsigned long int T = pow(2, t);
        compute_power_2T(x, T, N, y);
        mpz_mod (y, y, N);
        vector pi;
        construct_vector(&pi);

        fprintf(fp,"\n%lu",T);
        
        clock_t time;
        time = clock();
        compute_proof_brute_force(x, y, &pi, T, N);
        time = clock() - time;
        
        fprintf(fp,",%lu ",time);
        
    }
    fclose(fp);
    
    printf("%s file created \n",filename);
}

void benchmark_proof_opt (void) {
    mpz_t x;
    mpz_t N;
    mpz_t y;
    mpz_inits(x, N, y, NULL);
    mpz_set_ui(x, 350003);
    mpz_set_str(N, "622508016097411244439761737392416325553332376060386097641057707287735055303924775370444497742993919891589684328516458697581692371705394041823221085279874642396220161984177201792600246913045294001429059109375816432086923550995143584650550477", 10);
    
    // creation of the csv file to save result
    char * filename = "opt_proof.csv";
    printf("Creating %s file \n",filename);
    FILE *fp;
    
    fp=fopen(filename,"w+");
    
    fprintf(fp,"sub_exponent,time");
    for (int t = 13; t < 30; t++){
        printf("at iteration : %d \n", t);
        unsigned long int T = pow(2, t);
        vector saves;
        construct_vector(&saves);
        compute_power_2T_opt(x, T, N, &saves, y);
        mpz_mod (y, y, N);
        vector pi;
        construct_vector(&pi);
        
        fprintf(fp,"\n%lu",T);
        
        clock_t time;
        time = clock();
        compute_proof_opt(x, y, &pi, T, N, &saves);
        time = clock() - time;
        
        fprintf(fp,",%lu ",time);
        
    }
    fclose(fp);
    
    printf("%s file created \n",filename);

}

void benchmark_both_proof (void) {
    mpz_t x;
    mpz_t N;
    mpz_t y;
    mpz_inits(x, N, y, NULL);
    mpz_set_ui(x, 123456);
    mpz_set_str(N, "16158503035655503650357438344334975980222051334857742016065172713762327569433945446598600705761456731844358980460949009747059779575245460547544076193224141560315438683650498045875098875194826053398028819192033784138396109321309878080919047169238085235290822926018152521443787945770532904303776199561965642282844350721009131075592574364243695880618860889291860118718196676371399528079340206559035126612674866232053943452084332329067399812414572508105263197679145256552814549607319534463349117382246918962235483023376108551954504056221074590325455782931366628146267643957799255048569835849362555689794934167531092723509", 10);
    
    // creation of the csv file to save result
    char * filename_opt = "opt_proof.csv";
    printf("Creating %s file \n",filename_opt);
    FILE *fp_opt;
    
    fp_opt=fopen(filename_opt,"w+");
    
    fprintf(fp_opt,"T,time");
    
    char * filename_brute = "bruteforce_proof.csv";
    printf("Creating %s file \n",filename_brute);
    FILE *fp_brute;
    
    fp_brute=fopen(filename_brute,"w+");
    
    fprintf(fp_brute,"T,time");
    
    char * filename_mul = "multiplication.csv";
    printf("Creating %s file \n",filename_mul);
    FILE *fp_mul;
    
    fp_mul=fopen(filename_mul,"w+");
    fprintf(fp_mul,"T,time");

    
    
    for (int t = 13; t < 30; t++){
        printf("at iteration : %d \n", t);
        unsigned long int T = pow(2, t);
        vector saves;
        construct_vector(&saves);
        
        // Compute mul
        fprintf(fp_mul,"\n%lu",T);
        
        clock_t time_mul;
        time_mul = clock();
        compute_power_2T_opt(x, T, N, &saves, y);
        time_mul = clock() - time_mul;
        
        fprintf(fp_mul,",%f ", (double) time_mul/CLOCKS_PER_SEC);

        
        
        mpz_mod (y, y, N);
        vector pi_opt;
        construct_vector(&pi_opt);
        vector pi_brute;
        construct_vector(&pi_brute);
        
        // Compute proof optimized version
        fprintf(fp_opt,"\n%lu",T);
        
        clock_t time_opt;
        time_opt = clock();
        compute_proof_opt(x, y, &pi_opt, T, N, &saves);
        time_opt = clock() - time_opt;
        
        fprintf(fp_opt,",%f ", (double) time_opt/CLOCKS_PER_SEC);
        
        // Compute proof brute force version
        fprintf(fp_brute,"\n%lu",T);

        clock_t time_brute;
        time_brute = clock();
        compute_proof_brute_force(x, y, &pi_brute, T, N);
        time_brute = clock() - time_brute;
        
        fprintf(fp_brute,",%f ", (double) time_brute/CLOCKS_PER_SEC);

        
    }
    fclose(fp_opt);
    fclose(fp_brute);
    
    printf("%s file created \n",filename_opt);
    printf("%s file created \n",filename_brute);

}

