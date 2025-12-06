/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_sub_ju(struct libj2_j2u *a, uintmax_t b);
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
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b)
{
	struct libj2_j2u a, r, expected;
	int expected_overflow, expected_roverflow;

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	expected_overflow = libj2_j2u_lt_ju(&a, b);
	expected_roverflow = libj2_ju_lt_j2u(b, &a);
	libj2_ju_to_j2u(b, &expected);
	libj2_minus_j2u(&expected);
	libj2_j2u_add_j2u_overflow(&expected, &a);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sub_ju(&a, b);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_sub_ju_overflow(&a, b) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sat_sub_ju(&a, b);
	EXPECT(expected_overflow ? libj2_j2u_is_zero(&a) : libj2_j2u_eq_j2u(&a, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_sub_ju_overflow_p((const struct libj2_j2u *)&a, b) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sub_ju_to_j2u(&a, b, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sub_ju_to_j2u(&a, b, &a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_sub_ju_to_j2u_overflow(&a, b, &r) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_sub_ju_to_j2u_overflow(&a, b, &a) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sat_sub_ju_to_j2u(&a, b, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(expected_overflow ? libj2_j2u_is_zero(&r) : libj2_j2u_eq_j2u(&r, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sat_sub_ju_to_j2u(&a, b, &a);
	EXPECT(expected_overflow ? libj2_j2u_is_zero(&a) : libj2_j2u_eq_j2u(&a, &expected));

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_ju_sub_j2u_to_j2u(b, &a, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	libj2_minus_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_ju_sub_j2u_to_j2u(b, &a, &a);
	libj2_minus_j2u(&a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_rsub_ju(&a, b);
	libj2_minus_j2u(&a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_rsub_ju_overflow(&a, b) == expected_roverflow);
	libj2_minus_j2u(&a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_sat_rsub_ju(&a, b);
	if (expected_roverflow) {
		EXPECT(libj2_j2u_is_zero(&a));
	} else {
		libj2_minus_j2u(&a);
		EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	}

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_rsub_ju_overflow_p((const struct libj2_j2u *)&a, b) == expected_roverflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_ju_sub_j2u_to_j2u_overflow(b, &a, &r) == expected_roverflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	libj2_minus_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_ju_sub_j2u_to_j2u_overflow(b, &a, &a) == expected_roverflow);
	libj2_minus_j2u(&a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_ju_sat_sub_j2u_to_j2u(b, &a, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (expected_roverflow) {
		EXPECT(libj2_j2u_is_zero(&r));
	} else {
		libj2_minus_j2u(&r);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	}

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_ju_sat_sub_j2u_to_j2u(b, &a, &a);
	if (expected_roverflow) {
		EXPECT(libj2_j2u_is_zero(&a));
	} else {
		libj2_minus_j2u(&a);
		EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	}

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_ju_sub_j2u_overflow_p(b, (const struct libj2_j2u *)&a) == expected_roverflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	check(0, 0, 0);
	check(0, 0, UINTMAX_MAX);
	check(UINTMAX_MAX, 0, 0);
	check(UINTMAX_MAX, 0, UINTMAX_MAX);
	for (i = 0; i < 256; i++) {
		check(0, 0, random_ju());
		check(random_ju(), 0, 0);
		check(random_ju(), 0, random_ju());
		check(random_ju(), 0, UINTMAX_MAX);
		check(UINTMAX_MAX, 0, random_ju());
	}

	check(0, UINTMAX_MAX, 0);
	check(0, UINTMAX_MAX, UINTMAX_MAX);
	check(UINTMAX_MAX, UINTMAX_MAX, 0);
	check(UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX);
	for (i = 0; i < 256; i++) {
		check(0, UINTMAX_MAX, random_ju());
		check(random_ju(), UINTMAX_MAX, 0);
		check(random_ju(), UINTMAX_MAX, 1);
		check(random_ju(), UINTMAX_MAX, random_ju());
		check(random_ju(), UINTMAX_MAX, UINTMAX_MAX);
		check(UINTMAX_MAX, UINTMAX_MAX, random_ju());
	}

	for (i = 0; i < 256; i++)
		check(random_ju(), random_ju(), random_ju());

	return 0;
}

#endif
