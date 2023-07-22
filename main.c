// Copyright IBM Inc. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0
// updated by Dr. Tanvir Arafin

#include <stdio.h>
#include "precompute.h"
#include "test_cases.h"
#include "test_correctness.h"
#include "test_speed.h"
#include "defs.h"


int main() {
    printf("NTT Testing Suite\n");
    init_test_cases();

    int run_correctness_test = 1;

    if (run_correctness_test) {
        for(size_t i = 0; i < NUM_OF_TEST_CASES; i++) {
            printf("Test %2.0lu\n", i);
            if(SUCCESS != test_correctness(&tests[i])) {
                destroy_test_cases();
                return SUCCESS;
            }
        }
    }

    int test_cases_to_run = NUM_OF_TEST_CASES;

    report_test_fwd_perf_headers();
    for(size_t i = 0; i < test_cases_to_run; i++) {
        test_aligned_fwd_perf(&tests[i]);
    }

    report_test_inv_perf_headers();
    for(size_t i = 0; i < test_cases_to_run; i++) {
        test_inv_perf(&tests[i]);
    }

    return 0;
}
