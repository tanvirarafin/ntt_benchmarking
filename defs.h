// Copyright IBM Inc. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0
// updated by Dr. Tanvir Arafin



#ifndef NTT_EXPERIMENTS_DEFS_H
#define NTT_EXPERIMENTS_DEFS_H
#include <stddef.h>
#include <stdint.h>

#define WORD_SIZE             64UL
#if WORD_SIZE == 64
#  define WORD_SIZE_MASK (-1UL)
#else
#  define WORD_SIZE_MASK ((1UL << WORD_SIZE) - 1)
#endif

#define SUCCESS 0
#define ERROR   (-1)

#define HIGH_WORD(x) ((x) >> WORD_SIZE)
#define LOW_WORD(x)  ((x)&WORD_SIZE_MASK)

// Check whether N=2^m where m is odd by masking it.
#define ODD_POWER_MASK  0xaaaaaaaaaaaaaaaa
#define REM1_POWER_MASK 0x2222222222222222
#define REM2_POWER_MASK 0x4444444444444444
#define REM3_POWER_MASK 0x8888888888888888

#define HAS_AN_EVEN_POWER(n) (!((n)&ODD_POWER_MASK))
#define HAS_AN_REM1_POWER(n) ((n)&REM1_POWER_MASK)
#define HAS_AN_REM2_POWER(n) ((n)&REM2_POWER_MASK)
#define HAS_AN_REM3_POWER(n) ((n)&REM3_POWER_MASK)

#define GUARD_MSG(func, msg) \
  {                          \
    if(SUCCESS != (func)) {  \
      printf(msg);           \
      return ERROR;          \
    }                        \
  }
#define GUARD(func)         \
  {                         \
    if(SUCCESS != (func)) { \
      return ERROR;         \
    }                       \
  }

#if defined(__GNUC__) && (__GNUC__ >= 8)
#  define GCC_SUPPORT_UNROLL_PRAGMA
#endif

#ifdef GCC_SUPPORT_UNROLL_PRAGMA
#  define LOOP_UNROLL_2 _Pragma("GCC unroll 2")
#  define LOOP_UNROLL_4 _Pragma("GCC unroll 4")
#  define LOOP_UNROLL_8 _Pragma("GCC unroll 8")
#elif defined(__clang__)
#  define LOOP_UNROLL_2 _Pragma("clang loop unroll_count(2)")
#  define LOOP_UNROLL_4 _Pragma("clang loop unroll_count(4)")
#  define LOOP_UNROLL_8 _Pragma("clang loop unroll_count(8)")
#else
#  define LOOP_UNROLL_2
#  define LOOP_UNROLL_4
#  define LOOP_UNROLL_8
#endif

#define ALIGN(n) __attribute__((aligned(n)))
#endif //NTT_EXPERIMENTS_DEFS_H
