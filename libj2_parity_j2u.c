/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline unsigned libj2_parity_j2u(const struct libj2_j2u *a);
/* TODO Add man page */


#else

static uintmax_t
random_ju(unsigned *popcount)
{
        size_t n = LIBJ2_JU_BIT;
        uintmax_t r = 0;
	*popcount = 0;
        while (n--) {
                if (rand() < rand()) {
                        r |= (uintmax_t)1 << n;
			*popcount += 1U;
		}
	}
        return r;
}


int
main(void)
{
	struct libj2_j2u a;
	uintmax_t high, low;
	unsigned i, high_n, low_n;

	srand((unsigned)time(NULL));

	a.high = 0;
	a.low = 0;
	EXPECT(libj2_parity_j2u(&a) == 0);
	EXPECT(a.high == 0);
	EXPECT(a.low == 0);

	a.high = 0;
	a.low = UINTMAX_MAX;
	EXPECT(libj2_parity_j2u(&a) == (LIBJ2_JU_BIT & 1U));
	EXPECT(a.high == 0);
	EXPECT(a.low == UINTMAX_MAX);

	a.high = UINTMAX_MAX;
	a.low = 0;
	EXPECT(libj2_parity_j2u(&a) == (LIBJ2_JU_BIT & 1U));
	EXPECT(a.high == UINTMAX_MAX);
	EXPECT(a.low == 0);

	a.high = UINTMAX_MAX;
	a.low = UINTMAX_MAX;
	EXPECT(libj2_parity_j2u(&a) == (LIBJ2_J2U_BIT & 1U));
	EXPECT(a.high == UINTMAX_MAX);
	EXPECT(a.low == UINTMAX_MAX);

	for (i = 0; i < 256; i++) {
		a.high = high = random_ju(&high_n);
		a.low = low = random_ju(&low_n);
		EXPECT(libj2_parity_j2u(&a) == ((high_n + low_n) & 1U));
		EXPECT(a.high == high);
		EXPECT(a.low == low);

		a.high = high = random_ju(&high_n);
		a.low = low = 0;
		EXPECT(libj2_parity_j2u(&a) == (high_n & 1U));
		EXPECT(a.high == high);
		EXPECT(a.low == 0);

		a.high = high = random_ju(&high_n);
		a.low = low = UINTMAX_MAX;
		EXPECT(libj2_parity_j2u(&a) == ((high_n + LIBJ2_JU_BIT) & 1U));
		EXPECT(a.high == high);
		EXPECT(a.low == UINTMAX_MAX);

		a.high = high = 0;
		a.low = low = random_ju(&low_n);
		EXPECT(libj2_parity_j2u(&a) == (low_n & 1U));
		EXPECT(a.high == 0);
		EXPECT(a.low == low);

		a.high = high = UINTMAX_MAX;
		a.low = low = random_ju(&low_n);
		EXPECT(libj2_parity_j2u(&a) == ((LIBJ2_JU_BIT + low_n) & 1U));
		EXPECT(a.high == UINTMAX_MAX);
		EXPECT(a.low == low);
	}

	return 0;
}

#endif
