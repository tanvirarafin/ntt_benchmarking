//
// Created by marafin on 7/21/23.
//

#ifndef NTT_EXPERIMENTS_MEASUREMENTS_H
#define NTT_EXPERIMENTS_MEASUREMENTS_H
#include "defs.h"

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#    define WARMUP        10
#    define OUTER_REPEAT  10
#    define MEASURE_TIMES 200

static double start_clk;
static double end_clk;
static double total_clk;
static double temp_clk;

#    define NANO_SEC (1000000000UL)
static inline uint64_t cpucycles(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * NANO_SEC + ts.tv_nsec;
    ;
}
#    define MEASURE(x)                                                   \
      for(size_t warmup_itr = 0; warmup_itr < WARMUP; warmup_itr++) {    \
        {                                                                \
          x;                                                             \
        }                                                                \
      }                                                                  \
      total_clk = DBL_MAX;                                               \
      for(size_t outer_itr = 0; outer_itr < OUTER_REPEAT; outer_itr++) { \
        start_clk = cpucycles();                                         \
        for(size_t clk_itr = 0; clk_itr < MEASURE_TIMES; clk_itr++) {    \
          {                                                              \
            x;                                                           \
          }                                                              \
        }                                                                \
        end_clk  = cpucycles();                                          \
        temp_clk = (double)(end_clk - start_clk) / MEASURE_TIMES;        \
        if(total_clk > temp_clk) total_clk = temp_clk;                   \
      }                                                                  \
      printf("%9.0lu ", (uint64_t)total_clk);

#endif //NTT_EXPERIMENTS_MEASUREMENTS_H
