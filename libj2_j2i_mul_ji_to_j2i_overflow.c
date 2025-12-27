/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_mul_ji_to_j2i_overflow(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res);
/* TODO Add man page */


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_mul_ji.c */

#endif
