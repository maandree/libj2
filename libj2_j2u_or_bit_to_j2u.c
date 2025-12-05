/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_or_bit_to_j2u(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res);
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


static void
check(uintmax_t high, uintmax_t low, unsigned shift)
{
	struct libj2_j2u a, r, expected;

	a.high = high;
	a.low = low;

	libj2_ju_lsh_to_j2u(1U, shift, &expected);
	libj2_j2u_or_j2u_to_j2u(&a, &expected, &expected);

	r = (struct libj2_j2u){111, 222};
	libj2_j2u_or_bit_to_j2u(&a, shift, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	r = a;
	libj2_j2u_or_bit_to_j2u(&r, shift, &r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	r = a;
	libj2_j2u_or_bit(&r, shift);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	for (i = 0; i < LIBJ2_J2U_BIT + 4U; i++) {
		check(0, 0, i);
		check(0, random_ju(), i);
		check(0, UINTMAX_MAX, i);
		check(random_ju(), 0, i);
		check(random_ju(), random_ju(), i);
		check(random_ju(), UINTMAX_MAX, i);
		check(UINTMAX_MAX, 0, i);
		check(UINTMAX_MAX, random_ju(), i);
		check(UINTMAX_MAX, UINTMAX_MAX, i);
	}

	return 0;
}

#endif
