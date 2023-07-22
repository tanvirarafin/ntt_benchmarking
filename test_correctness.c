// Copyright IBM Inc. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0
// updated by Dr. Tanvir Arafin



#include "test_cases.h"
#include "ntt_reference.h"
#include "defs.h"
#include <string.h>
#include <stdio.h>

void write_data(const uint64_t a[], const uint64_t n, const uint64_t q, const unsigned int fwd){
    printf("Writing data to ");
    FILE *fp = NULL;
    char fname[100];
    snprintf(fname, sizeof(fname), "results/%lu_%lu_%d_data.txt", n, q, fwd );
    printf("%s \n", fname);
    if ((fp = fopen(fname, "w+")) == NULL) {
        printf("Cannot find results directory. Please create one in the build folder");
        exit(1);
    };

    fprintf(fp, "%lu \n", n);
    fprintf(fp, "%lu \n", q);
    for(uint64_t i = 0; i < n; ++i){
        //printf("%lu \n", a[i]);
        fprintf(fp, "%lu \n", a[i]);
    }
    fclose(fp);
}

static inline int test_radix2_scalar(const test_case_t *t, uint64_t a_orig[])
{
    uint64_t a[t->n];
    memcpy(a, a_orig, sizeof(a));

    printf("Running fwd_ntt_ref_harvey\n");
    printf("Param values are n = %lu, q = %lu \n", t->n, t->q);
    write_data(a, t->n, t->q, 1);
    fwd_ntt_ref_harvey(a, t->n, t->q, t->w_powers.ptr, t->w_powers_con.ptr);

    printf("Running inv_ntt_ref_harvey\n");
    write_data(a, t->n, t->q, 0);
    inv_ntt_ref_harvey(a, t->n, t->q, t->n_inv, WORD_SIZE, t->w_inv_powers.ptr,
                       t->w_inv_powers_con.ptr);


    GUARD_MSG(memcmp(a_orig, a, sizeof(a)), "Bad results after radix-2 inv\n");

    return SUCCESS;
}

int test_correctness(const test_case_t *t)
{
    // Prepare input
    uint64_t a[t->n];
    uint64_t b[t->n];
    uint64_t a_ntt[t->n];
    uint64_t a_cpy[t->n];
    random_buf(a, t->n, t->q);
    memcpy(a_cpy, a, sizeof(a));
    memcpy(b, a, sizeof(a));

    // Prepare a_ntt = NTT(a)
    fwd_ntt_ref_harvey(a_cpy, t->n, t->q, t->w_powers.ptr, t->w_powers_con.ptr);
    memcpy(a_ntt, a_cpy, sizeof(a_cpy));

    GUARD(test_radix2_scalar(t, a));
    return SUCCESS;
}