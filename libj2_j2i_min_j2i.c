/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_min_j2i(struct libj2_j2i *a, const struct libj2_j2i *b);
/* TODO Add man pages
   libj2_j2i_min_j2i
   libj2_j2i_min_j2i_to_j2i
   libj2_j2i_min_ji
   libj2_j2i_min_ji_to_j2i
   libj2_j2u_min_j2u
   libj2_j2u_min_j2u_to_j2u
   libj2_j2u_min_ju
   libj2_j2u_min_ju_to_j2u
 */


#else

CONST int main(void) { return 0; } /* Tested in libj2_j2i_cmp_j2i.c */

#endif
