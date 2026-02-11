/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_sat_lsh_to_j2i(const struct libj2_j2i *a, unsigned b, struct libj2_j2i *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_lsh.c */

#endif
