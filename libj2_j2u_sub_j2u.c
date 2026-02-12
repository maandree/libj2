/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_sub_j2u(struct libj2_j2u *a, const struct libj2_j2u *b);


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
check_(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
       uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	struct libj2_j2u a, b, r, a_saved, b_saved, expected, expected_minus_one;
	int borrow;

	a_saved = (struct libj2_j2u){.high = a_high, .low = a_low};
	b_saved = (struct libj2_j2u){.high = b_high, .low = b_low};
	expected = (struct libj2_j2u){.high = r_high, .low = r_low};

	libj2_j2u_sub_ju_to_j2u(&expected, 1, &expected_minus_one);

	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u(&a, &b);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u(&a, &b, &r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u(&a, &b, &a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u(&a, &b, &b);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_sub_j2u_overflow(&a, &b) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_sat_sub_j2u(&a, &b);
	EXPECT(r_overflow ? libj2_j2u_is_zero(&a) : libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_sub_j2u_overflow_p((const struct libj2_j2u *)&a, (const struct libj2_j2u *)&b) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_sub_j2u_to_j2u_overflow(&a, &b, &r) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_sub_j2u_to_j2u_overflow(&a, &b, &a) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_sub_j2u_to_j2u_overflow(&a, &b, &b) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2u_sat_sub_j2u_to_j2u(&a, &b, &r);
	EXPECT(r_overflow ? libj2_j2u_is_zero(&r) : libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_sat_sub_j2u_to_j2u(&a, &b, &a);
	EXPECT(r_overflow ? libj2_j2u_is_zero(&a) : libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_sat_sub_j2u_to_j2u(&a, &b, &b);
	EXPECT(r_overflow ? libj2_j2u_is_zero(&b) : libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_rsub_j2u(&b, &a);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_rsub_j2u_overflow(&b, &a) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_sat_rsub_j2u(&b, &a);
	EXPECT(r_overflow ? libj2_j2u_is_zero(&b) : libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_rsub_j2u_overflow_p(&b, &a) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_borrow(&a, &b, &borrow);
	EXPECT(borrow == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	borrow = 0;
	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &r, &borrow);
	EXPECT(borrow == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	borrow = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &a, &borrow);
	EXPECT(borrow == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	borrow = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &b, &borrow);
	EXPECT(borrow == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2u_rsub_j2u_borrow(&b, &a, &borrow);
	EXPECT(borrow == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 1;
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_borrow(&a, &b, &borrow);
	EXPECT(borrow >= r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected_minus_one));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	borrow = 1;
	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &r, &borrow);
	EXPECT(borrow >= r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected_minus_one));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	borrow = 1;
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &a, &borrow);
	EXPECT(borrow >= r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected_minus_one));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	borrow = 1;
	a = a_saved;
	b = b_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &b, &borrow);
	EXPECT(borrow >= r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected_minus_one));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 1;
	a = a_saved;
	b = b_saved;
	libj2_j2u_rsub_j2u_borrow(&b, &a, &borrow);
	EXPECT(borrow >= r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected_minus_one));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2u a, b, r;
	int overflow;

	a.high = a_high;
	a.low = a_low;
	b.high = b_high;
	b.low = b_low;

	overflow = libj2_j2u_lt_j2u(&a, &b);
	libj2_minus_j2u(&b);
	libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, &r);
	check_(a_high, a_low, b_high, b_low, r.high, r.low, overflow);
}


static void
check_manual(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
             uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	check_(a_high, a_low, b_high, b_low, r_high, r_low, r_overflow);
	check(a_high, a_low, b_high, b_low);
}


static void
check_double(uintmax_t high, uintmax_t low)
{
	struct libj2_j2u a, a_saved, r;
	int borrow;

	a_saved = (struct libj2_j2u){.high = high, .low = low};

	a = a_saved;
	libj2_j2u_sub_j2u(&a, &a);
	EXPECT(libj2_j2u_is_zero(&a));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	libj2_j2u_sub_j2u_to_j2u(&a, &a, &r);
	EXPECT(libj2_j2u_is_zero(&r));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	libj2_j2u_sub_j2u_to_j2u(&a, &a, &a);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	EXPECT(libj2_j2u_sub_j2u_overflow(&a, &a) == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	libj2_j2u_sat_sub_j2u(&a, &a);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	EXPECT(libj2_j2u_sub_j2u_overflow_p((const struct libj2_j2u *)&a, (const struct libj2_j2u *)&a) == 0);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	EXPECT(libj2_j2u_sub_j2u_to_j2u_overflow(&a, &a, &r) == 0);
	EXPECT(libj2_j2u_is_zero(&r));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	EXPECT(libj2_j2u_sub_j2u_to_j2u_overflow(&a, &a, &a) == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	libj2_j2u_sat_sub_j2u_to_j2u(&a, &a, &r);
	EXPECT(libj2_j2u_is_zero(&r));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	libj2_j2u_sat_sub_j2u_to_j2u(&a, &a, &a);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	libj2_j2u_rsub_j2u(&a, &a);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	EXPECT(libj2_j2u_rsub_j2u_overflow(&a, &a) == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	libj2_j2u_sat_rsub_j2u(&a, &a);
	EXPECT(libj2_j2u_is_zero(&a));

	a = a_saved;
	EXPECT(libj2_j2u_rsub_j2u_overflow_p((const struct libj2_j2u *)&a, (const struct libj2_j2u *)&a) == 0);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 0;
	a = a_saved;
	libj2_j2u_sub_j2u_borrow(&a, &a, &borrow);
	EXPECT(borrow == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	borrow = 0;
	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &a, &r, &borrow);
	EXPECT(borrow == 0);
	EXPECT(libj2_j2u_is_zero(&r));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 0;
	a = a_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &a, &a, &borrow);
	EXPECT(borrow == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	borrow = 0;
	a = a_saved;
	libj2_j2u_rsub_j2u_borrow(&a, &a, &borrow);
	EXPECT(borrow == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	borrow = 1;
	a = a_saved;
	libj2_j2u_sub_j2u_borrow(&a, &a, &borrow);
	EXPECT(borrow == 1);
	EXPECT(libj2_j2u_is_max(&a));

	borrow = 1;
	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &a, &r, &borrow);
	EXPECT(borrow == 1);
	EXPECT(libj2_j2u_is_max(&r));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	borrow = 1;
	a = a_saved;
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &a, &a, &borrow);
	EXPECT(borrow == 1);
	EXPECT(libj2_j2u_is_max(&a));

	borrow = 1;
	a = a_saved;
	libj2_j2u_rsub_j2u_borrow(&a, &a, &borrow);
	EXPECT(borrow == 1);
	EXPECT(libj2_j2u_is_max(&a));
}


int
main(void)
{
	unsigned i;
	struct libj2_j2u a, b;
	int borrow;

	srand((unsigned)time(NULL));

	check_manual(0, 0, 0, 0, 0, 0, 0);
	check_manual(0, 1, 0, 1, 0, 0, 0);
	check_manual(0, 1, 0, 0, 0, 1, 0);
	check_manual(1, 0, 0, 1, 0, UINTMAX_MAX, 0);
	check_manual(1, 1, 0, 2, 0, UINTMAX_MAX, 0);
	check_manual(1, 1, 0, 1, 1, 0, 0);
	check_manual(2, 0, 0, 1, 1, UINTMAX_MAX, 0);
	check_manual(2, 0, 1, 1, 0, UINTMAX_MAX, 0);
	check_manual(0, 0, 0, 1, UINTMAX_MAX, UINTMAX_MAX, 1);
	check_manual(0, UINTMAX_MAX, 0, 1, 0, UINTMAX_MAX - 1U, 0);
	check_manual(0, UINTMAX_MAX, 0, UINTMAX_MAX, 0, 0, 0);
	check_manual(UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX, 0, 0, 0);

	for (i = 0; i < 256; i++)
		check(random_ju(), random_ju(), random_ju(), random_ju());

	check_double(0, 0);
	check_double(0, UINTMAX_MAX);
	check_double(UINTMAX_MAX, 0);
	check_double(UINTMAX_MAX, UINTMAX_MAX);
	for (i = 0; i < 256; i++) {
		check_double(0, random_ju());
		check_double(random_ju(), 0);
		check_double(random_ju(), UINTMAX_MAX);
		check_double(random_ju(), random_ju());
		check_double(UINTMAX_MAX, random_ju());
	}

	borrow = 1;
	libj2_j2u_min(&a);
	libj2_j2u_zero(&b);
	libj2_j2u_sub_j2u_to_j2u_borrow(&a, &b, &a, &borrow);
	EXPECT(borrow == 1);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(libj2_j2u_is_zero(&b));

	borrow = 1;
	libj2_j2u_min(&a);
	libj2_j2u_zero(&b);
	libj2_j2u_sub_j2u_borrow(&a, &b, &borrow);
	EXPECT(borrow == 1);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(libj2_j2u_is_zero(&b));

	return 0;
}

#endif
