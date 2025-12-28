/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ji_rsh_underflow_p(intmax_t a, unsigned b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_ji_rsh_to_j2i.c */

#endif
