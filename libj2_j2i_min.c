/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_min(struct libj2_j2i *res);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2i value = {1, 2};

	libj2_j2i_min(&value);
	EXPECT(value.high == (uintmax_t)INTMAX_MAX + 1U);
	EXPECT(value.low == 0);

	libj2_j2i_min(&value);
	EXPECT(value.high == (uintmax_t)INTMAX_MAX + 1U);
	EXPECT(value.low == 0);

	libj2_j2i_add_ji(&value, -1);
	EXPECT(libj2_j2i_is_max(&value));

	return 0;
}

#endif
