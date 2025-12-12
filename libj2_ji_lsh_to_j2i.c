/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ji_lsh_to_j2i(intmax_t a, unsigned b, struct libj2_j2i *res);
/* TODO Add man page */


#else

CONST int main(void) { return 0; }
/* TODO test libj2_ji_lsh_to_j2i, libj2_ji_lsh_to_j2i_overflow, libj2_ji_lsh_overflow_p */

#endif
