/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_add_j2u(struct libj2_j2u *a, const struct libj2_j2u *b);
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
check_(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
       uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	struct libj2_j2u a, b, r, a_saved, b_saved, expected;

	a_saved = (struct libj2_j2u){.high = a_high, .low = a_low};
	b_saved = (struct libj2_j2u){.high = b_high, .low = b_low};
	expected = (struct libj2_j2u){.high = r_high, .low = r_low};

	a = a_saved;
	b = b_saved;
	libj2_j2u_add_j2u(&a, &b);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2u_add_j2u_to_j2u(&a, &b, &r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_add_j2u_to_j2u(&a, &b, &a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2u_add_j2u_to_j2u(&a, &b, &b);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_add_j2u_overflow(&a, &b) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_add_j2u_overflow_p((const struct libj2_j2u *)&a, (const struct libj2_j2u *)&b) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, &r) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, &a) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
	EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, &b) == r_overflow);
	EXPECT(libj2_j2u_eq_j2u(&b, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	uintmax_t r_high = 0, r_low = 0, carry = 0;
	int r_overflow;
	unsigned i;

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a_low >> i) & 1U;
		carry += (b_low >> i) & 1U;
		r_low |= (carry & 1U) << i;
		carry >>= 1;
	}

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a_high >> i) & 1U;
		carry += (b_high >> i) & 1U;
		r_high |= (carry & 1U) << i;
		carry >>= 1;
	}

	r_overflow = (int)carry;
	check_(a_high, a_low, b_high, b_low, r_high, r_low, r_overflow);
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
	struct libj2_j2u a, r, a_saved, expected, b;
	uintmax_t expected_high = (high << 1 | low >> (LIBJ2_JU_BIT - 1U));
	uintmax_t expected_low = low << 1;
	int expected_overflow = !!(high >> (LIBJ2_JU_BIT - 1U));

	a_saved = (struct libj2_j2u){.high = high, .low = low};
	expected = (struct libj2_j2u){.high = expected_high, .low = expected_low};

	a = a_saved;
	b = a_saved;
	libj2_j2u_add_j2u(&a, &b);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = a_saved;
	libj2_j2u_add_j2u(&a, &a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	libj2_j2u_add_j2u_to_j2u(&a, &a, &r);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	libj2_j2u_add_j2u_to_j2u(&a, &a, &a);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = a_saved;
	EXPECT(libj2_j2u_add_j2u_overflow(&a, &a) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));

	a = a_saved;
	EXPECT(libj2_j2u_add_j2u_overflow_p((const struct libj2_j2u *)&a, (const struct libj2_j2u *)&a) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	r = (struct libj2_j2u){111, 222};
	a = a_saved;
	EXPECT(libj2_j2u_add_j2u_to_j2u_overflow(&a, &a, &r) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a = a_saved;
	EXPECT(libj2_j2u_add_j2u_to_j2u_overflow(&a, &a, &a) == expected_overflow);
	EXPECT(libj2_j2u_eq_j2u(&a, &expected));
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	check_manual(0, 0, 0, 0, 0, 0, 0);
	check_manual(0, 1, 0, 1, 0, 2, 0);
	check_manual(0, UINTMAX_MAX, 0, 1, 1, 0, 0);
	check_manual(0, UINTMAX_MAX, 0, UINTMAX_MAX, 1, UINTMAX_MAX - 1U, 0);
	check_manual(UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX - 1U, 1);

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

	return 0;
}

#endif
