/* Checks each kernel against a scalar loop. Integer-valued floats keep every sum exact. */
#include <stdio.h>

#include "demo.h"

enum { N = 1003 };

int main(void) {
    if (!__builtin_cpu_supports("avx2") || !__builtin_cpu_supports("fma") ||
        !__builtin_cpu_supports("popcnt")) {
        puts("skip: this CPU has no AVX2, FMA or POPCNT");
        return 0;
    }
    float a[N], b[N];
    float dot = 0, sum = 0;
    for (int i = 0; i < N; ++i) {
        a[i] = (float)(i % 7);
        b[i] = (float)(i % 5);
        dot += a[i] * b[i];
        sum += a[i];
    }
    int failures = 0;
#define CHECK(name, got, want)                                            \
    do {                                                                  \
        int ok = (got) == (want);                                         \
        failures += !ok;                                                  \
        printf("%s %s: got %g, want %g\n", ok ? "ok  " : "FAIL", name,    \
               (double)(got), (double)(want));                            \
    } while (0)
    CHECK("dot_avx2 (intrinsics.c)", dot_avx2(a, b, N), dot);
    CHECK("sum_avx (sum.s)", sum_avx(a, N), sum);
    float c[8];
    add8_asm(c, a, b);
    for (int i = 0; i < 8; ++i)
        CHECK("add8_asm (inline_asm.c)", c[i], a[i] + b[i]);
    CHECK("popcount_asm (inline_asm.c)", popcount_asm(0xF0F0F0F0F0F0F0F0u), 32);
    return failures != 0;
}
