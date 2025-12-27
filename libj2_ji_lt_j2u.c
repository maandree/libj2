/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ji_lt_j2u(intmax_t a, const struct libj2_j2u *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_cmp_ji.c */

#endif
