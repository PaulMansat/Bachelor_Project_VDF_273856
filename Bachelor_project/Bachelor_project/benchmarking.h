//
//  benchmarking.h
//  Bachelor_project
//
//  Created by Paul Mansat on 06.11.19.
//  Copyright © 2019 Paul Mansat. All rights reserved.
//

#ifndef benchmarking_h
#define benchmarking_h

#include <stdio.h>
#include <time.h>
#include "unit_tests.h"

void benchmark_multiplication_bruteforce (void);

void benchmark_multiplication_opt (void);

void benchmark_proof_bruteforce (void);

void benchmark_proof_opt (void);

void benchmark_both_proof (void);



#endif /* benchmarking_h */
