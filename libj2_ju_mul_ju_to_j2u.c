/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_mul_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res);
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
mul(uintmax_t a, uintmax_t b, struct libj2_j2u *expected)
{
	struct libj2_j2u c;
	unsigned i;

	libj2_j2u_zero(expected);
	for (i = 0; i < LIBJ2_JU_BIT; i++, b >>= 1) {
		if (b & 1U) {
			libj2_ju_lsh_to_j2u(a, i, &c);
			libj2_j2u_add_j2u(expected, &c);
		}
	}
}


int
main(void)
{
	struct libj2_j2u r, expected;
	uintmax_t u, v;
	unsigned i;

	srand((unsigned)time(NULL));

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(0, 0, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(0, 1, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(0, UINTMAX_MAX, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(1, 0, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(UINTMAX_MAX, 0, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2u){111, 222};
		libj2_ju_mul_ju_to_j2u(0, random_ju(), &r);
		EXPECT(libj2_j2u_is_zero(&r));

		r = (struct libj2_j2u){111, 222};
		libj2_ju_mul_ju_to_j2u(random_ju(), 0, &r);
		EXPECT(libj2_j2u_is_zero(&r));
	}

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(1, 1, &r);
	EXPECT(r.high == 0);
	EXPECT(r.low == 1);

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(4, 4, &r);
	EXPECT(r.high == 0);
	EXPECT(r.low == 16);

	for (i = 0; i < 32; i++) {
		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		libj2_ju_mul_ju_to_j2u(1, v, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == v);

		r = (struct libj2_j2u){111, 222};
		v = random_ju();
		libj2_ju_mul_ju_to_j2u(v, 1, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == v);
	}

	for (i = 0; i < 32; i++) {
		u = random_hju();
		v = random_hju();

		r = (struct libj2_j2u){111, 222};
		libj2_ju_mul_ju_to_j2u(u, v, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == u * v);

		libj2_ju_mul_ju_to_j2u(v, u, &r);
		EXPECT(r.high == 0);
		EXPECT(r.low == u * v);
	}

	r = (struct libj2_j2u){111, 222};
	libj2_ju_mul_ju_to_j2u(UINTMAX_MAX, UINTMAX_MAX, &r);
	EXPECT(r.high == UINTMAX_MAX - 1U);
	EXPECT(r.low == 1);

	for (i = 0; i < 256; i++) {
		u = random_ju();
		v = random_ju();

		mul(u, v, &expected);

		r = (struct libj2_j2u){111, 222};
		libj2_ju_mul_ju_to_j2u(u, v, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		libj2_ju_mul_ju_to_j2u(v, u, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	}

	return 0;
}

#endif
