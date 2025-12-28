/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_mul_ji_overflow(struct libj2_j2i *a, intmax_t b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_mul_ji.c */

#endif
