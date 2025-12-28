/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_mul_j2i_to_j2i_overflow_p(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res, int *res_set);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_mul_j2i.c */

#endif
