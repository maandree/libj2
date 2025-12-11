/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_abs_j2i(struct libj2_j2i *a);
/* TODO Add man page */


#else

CONST int main(void) { return 0; }
/* TODO test libj2_abs_j2i{,_to_j2i,_to_j2u} libj2_minus_abs_j2i{,_to_j2i} */

#endif
