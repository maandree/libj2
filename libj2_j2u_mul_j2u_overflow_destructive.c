/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_mul_j2u_overflow_destructive(struct libj2_j2u *restrict a /*result */, struct libj2_j2u *restrict b /*destructed */);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_mul_j2u_destructive.c */

#endif
