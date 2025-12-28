/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ji_mul_j2i_overflow_p(intmax_t a, const struct libj2_j2i *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_mul_ji.c */

#endif
