// Copyright IBM Inc. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0
// updated by Dr. Tanvir Arafin



#ifndef NTT_EXPERIMENTS_FAST_MUL_OPERATORS_H
#define NTT_EXPERIMENTS_FAST_MUL_OPERATORS_H
#include "defs.h"

typedef struct mul_op_s {
    __uint128_t op;
    __uint128_t con;
} mul_op_t;

#ifndef L_HIGH_WORD
#  define L_HIGH_WORD HIGH_WORD
#endif
static inline uint64_t reduce_2q_to_q(const uint64_t val, const uint64_t q)
{
    return (val < q) ? val : val - q;
}

static inline uint64_t reduce_4q_to_2q(const uint64_t val, const uint64_t q)
{
    return (val < 2 * q) ? val : val - 2 * q;
}

static inline uint64_t reduce_4q_to_q(const uint64_t val, const uint64_t q)
{
    return reduce_2q_to_q(reduce_4q_to_2q(val, q), q);
}

static inline uint64_t
fast_mul_mod_q2(const mul_op_t w, const uint64_t t, const uint64_t q)
{
    const uint64_t Q = L_HIGH_WORD(w.con * t);
    return w.op * t - Q * q;
}
static inline uint64_t
fast_mul_mod_q(const mul_op_t w, const uint64_t t, const uint64_t q)
{
    return reduce_2q_to_q(fast_mul_mod_q2(w, t, q), q);
}


static inline void
harvey_fwd_butterfly(uint64_t *X, uint64_t *Y, const mul_op_t w, const uint64_t q)
{
    const uint64_t q2 = q << 1;
    const uint64_t X1 = reduce_4q_to_2q(*X, q);
    const uint64_t T  = fast_mul_mod_q2(w, *Y, q);

    *X = X1 + T;
    *Y = X1 - T + q2;
}

static inline void
harvey_bkw_butterfly(uint64_t *X, uint64_t *Y, const mul_op_t w, const uint64_t q)
{
    const uint64_t q2 = q << 1;
    const uint64_t X1 = reduce_4q_to_2q(*X + *Y, q);
    const uint64_t T  = *X - *Y + q2;

    *X = X1;
    *Y = fast_mul_mod_q2(w, T, q);
}

static inline void harvey_bkw_butterfly_final(uint64_t *     X,
                                              uint64_t *     Y,
                                              const mul_op_t w,
                                              const mul_op_t n_inv,
                                              const uint64_t q)
{
    const uint64_t q2 = q << 1;
    const uint64_t X1 = *X + *Y;
    const uint64_t T  = *X - *Y + q2;

    *X = fast_mul_mod_q(n_inv, X1, q);
    *Y = fast_mul_mod_q(w, T, q);
}

#endif //NTT_EXPERIMENTS_FAST_MUL_OPERATORS_H
