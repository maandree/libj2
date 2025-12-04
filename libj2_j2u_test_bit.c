/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_test_bit(const struct libj2_j2u *a, unsigned b);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2u a;
	unsigned i, j, k;

	for (k = 1; k <= 10; k++) {
		for (j = 0; j < k; j++) {
			a.high = 0;
			a.low = 0;
			for (i = 0; i < LIBJ2_J2U_BIT; i++) {
				if (i % k != j)
					continue;
				if (i < LIBJ2_JU_BIT)
					a.low |= (uintmax_t)1 << i;
				else
					a.high |= (uintmax_t)1 << (i - LIBJ2_JU_BIT);
			}
			for (i = 0; i < LIBJ2_J2U_BIT; i++)
				EXPECT(libj2_j2u_test_bit(&a, i) == (i % k == j));
			for (i = LIBJ2_J2U_BIT; i < 2U * LIBJ2_J2U_BIT; i++)
				EXPECT(libj2_j2u_test_bit(&a, i) == 0);
		}
	}

	return 0;
}

#endif
