/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_rdivmod_j2u_to_j2u(struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res_q);


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2u_divmod_j2u_to_j2u.c */

#endif
