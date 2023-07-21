//
// Created by marafin on 7/21/23.
//

#ifndef NTT_EXPERIMENTS_TEST_SPEED_H
#define NTT_EXPERIMENTS_TEST_SPEED_H
#include "measurements.h"
#include "test_cases.h"


void test_fwd_single_case(const test_case_t *t);
void test_inv_perf(const test_case_t *t);

void report_test_fwd_perf_headers(void);
void test_aligned_fwd_perf(const test_case_t *t);

void report_test_inv_perf_headers(void);

#endif //NTT_EXPERIMENTS_TEST_SPEED_H
