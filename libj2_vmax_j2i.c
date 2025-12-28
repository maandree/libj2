/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_vmax_j2i(struct libj2_j2i *a, va_list args);


#else

CONST int main(void) { return 0; } /* Tested via libj2_max_j2i */

#endif
