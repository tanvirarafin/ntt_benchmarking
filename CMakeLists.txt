cmake_minimum_required(VERSION 3.15)
project(ntt_experiments C)

set(CMAKE_C_STANDARD 99)

add_executable(ntt_experiments main.c ntt_reference.c ntt_reference.h defs.h fast_mul_operators.h test_cases.h precompute.h test_correctness.c test_correctness.h measurements.h test_speed.h test_speed.c)
