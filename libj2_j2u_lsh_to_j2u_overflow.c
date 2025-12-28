/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_lsh_to_j2u_overflow(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_lsh.c */

#endif
