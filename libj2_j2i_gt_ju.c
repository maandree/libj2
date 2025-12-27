/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_gt_ju(const struct libj2_j2i *a, uintmax_t b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_cmp_ju.c */

#endif
