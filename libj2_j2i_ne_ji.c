/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_ne_ji(const struct libj2_j2i *a, intmax_t b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_cmp_ji.c */

#endif
