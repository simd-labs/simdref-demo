/* Each instruction inside an asm string gets a summary at the end of its line. */
#include "demo.h"

void add8_asm(float *dst, const float *a, const float *b) {
    __asm__ volatile(
        "vmovups (%1), %%ymm0\n\t"
        "vaddps (%2), %%ymm0, %%ymm0\n\t"
        "vmovups %%ymm0, (%0)\n\t"
        "vzeroupper"
        :
        : "r"(dst), "r"(a), "r"(b)
        : "xmm0", "memory");
}

uint64_t popcount_asm(uint64_t x) {
    uint64_t r;
    __asm__("popcnt %1, %0" : "=r"(r) : "r"(x));
    return r;
}
