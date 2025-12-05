/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline unsigned libj2_clz_j2u(const struct libj2_j2u *a);
/* TODO Add man page */


#else

static uintmax_t
random_ju(void)
{
        size_t n = LIBJ2_JU_BIT;
        uintmax_t r = 0;
        while (n--)
                if (rand() < rand())
                        r |= (uintmax_t)1 << n;
        return r;
}


int
main(void)
{
	struct libj2_j2u a, a_saved;
	unsigned i, j;

	srand((unsigned)time(NULL));

	for (i = 0; i <= LIBJ2_J2U_BIT; i++) {
		for (j = 0; j < 64; j++) {
			a.high = random_ju();
			a.low = random_ju();
			libj2_j2u_or_bit(&a, LIBJ2_J2U_BIT - 1U);
			libj2_j2u_rsh(&a, i);
			a_saved = a;

			EXPECT(libj2_clz_j2u(&a) == i);
			EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

			if (i <= LIBJ2_JU_BIT) {
				a.low = UINTMAX_MAX;
				a_saved.low = UINTMAX_MAX;
				EXPECT(libj2_clz_j2u(&a) == i);
				EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
			}

			if (i < LIBJ2_JU_BIT) {
				a.low = 0;
				a_saved.low = 0;
				EXPECT(libj2_clz_j2u(&a) == i);
				EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
			}
		}
	}

	return 0;
}

#endif
