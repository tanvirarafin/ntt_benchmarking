// Copyright IBM Inc. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0
// updated by Dr. Tanvir Arafin



#ifndef NTT_EXPERIMENTS_NTT_REFERENCE_H
#define NTT_EXPERIMENTS_NTT_REFERENCE_H

#include "defs.h"
#include "fast_mul_operators.h"

void fwd_ntt_ref_harvey_lazy(uint64_t       a[],
                             const uint64_t N,
                             const uint64_t q,
                             const uint64_t w[],
                             const uint64_t w_con[]);
static inline void fwd_ntt_ref_harvey(uint64_t       a[],
                                      const uint64_t N,
                                      const uint64_t q,
                                      const uint64_t w[],
                                      const uint64_t w_con[])
{
    fwd_ntt_ref_harvey_lazy(a, N, q, w, w_con);

    // Final reduction
    for(size_t i = 0; i < N; i++) {
        a[i] = reduce_4q_to_q(a[i], q);
    }
}

void inv_ntt_ref_harvey(uint64_t       a[],
                        const uint64_t N,
                        const uint64_t q,
                        const mul_op_t n_inv,
                        const uint64_t word_size,
                        const uint64_t w[],
                        const uint64_t w_con[]);
#endif //NTT_EXPERIMENTS_NTT_REFERENCE_H
