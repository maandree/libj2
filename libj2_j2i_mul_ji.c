/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_mul_ji(struct libj2_j2i *a, intmax_t b);


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
refmul(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *expected)
{
	struct libj2_j2u u;
	struct libj2_j2i c;
	uintmax_t v;
	unsigned i;
	int neg, overflow = 0;

	neg = libj2_j2i_is_negative(a) ^ (b < 0);
	libj2_abs_j2i_to_j2u(a, &u);
	v = b < 0 ? (uintmax_t)-(b + 1) + 1U : (uintmax_t)b;

	libj2_j2i_zero(expected);
	for (i = 0; i < LIBJ2_J2U_BIT; i++, v >>= 1) {
		if (v & 1U) {
			overflow |= libj2_j2i_lsh_to_j2i_overflow(a, i, &c);
			libj2_j2i_add_j2i(expected, &c);
		}
	}

	if (neg) {
		overflow = -overflow;
		libj2_minus_j2i(expected);
	}

	return overflow;
}


static void
mul_(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *expected, int expect_overflow)
{
	struct libj2_j2i t, a_saved = *a, t_saved;
	enum libj2_overflow ofp;
	enum libj2_overflow unknown_overflow;
	int set;

	if (libj2_j2i_is_zero(a) || b == 0)
		unknown_overflow = LIBJ2_NO_OVERFLOW;
	else if (libj2_j2i_is_negative(a) ^ (b < 0))
		unknown_overflow = LIBJ2_NEGATIVE_OVERFLOW_UNKNOWN;
	else
		unknown_overflow = LIBJ2_POSITIVE_OVERFLOW_UNKNOWN;

	*expected = *a;
	libj2_j2i_mul_ji(expected, b);

	t = (struct libj2_j2i){111, 222};
	libj2_j2i_mul_ji_to_j2i(a, b, &t);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	t = *a;
	libj2_j2i_mul_ji_to_j2i(&t, b, &t);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));

	t = (struct libj2_j2i){111, 222};
	libj2_ji_mul_j2i_to_j2i(b, a, &t);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	t = *a;
	libj2_ji_mul_j2i_to_j2i(b, &t, &t);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));

	t = *a;
	EXPECT(libj2_j2i_mul_ji_overflow(&t, b) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));

	t = *a;
	libj2_j2i_sat_mul_ji(&t, b);
	EXPECT(expect_overflow > 0 ? libj2_j2i_is_max(&t) :
	       expect_overflow ? libj2_j2i_is_min(&t) : libj2_j2i_eq_j2i(&t, expected));

	t = *a;
	EXPECT(libj2_j2i_mul_ji_overflow_p((const struct libj2_j2i *)&t, b) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, a));

	t = *a;
	ofp = libj2_j2i_mul_ji_overflow_p_quick((const struct libj2_j2i *)&t, b);
	EXPECT(ofp == unknown_overflow || (int)ofp == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, a));

	set = 999;
	t = (struct libj2_j2i){111, 222};
	t_saved = t;
	EXPECT(libj2_j2i_mul_ji_to_j2i_overflow_p((const struct libj2_j2i *)a, b, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&t, set ? expected : &t_saved));

	set = 999;
	t = *a;
	EXPECT(libj2_j2i_mul_ji_to_j2i_overflow_p((const struct libj2_j2i *)&t, b, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2i_eq_j2i(&t, set ? expected : a));

	t = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2i_mul_ji_to_j2i_overflow(a, b, &t) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	t = *a;
	EXPECT(libj2_j2i_mul_ji_to_j2i_overflow(&t, b, &t) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));

	t = (struct libj2_j2i){111, 222};
	libj2_j2i_sat_mul_ji_to_j2i(a, b, &t);
	EXPECT(expect_overflow > 0 ? libj2_j2i_is_max(&t) :
	       expect_overflow ? libj2_j2i_is_min(&t) : libj2_j2i_eq_j2i(&t, expected));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	t = *a;
	libj2_j2i_sat_mul_ji_to_j2i(&t, b, &t);
	EXPECT(expect_overflow > 0 ? libj2_j2i_is_max(&t) :
	       expect_overflow ? libj2_j2i_is_min(&t) : libj2_j2i_eq_j2i(&t, expected));

	t = (struct libj2_j2i){111, 222};
	EXPECT(libj2_ji_mul_j2i_to_j2i_overflow(b, a, &t) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	t = *a;
	EXPECT(libj2_ji_mul_j2i_to_j2i_overflow(b, &t, &t) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&t, expected));

	t = (struct libj2_j2i){111, 222};
	libj2_ji_sat_mul_j2i_to_j2i(b, a, &t);
	EXPECT(expect_overflow > 0 ? libj2_j2i_is_max(&t) :
	       expect_overflow ? libj2_j2i_is_min(&t) : libj2_j2i_eq_j2i(&t, expected));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	t = *a;
	libj2_ji_sat_mul_j2i_to_j2i(b, &t, &t);
	EXPECT(expect_overflow > 0 ? libj2_j2i_is_max(&t) :
	       expect_overflow ? libj2_j2i_is_min(&t) : libj2_j2i_eq_j2i(&t, expected));

	set = 999;
	t = (struct libj2_j2i){111, 222};
	t_saved = t;
	EXPECT(libj2_ji_mul_j2i_to_j2i_overflow_p(b, a, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2i_eq_j2i(&t, set ? expected : &t_saved));
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	set = 999;
	t = *a;
	EXPECT(libj2_ji_mul_j2i_to_j2i_overflow_p(b, &t, &t, &set) == expect_overflow);
	EXPECT(set == 0 || set == 1);
	EXPECT(libj2_j2i_eq_j2i(&t, set ? expected : a));

	EXPECT(libj2_ji_mul_j2i_overflow_p(b, (const struct libj2_j2i *)a) == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));

	ofp = libj2_ji_mul_j2i_overflow_p_quick(b, (const struct libj2_j2i *)a);
	EXPECT(ofp == unknown_overflow || (int)ofp == expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
}


static void
mul(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *expected, int expect_overflow)
{
	struct libj2_j2i r, neg_a, e;
	struct libj2_j2u u;

	libj2_minus_j2i_to_j2i(a, &neg_a);
	libj2_j2i_to_j2u(a, &u);


	mul_(a, b, expected, expect_overflow);

	mul_(&neg_a, -b, &r, expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	mul_(&neg_a, b, &r, -expect_overflow);
	libj2_minus_j2i(&r);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	mul_(a, -b, &r, -expect_overflow);
	libj2_minus_j2i(&r);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));


	expect_overflow = libj2_j2u_mul_ju_to_j2u_overflow(&u, (uintmax_t)b + 1U, (void *)&e);
	if (libj2_j2i_is_negative(&e))
		expect_overflow = 1;

	mul_(&neg_a, -b - 1, &r, expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &e));

	mul_(a, -b - 1, &r, -expect_overflow);
	libj2_minus_j2i(&r);
	EXPECT(libj2_j2i_eq_j2i(&r, &e));


	libj2_j2u_add_ju(&u, 1U);
	libj2_j2i_add_ji(&neg_a, -1);
	expect_overflow = libj2_j2u_mul_ju_to_j2u_overflow(&u, (uintmax_t)b, (void *)&e);
	if (libj2_j2i_is_negative(&e))
		expect_overflow = 1;

	mul_(&neg_a, b, &r, -expect_overflow);
	libj2_minus_j2i(&r);
	EXPECT(libj2_j2i_eq_j2i(&r, &e));


	expect_overflow = libj2_j2u_mul_ju_to_j2u_overflow(&u, (uintmax_t)b + 1U, (void *)&e);
	if (libj2_j2i_is_negative(&e))
		expect_overflow = 1;

	mul_(&neg_a, -b - 1, &r, expect_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &e));
}


int
main(void)
{
	struct libj2_j2i r, expected;
	intmax_t u, v;
	uintmax_t w;
	unsigned i;
	int expect_overflow;

	srand((unsigned)time(NULL));

	/* self-check */
	r = (struct libj2_j2i){111, 222};
	EXPECT(refmul(&(struct libj2_j2i){.high = UINTMAX_MAX >> 1, .low = UINTMAX_MAX}, INTMAX_MAX, &r) == 1);
	EXPECT(r.high == UINTMAX_MAX >> 1);
	EXPECT(r.low == 2 + (uintmax_t)INTMAX_MAX);

	r = (struct libj2_j2i){111, 222};
	mul_(&(struct libj2_j2i){.high = (UINTMAX_MAX >> 2) + 1U, .low = 0}, 2, &r, 1);
	EXPECT(r.high == (UINTMAX_MAX >> 1) + 1U);
	EXPECT(r.low == 0);

	r = (struct libj2_j2i){111, 222};
	mul_(&(struct libj2_j2i){.high = (UINTMAX_MAX >> 2) + 1U, .low = 0}, -2, &r, 0);
	EXPECT(r.high == (UINTMAX_MAX >> 1) + 1U);
	EXPECT(r.low == 0);

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = 0}, 0, &r, 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = 0}, 1, &r, 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = 0}, INTMAX_MAX, &r, 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = 1}, 0, &r, 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = UINTMAX_MAX}, 0, &r, 0);
	EXPECT(libj2_j2i_is_zero(&r));

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2i){111, 222};
		mul(&(struct libj2_j2i){.high = 0, .low = 0}, (intmax_t)(random_ju() >> 1), &r, 0);
		EXPECT(libj2_j2i_is_zero(&r));

		r = (struct libj2_j2i){111, 222};
		mul(&(struct libj2_j2i){.high = 0, .low = random_ju()}, 0, &r, 0);
		EXPECT(libj2_j2i_is_zero(&r));
	}

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = 1}, 1, &r, 0);
	EXPECT(r.high == 0);
	EXPECT(r.low == 1);

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = 4}, 4, &r, 0);
	EXPECT(r.high == 0);
	EXPECT(r.low == 16);

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2i){111, 222};
		v = (intmax_t)(random_ju() >> 1);
		mul(&(struct libj2_j2i){.high = 0, .low = 1}, v, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)v);

		r = (struct libj2_j2i){111, 222};
		v = (intmax_t)(random_ju() >> 1);
		mul(&(struct libj2_j2i){.high = 0, .low = (uintmax_t)v}, 1, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)v);
	}

	for (i = 0; i < 32; i++) {
		u = (intmax_t)random_hju();
		v = (intmax_t)random_hju();

		r = (struct libj2_j2i){111, 222};
		mul(&(struct libj2_j2i){.high = 0, .low = (uintmax_t)u}, v, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)u * (uintmax_t)v);

		r = (struct libj2_j2i){111, 222};
		mul(&(struct libj2_j2i){.high = 0, .low = (uintmax_t)v}, u, &r, 0);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)u * (uintmax_t)v);
	}

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = 0, .low = UINTMAX_MAX >> 1}, INTMAX_MAX, &r, 0);
	EXPECT(r.high == UINTMAX_MAX >> 2);
	EXPECT(r.low == 1);

	r = (struct libj2_j2i){111, 222};
	mul(&(struct libj2_j2i){.high = UINTMAX_MAX >> 1, .low = UINTMAX_MAX}, INTMAX_MAX, &r, 1);
	EXPECT(r.high == UINTMAX_MAX >> 1);
	EXPECT(r.low == 2 + (uintmax_t)INTMAX_MAX);

	for (i = 0; i < 256; i++) {
		u = (intmax_t)(random_ju() >> 1);
		v = (intmax_t)(random_ju() >> 1);
		w = random_ju();

		expect_overflow = refmul(&(struct libj2_j2i){(uintmax_t)u, w}, v, &expected);

		r = (struct libj2_j2i){111, 222};
		mul(&(struct libj2_j2i){(uintmax_t)u, w}, v, &r, expect_overflow);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	}

	return 0;
}

#endif
