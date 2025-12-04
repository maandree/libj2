/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_mul_j2u_destructive(struct libj2_j2u *restrict a /*result */, struct libj2_j2u *restrict b /*destructed */);
/* TODO Add man page */


#else

static uintmax_t
random_small_ju(size_t bits)
{
	uintmax_t r = 0;
	while (bits--)
		if (rand() < rand())
			r |= (uintmax_t)1 << bits;
	return r;
}

static uintmax_t
random_hju(void)
{
	return random_small_ju(LIBJ2_JU_BIT / 2U);
}

static uintmax_t
random_ju(void)
{
	return random_small_ju(LIBJ2_JU_BIT);
}

static void
random_j2u(struct libj2_j2u *a)
{
	a->high = random_ju();
	a->low = random_ju();
}


static int
refmul(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *expected)
{
	struct libj2_j2u c;
	unsigned i;
	int overflow = 0;

	libj2_j2u_zero(expected);
	for (i = 0; i < LIBJ2_J2U_BIT; i++) {
		if (libj2_j2u_test_bit(b, i)) {
			overflow |= libj2_j2u_lsh_to_j2u_overflow(a, i, &c);
			libj2_j2u_add_j2u(expected, &c);
		}
	}

	return overflow;
}


static void
mul_(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *expected, int expect_overflow)
{
	struct libj2_j2u t, x, a_saved = *a, b_saved = *b;

	*expected = *a;
	libj2_j2u_mul_j2u(expected, b);

	t = (struct libj2_j2u){111, 222};
	libj2_j2u_mul_j2u_to_j2u(a, b, &t);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));

	t = *a;
	EXPECT(libj2_j2u_mul_j2u_overflow(&t, b) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));

	t = (struct libj2_j2u){111, 222};
	EXPECT(libj2_j2u_mul_j2u_to_j2u_overflow(a, b, &t) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));

	t = *a;
	x = *b;
	libj2_j2u_mul_j2u_destructive(&t, &x);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	t = *a;
	x = *b;
	EXPECT(libj2_j2u_mul_j2u_overflow_destructive(&t, &x) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	if (a == b) {
		t = *a;
		libj2_j2u_mul_j2u(&t, &t);
		EXPECT(libj2_j2u_eq_j2u(&t, expected));

		t = *a;
		libj2_j2u_mul_j2u_to_j2u(&t, &t, &t);
		EXPECT(libj2_j2u_eq_j2u(&t, expected));

		t = *a;
		EXPECT(libj2_j2u_mul_j2u_overflow(&t, &t) == expect_overflow);
		EXPECT(libj2_j2u_eq_j2u(&t, expected));

		t = *a;
		EXPECT(libj2_j2u_mul_j2u_to_j2u_overflow(&t, &t, &t) == expect_overflow);
		EXPECT(libj2_j2u_eq_j2u(&t, expected));
	}}


static void
mul(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *expected, int expect_overflow)
{
	struct libj2_j2u t;

	if (a == b) {
		t = *a;
		mul_(a, &t, expected, expect_overflow);
		mul_(a, a, expected, expect_overflow);
	} else {
		mul_(a, b, expected, expect_overflow);
		mul_(b, a, expected, expect_overflow);
	}
}


int
main(void)
{
	const struct libj2_j2u zero = {0, 0};
	const struct libj2_j2u one = {.high = 0, .low = 1};
	const struct libj2_j2u four = {.high = 0, .low = 4};
	const struct libj2_j2u ju_max = {.high = 0, .low = UINTMAX_MAX};
	const struct libj2_j2u j2u_max = {.high = UINTMAX_MAX, .low = UINTMAX_MAX};
	struct libj2_j2u a, b, r, expected;
	uintmax_t u, v;
	unsigned i;
	int expect_overflow;

	srand((unsigned)time(NULL));

	r = (struct libj2_j2u){111, 222};
	mul(&zero, &zero, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&zero, &one, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&zero, &ju_max, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&one, &zero, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&ju_max, &zero, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		libj2_ju_to_j2u(v, &a);
		mul(&zero, &a, &r, 0);
		EXPECT(libj2_j2u_is_zero(&r));

		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		libj2_ju_to_j2u(v, &a);
		mul(&a, &zero, &r, 0);

		EXPECT(libj2_j2u_is_zero(&r));
		r = (struct libj2_j2u){111, 222};
		random_j2u(&a);
		mul(&zero, &a, &r, 0);
		EXPECT(libj2_j2u_is_zero(&r));

		r = (struct libj2_j2u){111, 222};
		random_j2u(&a);
		mul(&a, &zero, &r, 0);
		EXPECT(libj2_j2u_is_zero(&r));
	}

	r = (struct libj2_j2u){111, 222};
	mul(&one, &one, &r, 0);
	EXPECT(r.high == 0);
	EXPECT(r.low == 1);

	r = (struct libj2_j2u){111, 222};
	mul(&four, &four, &r, 0);
	EXPECT(r.high == 0);
	EXPECT(r.low == 16);

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		libj2_ju_to_j2u(v, &a);
		mul(&one, &a, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == v);

		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		libj2_ju_to_j2u(v, &a);
		mul(&a, &one, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == v);
	}

	for (i = 0; i < 32; i++) {
		u = random_hju();
		v = random_hju();

		libj2_ju_to_j2u(u, &a);
		libj2_ju_to_j2u(v, &b);

		r = (struct libj2_j2u){111, 222};
		mul(&a, &b, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == u * v);

		r = (struct libj2_j2u){111, 222};
		mul(&b, &a, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == u * v);
	}

	r = (struct libj2_j2u){111, 222};
	mul(&ju_max, &ju_max, &r, 0);
	EXPECT(r.high == UINTMAX_MAX - 1U);
	EXPECT(r.low == 1);

	r = (struct libj2_j2u){111, 222};
	mul(&j2u_max, &ju_max, &r, 1);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == 1);

	/* self-check */
	r = (struct libj2_j2u){111, 222};
	EXPECT(refmul(&j2u_max, &ju_max, &r) == 1);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == 1);
	r = (struct libj2_j2u){111, 222};
	EXPECT(refmul(&j2u_max, &j2u_max, &r) == 1);
	EXPECT(r.high == 0);
	EXPECT(r.low == 1);

	for (i = 0; i < 256; i++) {
		random_j2u(&a);
		random_j2u(&b);

		expect_overflow = refmul(&a, &b, &expected);

		r = (struct libj2_j2u){111, 222};
		mul(&a, &b, &r, expect_overflow);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	}

	return 0;
}

#endif
