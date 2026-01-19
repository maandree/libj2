/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_has_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b);


#else

int
main(void)
{
	struct libj2_j2u a, b, a_saved, b_saved;
	int expected;

	for (a.high = 0; a.high < 32U; a.high++) {
		for (a.low = 0; a.low < 32U; a.low++) {
			for (b.high = 0; b.high < 32U; b.high++) {
				for (b.low = 0; b.low < 32U; b.low++) {
					a_saved = a;
					b_saved = b;
					expected = libj2_j2u_has_ju(&a, b.low);
					expected &= libj2_j2u_has_high_ju(&a, b.high);
					EXPECT(libj2_j2u_has_j2u(&a, &b) == expected);
					EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
					EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));
				}
			}
		}
	}

	return 0;
}

#endif
