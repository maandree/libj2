/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_div_j2i_underflow(struct libj2_j2i *a, const struct libj2_j2i *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_divmod_j2i_to_j2i.c */

#endif
