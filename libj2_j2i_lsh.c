/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_lsh(struct libj2_j2i *a, unsigned b);
/* TODO Add man page */


#else

CONST int main(void) { return 0; }
/* TODO test libj2_j2i_lsh{,_to_j2i}{,_overflow}, libj2_j2i_lsh_overflow_p */

#endif
