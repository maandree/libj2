/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_rsub_j2u_borrow(struct libj2_j2u *a, const struct libj2_j2u *b, int *borrow);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_sub_j2u.c */

#endif
