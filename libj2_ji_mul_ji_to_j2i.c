/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ji_mul_ji_to_j2i(intmax_t a, intmax_t b, struct libj2_j2i *res);


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

static intmax_t
random_ji(void)
{
	uintmax_t u;
	u = random_small_ju(LIBJ2_JU_BIT);
	if (u >> (LIBJ2_JU_BIT - 1U))
		return (intmax_t)u;
	return (intmax_t)~u - 1;
}


static void
mul(intmax_t a, intmax_t b, struct libj2_j2i *expected)
{
	int neg = (a < 0) ^ (b < 0);
	uintmax_t u = a < 0 ? (uintmax_t)-(a + 1U) + 1U : (uintmax_t)a;
	uintmax_t v = b < 0 ? (uintmax_t)-(b + 1U) + 1U : (uintmax_t)b;
	struct libj2_j2u c;
	libj2_ju_mul_ju_to_j2u(u, v, &c);
	libj2_j2u_to_j2i(&c, expected);
	if (neg)
		libj2_minus_j2i(expected);
}


int
main(void)
{
	struct libj2_j2i r, expected;
	intmax_t u, v;
	unsigned i;

	srand((unsigned)time(NULL));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(0, 0, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(0, 1, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(0, -1, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(0, INTMAX_MAX, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(0, -INTMAX_MAX, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(0, INTMAX_MIN, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(1, 0, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(-1, 0, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(INTMAX_MAX, 0, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(-INTMAX_MAX, 0, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(INTMAX_MIN, 0, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2i){111, 222};
		libj2_ji_mul_ji_to_j2i(0, random_ji(), &r);
		EXPECT(libj2_j2i_is_zero(&r));

		r = (struct libj2_j2i){111, 222};
		libj2_ji_mul_ji_to_j2i(random_ji(), 0, &r);
		EXPECT(libj2_j2i_is_zero(&r));
	}

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(1, 1, &r);
	EXPECT(r.high == 0);
	EXPECT(r.low == 1);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(4, 4, &r);
	EXPECT(r.high == 0);
	EXPECT(r.low == 16);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(2, 3, &r);
	EXPECT(libj2_j2i_eq_ji(&r, 6));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(2, -3, &r);
	EXPECT(libj2_j2i_eq_ji(&r, -6));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(-2, 3, &r);
	EXPECT(libj2_j2i_eq_ji(&r, -6));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(-2, -3, &r);
	EXPECT(libj2_j2i_eq_ji(&r, 6));

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2i){111, 222};
		v = (intmax_t)(random_ju() >> 1);
		libj2_ji_mul_ji_to_j2i(1, v, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)v);

		r = (struct libj2_j2i){111, 222};
		v = (intmax_t)(random_ju() >> 1);
		libj2_ji_mul_ji_to_j2i(v, 1, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)v);
	}

	for (i = 0; i < 32; i++) {
		u = (intmax_t)random_hju();
		v = (intmax_t)random_hju();

		r = (struct libj2_j2i){111, 222};
		libj2_ji_mul_ji_to_j2i(u, v, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)u * (uintmax_t)v);

		libj2_ji_mul_ji_to_j2i(v, u, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == (uintmax_t)u * (uintmax_t)v);
	}

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(INTMAX_MAX, INTMAX_MAX, &r);
	EXPECT(r.high == (uintmax_t)INTMAX_MAX >> 1);
	EXPECT(r.low == 1);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(INTMAX_MAX, -INTMAX_MAX, &r);
	libj2_minus_j2i(&r);
	EXPECT(r.high == (uintmax_t)INTMAX_MAX >> 1);
	EXPECT(r.low == 1);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(-INTMAX_MAX, INTMAX_MAX, &r);
	libj2_minus_j2i(&r);
	EXPECT(r.high == (uintmax_t)INTMAX_MAX >> 1);
	EXPECT(r.low == 1);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(-INTMAX_MAX, -INTMAX_MAX, &r);
	EXPECT(r.high == (uintmax_t)INTMAX_MAX >> 1);
	EXPECT(r.low == 1);

#if INTMAX_MIN + 1 == -INTMAX_MAX
	r = (struct libj2_j2i){111, 222};
	libj2_ji_mul_ji_to_j2i(INTMAX_MIN, INTMAX_MIN, &r);
	EXPECT(r.high == ((uintmax_t)INTMAX_MAX + 1U) >> 1);
	EXPECT(r.low == 0);
#endif

	for (i = 0; i < 256; i++) {
		u = random_ji();
		v = random_ji();

		mul(u, v, &expected);

		r = (struct libj2_j2i){111, 222};
		libj2_ji_mul_ji_to_j2i(u, v, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));

		libj2_ji_mul_ji_to_j2i(v, u, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	}

	return 0;
}

#endif
