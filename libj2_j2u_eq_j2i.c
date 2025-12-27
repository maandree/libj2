/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_eq_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_cmp_j2i.c */

#endif
