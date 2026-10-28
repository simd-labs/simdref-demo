#pragma once
#include <stddef.h>
#include <stdint.h>

float dot_avx2(const float *a, const float *b, size_t n);   /* intrinsics.c */
void add8_asm(float *dst, const float *a, const float *b);  /* inline_asm.c */
uint64_t popcount_asm(uint64_t x);                          /* inline_asm.c */
float sum_avx(const float *x, size_t n);                    /* sum.s */
