/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_sat_add_j2u(struct libj2_j2u *a, const struct libj2_j2u *b);
/* TODO Add man pages
 * libj2_j2u_sat_add_j2u
 * libj2_j2u_sat_add_j2u_to_j2u
 * libj2_j2u_sat_add_ju
 * libj2_j2u_sat_add_ju_to_j2u
 * libj2_ju_sat_add_j2u_to_j2u
 */


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_add_j2u.c */

#endif
