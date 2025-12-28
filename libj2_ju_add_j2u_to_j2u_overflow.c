/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ju_add_j2u_to_j2u_overflow(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_add_ju.c */

#endif
