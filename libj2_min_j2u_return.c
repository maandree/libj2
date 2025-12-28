/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline const struct libj2_j2u *libj2_min_j2u_return(const struct libj2_j2u *a, ... /*, NULL */);


#else

CONST int main(void) { return 0; } /* Tested in libj2_min_j2u.c */

#endif
