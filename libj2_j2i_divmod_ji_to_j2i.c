/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_divmod_ji_to_j2i(struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res_q);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_divmod_j2i_to_j2i.c */

#endif
