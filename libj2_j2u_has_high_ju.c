/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_has_high_ju(const struct libj2_j2u *a, uintmax_t b);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2u a;
	uintmax_t h, i, j, b;
	int expected;

	for (h = 0; h < 10; h++) {
		a.low = h;
		for (i = 0; i < 128; i++) {
			a.high = i;
			for (b = 0; b < 128; b++) {
				expected = 1;
				for (j = 0; j < LIBJ2_JU_BIT; j++) {
					if (((b & ~a.high) >> j) & 1U) {
						expected = 0;
						break;
					}
				}
				EXPECT(libj2_j2u_has_high_ju(&a, b) == expected);
				EXPECT(a.low == h);
				EXPECT(a.high == i);
			}
		}
	}

	return 0;
}

#endif
