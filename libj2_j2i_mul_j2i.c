/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_mul_j2i(struct libj2_j2i *a, const struct libj2_j2i *b);
/* TODO Add man page */


#else

CONST int main(void) { return 0; }
/* TODO test libj2_j2i_mul_j2i, libj2_j2i_mul_j2i_to_j2i_overflow_p_quick, libj2_j2i_mul_j2i_to_j2i_overflow_p, libj2_j2i_mul_j2i_to_j2i_overflow, libj2_j2i_mul_j2i_overflow_p_quick, libj2_j2i_mul_j2i_overflow_p, libj2_j2i_mul_j2i_overflow */

#endif
