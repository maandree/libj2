/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_test_ju(const struct libj2_j2u *a, uintmax_t b);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2u a;
	uintmax_t h, i, j;

	for (h = 0; h < 10; h++) {
		a.high = h;
		for (i = 0; i < 128; i++) {
			a.low = i;
			for (j = 0; j < 128; j++) {
				if (i & j)
					EXPECT(libj2_j2u_test_ju(&a, j) == 1);
				else
					EXPECT(libj2_j2u_test_ju(&a, j) == 0);
				EXPECT(a.high == h);
				EXPECT(a.low == i);
			}
		}
	}

	return 0;
}

#endif
