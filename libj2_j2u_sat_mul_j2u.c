/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_sat_mul_j2u(struct libj2_j2u *a, const struct libj2_j2u *b);
/* TODO Add man pages
 * libj2_j2u_sat_mul_j2u
 * libj2_j2u_sat_mul_j2u_destructive
 * libj2_j2u_sat_mul_j2u_to_j2u
 * libj2_j2u_sat_mul_ju
 * libj2_j2u_sat_mul_ju_to_j2u
 * libj2_ju_sat_mul_j2u_to_j2u
 */


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_mul_j2u_destructive.c */

#endif
