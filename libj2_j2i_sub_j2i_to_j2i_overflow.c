/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_sub_j2i_to_j2i_overflow(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_sub_j2i.c */

#endif
