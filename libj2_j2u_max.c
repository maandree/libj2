/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_max(struct libj2_j2u *res);


#else

int
main(void)
{
	struct libj2_j2u value = {1, 2};

	libj2_j2u_max(&value);
	EXPECT(~value.high == 0);
	EXPECT(~value.low == 0);

	libj2_j2u_max(&value);
	EXPECT(~value.high == 0);
	EXPECT(~value.low == 0);

	libj2_j2u_add_ju(&value, 1U);
	EXPECT(libj2_j2u_is_zero(&value));

	return 0;
}

#endif
