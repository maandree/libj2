/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_max(struct libj2_j2i *res);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2i value = {1, 2};

	libj2_j2i_max(&value);
	EXPECT(value.high == (uintmax_t)INTMAX_MAX);
	EXPECT(value.high == UINTMAX_MAX >> 1);
	EXPECT(value.low == UINTMAX_MAX);

	libj2_j2i_max(&value);
	EXPECT(value.high == (uintmax_t)INTMAX_MAX);
	EXPECT(value.low == UINTMAX_MAX);

#ifdef TODO /* requires libj2_j2i_add_ji */
	libj2_j2i_add_ji(&value, 1);
	EXPECT(libj2_j2i_is_min(&value));
#endif

	return 0;
}

#endif
