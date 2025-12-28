/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ju_lsh_to_j2u_overflow(uintmax_t a, unsigned b, struct libj2_j2u *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_ju_lsh_to_j2u.c */

#endif
