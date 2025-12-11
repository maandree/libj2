/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_to_j2u(uintmax_t a, struct libj2_j2u *res);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2u value;

	value = (struct libj2_j2u){1, 2};
	libj2_ju_to_j2u(0, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 0);

	value = (struct libj2_j2u){1, 2};
	libj2_ju_to_j2u(5, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 5);

	value = (struct libj2_j2u){1, 2};
	libj2_ju_to_j2u(10, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 10);

	value = (struct libj2_j2u){1, 2};
	libj2_ju_to_j2u(UINTMAX_MAX, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == UINTMAX_MAX);

	return 0;
}

#endif
