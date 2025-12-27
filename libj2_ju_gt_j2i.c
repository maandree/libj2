/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ju_gt_j2i(uintmax_t a, const struct libj2_j2i *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_cmp_ju.c */

#endif
