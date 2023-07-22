
#include "test_speed.h"
#include "ntt_reference.h"
#include <string.h>
void test_fwd_single_case(const test_case_t *t)
{
    const uint64_t n = t->n;
    const uint64_t q = t->q;

    // We use a_cpy to reset a after every NTT call.
    // This is especially important when dealing with the lazy evaluation functions
    // To avoid overflowing and therefore slowdowns of VMSL.
    uint64_t a[n];
    uint64_t a_cpy[n];
    random_buf(a, n, q);
    memcpy(a_cpy, a, sizeof(a));

    MEASURE(fwd_ntt_ref_harvey(a, n, q, t->w_powers.ptr, t->w_powers_con.ptr));
}

void test_inv_perf(const test_case_t *t)
{
    const uint64_t n = t->n;
    const uint64_t q = t->q;

    printf("m = %lu q = %lu cpu_cycles =", t->m, t->q);

    // We use a_cpy to reset a after every NTT call.
    // This is especially important when dealing with the lazy evaluation functions
    // To avoid overflowing and therefore slowdowns of VMSL.
    uint64_t a[n];
    uint64_t a_cpy[n];
    random_buf(a, n, q);
    memcpy(a_cpy, a, sizeof(a));

    MEASURE(inv_ntt_ref_harvey(a, n, q, t->n_inv, WORD_SIZE, t->w_inv_powers.ptr,
                               t->w_inv_powers_con.ptr));
    printf("\n");
}

void report_test_fwd_perf_headers(void)
{
    printf("fwd   pass\n");
    printf("--------------------------------------\n");
}

static inline void test_fwd_perf(const test_case_t *t,
                                 uint64_t *         a,
                                 uint64_t *         b,
                                 const uint64_t *   a_cpy)
{
    const uint64_t q = t->q;
    const uint64_t n = t->n;

    printf("m = %lu q = %lu cpu_cycles = ", t->m, t->q);

    MEASURE(fwd_ntt_ref_harvey(a, n, q, t->w_powers.ptr, t->w_powers_con.ptr));
    memcpy(a, a_cpy, n * sizeof(uint64_t));
    printf("\n");
}

void test_aligned_fwd_perf(const test_case_t *t)
{
    const uint64_t n = t->n;
    const uint64_t q = t->q;

    // We use a_cpy to reset a after every NTT call.
    // This is especially important when dealing with the lazy evaluation functions
    // To avoid overflowing and therefore slowdowns of VMSL.
    ALIGN(64) uint64_t a[n];
    ALIGN(64) uint64_t b[n];
    ALIGN(64) uint64_t a_cpy[n];
    random_buf(a, n, q);
    memcpy(a_cpy, a, sizeof(a));
    memcpy(b, a, sizeof(a));

    test_fwd_perf(t, a, b, a_cpy);
}

void report_test_inv_perf_headers(void)
{
    printf("inv pass \n");
    printf("------------------------------------------------------\n");
}
