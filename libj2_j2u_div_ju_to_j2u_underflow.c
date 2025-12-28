/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_div_ju_to_j2u_underflow(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_divmod_j2u_to_j2u.c */

#endif
