/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_abs_diff_j2u(struct libj2_j2u *a, const struct libj2_j2u *b);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_abs_diff_j2u_to_j2u */

#endif
