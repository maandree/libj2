/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline enum libj2_overflow libj2_ju_mul_j2u_overflow_p_quick(uintmax_t a, const struct libj2_j2u *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_mul_ju.c */

#endif
