/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_zero(struct libj2_j2i *res);


#else

int
main(void)
{
	struct libj2_j2i value = {1, 2};

	libj2_j2i_zero(&value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 0);

	libj2_j2i_zero(&value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 0);

	return 0;
}

#endif
