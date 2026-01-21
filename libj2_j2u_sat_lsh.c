/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_sat_lsh(struct libj2_j2u *a, unsigned b);
/* TODO Add man pages
 * libj2_j2u_sat_lsh
 * libj2_j2u_sat_lsh_to_j2u
 * libj2_ju_sat_lsh_to_j2u
 */


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_lsh.c */

#endif
