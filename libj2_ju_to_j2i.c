/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_to_j2i(uintmax_t a, struct libj2_j2i *res);


#else

int
main(void)
{
	struct libj2_j2i value;

	value = (struct libj2_j2i){1, 2};
	libj2_ju_to_j2i(0, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 0);

	value = (struct libj2_j2i){1, 2};
	libj2_ju_to_j2i(5, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 5);

	value = (struct libj2_j2i){1, 2};
	libj2_ju_to_j2i(10, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == 10);

	value = (struct libj2_j2i){1, 2};
	libj2_ju_to_j2i(UINTMAX_MAX, &value);
	EXPECT(value.high == 0);
	EXPECT(value.low == UINTMAX_MAX);

	return 0;
}

#endif
