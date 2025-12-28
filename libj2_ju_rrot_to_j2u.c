/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_rrot_to_j2u(uintmax_t a, unsigned b, struct libj2_j2u *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_ju_lrot_to_j2u.c */

#endif
