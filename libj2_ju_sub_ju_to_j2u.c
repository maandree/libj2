/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_sub_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res);


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
check(uintmax_t a, uintmax_t b)
{
	struct libj2_j2u r, expected;
	int expected_overflow;

	libj2_ju_to_j2u(a, &expected);
	expected_overflow = libj2_j2u_sub_ju_overflow(&expected, b);

	r = (struct libj2_j2u){111, 222};
	libj2_ju_sub_ju_to_j2u(a, b, &r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	r = (struct libj2_j2u){111, 222};
	EXPECT(libj2_ju_sub_ju_to_j2u_overflow(a, b, &r) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	r = (struct libj2_j2u){111, 222};
	libj2_ju_sat_sub_ju_to_j2u(a, b, &r);
	EXPECT(expected_overflow ? libj2_j2u_is_zero(&r) : libj2_j2u_eq_j2u(&r, &expected));

	EXPECT(libj2_ju_sub_ju_overflow_p(a, b) == expected_overflow);
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	check(0, 0);
	check(0, UINTMAX_MAX);
	check(UINTMAX_MAX, 0);
	check(UINTMAX_MAX, UINTMAX_MAX);
	for (i = 0; i < 256; i++) {
		check(0, random_ju());
		check(UINTMAX_MAX, random_ju());
		check(random_ju(), 0);
		check(random_ju(), random_ju());
		check(random_ju(), UINTMAX_MAX);
	}

	return 0;
}

#endif
