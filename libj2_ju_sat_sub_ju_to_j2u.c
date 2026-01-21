/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_sat_sub_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_ju_sub_ju_to_j2u.c */

#endif
