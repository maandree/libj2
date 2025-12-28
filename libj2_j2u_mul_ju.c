/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_mul_ju(struct libj2_j2u *a, uintmax_t b);


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


static int
refmul(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *expected)
{
	struct libj2_j2u c;
	unsigned i;
	int overflow = 0;

	libj2_j2u_zero(expected);
	for (i = 0; i < LIBJ2_J2U_BIT; i++, b >>= 1) {
		if (b & 1U) {
			overflow |= libj2_j2u_lsh_to_j2u_overflow(a, i, &c);
			libj2_j2u_add_j2u(expected, &c);
		}
	}

	return overflow;
}


static void
mul(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *expected, int expect_overflow)
{
	struct libj2_j2u t, a_saved = *a, t_saved;
	enum libj2_overflow ofp;
	int set;

	*expected = *a;
	libj2_j2u_mul_ju(expected, b);

	t = (struct libj2_j2u){111, 222};
	libj2_j2u_mul_ju_to_j2u(a, b, &t);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	t = *a;
	libj2_j2u_mul_ju_to_j2u(&t, b, &t);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	t = (struct libj2_j2u){111, 222};
	libj2_ju_mul_j2u_to_j2u(b, a, &t);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	t = *a;
	libj2_ju_mul_j2u_to_j2u(b, &t, &t);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	t = *a;
	EXPECT(libj2_j2u_mul_ju_overflow(&t, b) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	t = *a;
	libj2_j2u_sat_mul_ju(&t, b);
	EXPECT(expect_overflow ? libj2_j2u_is_max(&t) : libj2_j2u_eq_j2u(&t, expected));

	t = *a;
	EXPECT(libj2_j2u_mul_ju_overflow_p((const struct libj2_j2u *)&t, b) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, a));

	t = *a;
	ofp = libj2_j2u_mul_ju_overflow_p_quick((const struct libj2_j2u *)&t, b);
	EXPECT(ofp == LIBJ2_OVERFLOW_UNKNOWN || (int)ofp == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, a));

	set = 999;
	t = (struct libj2_j2u){111, 222};
	t_saved = t;
	EXPECT(libj2_j2u_mul_ju_to_j2u_overflow_p((const struct libj2_j2u *)a, b, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&t, set ? expected : &t_saved));

	set = 999;
	t = *a;
	EXPECT(libj2_j2u_mul_ju_to_j2u_overflow_p((const struct libj2_j2u *)&t, b, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2u_eq_j2u(&t, set ? expected : a));

	t = (struct libj2_j2u){111, 222};
	EXPECT(libj2_j2u_mul_ju_to_j2u_overflow(a, b, &t) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	t = *a;
	EXPECT(libj2_j2u_mul_ju_to_j2u_overflow(&t, b, &t) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	t = (struct libj2_j2u){111, 222};
	libj2_j2u_sat_mul_ju_to_j2u(a, b, &t);
	EXPECT(expect_overflow ? libj2_j2u_is_max(&t) : libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	t = *a;
	libj2_j2u_sat_mul_ju_to_j2u(&t, b, &t);
	EXPECT(expect_overflow ? libj2_j2u_is_max(&t) : libj2_j2u_eq_j2u(&t, expected));

	t = (struct libj2_j2u){111, 222};
	EXPECT(libj2_ju_mul_j2u_to_j2u_overflow(b, a, &t) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	t = *a;
	EXPECT(libj2_ju_mul_j2u_to_j2u_overflow(b, &t, &t) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(&t, expected));

	t = (struct libj2_j2u){111, 222};
	libj2_ju_sat_mul_j2u_to_j2u(b, a, &t);
	EXPECT(expect_overflow ? libj2_j2u_is_max(&t) : libj2_j2u_eq_j2u(&t, expected));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	t = *a;
	libj2_ju_sat_mul_j2u_to_j2u(b, &t, &t);
	EXPECT(expect_overflow ? libj2_j2u_is_max(&t) : libj2_j2u_eq_j2u(&t, expected));

	set = 999;
	t = (struct libj2_j2u){111, 222};
	t_saved = t;
	EXPECT(libj2_ju_mul_j2u_to_j2u_overflow_p(b, a, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2u_eq_j2u(&t, set ? expected : &t_saved));
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	set = 999;
	t = *a;
	EXPECT(libj2_ju_mul_j2u_to_j2u_overflow_p(b, &t, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2u_eq_j2u(&t, set ? expected : a));

	EXPECT(libj2_ju_mul_j2u_overflow_p(b, (const struct libj2_j2u *)a) == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	ofp = libj2_ju_mul_j2u_overflow_p_quick(b, (const struct libj2_j2u *)a);
	EXPECT(ofp == LIBJ2_OVERFLOW_UNKNOWN || (int)ofp == expect_overflow);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
}


int
main(void)
{
	struct libj2_j2u r, expected;
	uintmax_t u, v, w;
	unsigned i;
	int expect_overflow;

	srand((unsigned)time(NULL));

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = 0}, 0, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = 0}, 1, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = 0}, UINTMAX_MAX, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = 1}, 0, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = UINTMAX_MAX}, 0, &r, 0);
	EXPECT(libj2_j2u_is_zero(&r));

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2u){111, 222};
		mul(&(struct libj2_j2u){.high = 0, .low = 0}, random_ju(), &r, 0);
		EXPECT(libj2_j2u_is_zero(&r));

		r = (struct libj2_j2u){111, 222};
		mul(&(struct libj2_j2u){.high = 0, .low = random_ju()}, 0, &r, 0);
		EXPECT(libj2_j2u_is_zero(&r));
	}

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = 1}, 1, &r, 0);
	EXPECT(r.high == 0);
	EXPECT(r.low == 1);

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = 4}, 4, &r, 0);
	EXPECT(r.high == 0);
	EXPECT(r.low == 16);

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		mul(&(struct libj2_j2u){.high = 0, .low = 1}, v, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == v);

		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		mul(&(struct libj2_j2u){.high = 0, .low = v}, 1, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == v);
	}

	for (i = 0; i < 32; i++) {
		u = random_hju();
		v = random_hju();

		r = (struct libj2_j2u){111, 222};
		mul(&(struct libj2_j2u){.high = 0, .low = u}, v, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == u * v);

		r = (struct libj2_j2u){111, 222};
		mul(&(struct libj2_j2u){.high = 0, .low = v}, u, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == u * v);
	}

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = 0, .low = UINTMAX_MAX}, UINTMAX_MAX, &r, 0);
	EXPECT(r.high == UINTMAX_MAX - 1U);
	EXPECT(r.low == 1);

	r = (struct libj2_j2u){111, 222};
	mul(&(struct libj2_j2u){.high = UINTMAX_MAX, .low = UINTMAX_MAX}, UINTMAX_MAX, &r, 1);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == 1);

	/* self-check */
	r = (struct libj2_j2u){111, 222};
	EXPECT(refmul(&(struct libj2_j2u){.high = UINTMAX_MAX, .low = UINTMAX_MAX}, UINTMAX_MAX, &r) == 1);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == 1);

	for (i = 0; i < 256; i++) {
		u = random_ju();
		v = random_ju();
		w = random_ju();

		expect_overflow = refmul(&(struct libj2_j2u){u, v}, w, &expected);

		r = (struct libj2_j2u){111, 222};
		mul(&(struct libj2_j2u){u, v}, w, &r, expect_overflow);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	}

	return 0;
}

#endif
