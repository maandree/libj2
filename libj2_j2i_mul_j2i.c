/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_mul_j2i(struct libj2_j2i *a, const struct libj2_j2i *b);


#else

#define CONST_ARG (const struct libj2_j2i *)


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


static int
refmul(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *r)
{
	int overflow, neg = libj2_j2i_is_negative(a) ^ libj2_j2i_is_negative(b);
	struct libj2_j2u ulimit, u, v, w;
	struct libj2_j2i ilimit;

	libj2_abs_j2i_to_j2u(a, &u);
	libj2_abs_j2i_to_j2u(b, &v);
	overflow = libj2_j2u_mul_j2u_to_j2u_overflow(&u, &v, &w);
	libj2_j2u_to_j2i(&w, r);
	if (neg)
		libj2_j2i_min(&ilimit);
	else
		libj2_j2i_max(&ilimit);
	libj2_abs_j2i_to_j2u(&ilimit, &ulimit);
	if (libj2_j2u_gt_j2u(&w, &ulimit))
		overflow = 1;
	if (neg)
		libj2_minus_j2i(r);

	return neg ? -overflow : +overflow;
}


static int
check_double(uintmax_t a_high, uintmax_t a_low, struct libj2_j2i *r_out)
{
	struct libj2_j2i a = {.high = a_high, .low = a_low}, a_saved = a;
	struct libj2_j2i r, expected;
	int expected_overflow, r_set;
	enum libj2_overflow overflow;

	expected_overflow = refmul(&a, &a, &expected);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(expected_overflow >= 0);

	r = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow(CONST_ARG &a, CONST_ARG &a, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow(CONST_ARG &r, CONST_ARG &r, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_mul_j2i_overflow(&r, CONST_ARG &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_mul_j2i_to_j2i(CONST_ARG &a, CONST_ARG &a, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_mul_j2i_to_j2i(CONST_ARG &r, CONST_ARG &r, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_mul_j2i(&r, CONST_ARG &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	EXPECT(libj2_j2i_mul_j2i_overflow_p(CONST_ARG &a, CONST_ARG &a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	r = (struct libj2_j2i){111, 222};
	r_set = 999;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow_p(CONST_ARG &a, CONST_ARG &a, &r, &r_set) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(r_set == 0 || r_set == 1);
	EXPECT(libj2_j2i_eq_j2i(&r, r_set ? &expected : &(struct libj2_j2i){111, 222}));

	r = a;
	r_set = 999;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow_p(CONST_ARG &r, CONST_ARG &r, &r, &r_set) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(r_set == 0 || r_set == 1);
	EXPECT(libj2_j2i_eq_j2i(&r, r_set ? &expected : &a_saved));

	overflow = libj2_j2i_mul_j2i_overflow_p_quick(CONST_ARG &a, CONST_ARG &a);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(overflow == LIBJ2_POSITIVE_OVERFLOW_UNKNOWN || (int)overflow == expected_overflow);

	*r_out = expected;
	return expected_overflow;
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2i a = {.high = a_high, .low = a_low}, a_saved = a;
	struct libj2_j2i b = {.high = b_high, .low = b_low}, b_saved = b;
	struct libj2_j2i r, expected;
	int expected_overflow, r_set;
	enum libj2_overflow overflow;

	expected_overflow = refmul(&a, &b, &expected);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	if (a_high == b_high && a_low == b_low) {
		r = (struct libj2_j2i){111, 222};
		EXPECT(check_double(a_high, a_low, &r) == expected_overflow);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	}

	r = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow(CONST_ARG &a, CONST_ARG &b, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_mul_j2i_to_j2i(CONST_ARG &a, CONST_ARG &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow(CONST_ARG &r, CONST_ARG &b, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_mul_j2i_to_j2i(CONST_ARG &r, CONST_ARG &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = b;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow(CONST_ARG &a, CONST_ARG &r, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = b;
	libj2_j2i_mul_j2i_to_j2i(CONST_ARG &a, CONST_ARG &r, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_mul_j2i_overflow(&r, CONST_ARG &b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_mul_j2i(&r, CONST_ARG &b);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	EXPECT(libj2_j2i_mul_j2i_overflow_p(CONST_ARG &a, CONST_ARG &b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	r = (struct libj2_j2i){111, 222};
	r_set = 999;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow_p(CONST_ARG &a, CONST_ARG &b, &r, &r_set) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(r_set == 0 || r_set == 1);
	EXPECT(libj2_j2i_eq_j2i(&r, r_set ? &expected : &(struct libj2_j2i){111, 222}));

	r = a;
	r_set = 999;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow_p(CONST_ARG &r, CONST_ARG &b, &r, &r_set) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(r_set == 0 || r_set == 1);
	EXPECT(libj2_j2i_eq_j2i(&r, r_set ? &expected : &a_saved));

	r = b;
	r_set = 999;
	EXPECT(libj2_j2i_mul_j2i_to_j2i_overflow_p(CONST_ARG &a, CONST_ARG &r, &r, &r_set) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(r_set == 0 || r_set == 1);
	EXPECT(libj2_j2i_eq_j2i(&r, r_set ? &expected : &b_saved));

	overflow = libj2_j2i_mul_j2i_overflow_p_quick(CONST_ARG &a, CONST_ARG &b);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	if (libj2_j2i_is_zero(&a) || libj2_j2i_is_zero(&b))
		EXPECT(overflow == LIBJ2_NO_OVERFLOW);
	if (overflow == LIBJ2_POSITIVE_OVERFLOW_UNKNOWN) {
		EXPECT(expected_overflow >= 0);
		EXPECT(libj2_sgn_j2i(&a) == libj2_sgn_j2i(&b));
	} else if (overflow == LIBJ2_NEGATIVE_OVERFLOW_UNKNOWN) {
		EXPECT(expected_overflow <= 0);
		EXPECT(libj2_sgn_j2i(&a) == -libj2_sgn_j2i(&b));
	} else {
		EXPECT((int)overflow == expected_overflow);
	}
}


int
main(void)
{
	uintmax_t a, b, c, d, max, min, umax, vs[12];
	unsigned i, ii, iii, iv, k, j;

	srand((unsigned)time(NULL));

	umax = UINTMAX_MAX;
	max = umax >> 1;
	min = ~max;

	vs[0] = 0U;
	vs[1] = 1U;
	vs[2] = 2U;
	vs[3] = umax - 0U;
	vs[4] = umax - 1U;
	vs[5] = umax - 2U;
	vs[6] = max - 0U;
	vs[7] = max - 1U;
	vs[8] = max - 2U;
	vs[9] = min + 0U;
	vs[10] = min + 1U;
	vs[11] = min + 2U;

	for (j = 0; j < 32U; j++) {
		for (k = 0; k < 16U; k++) {
			a = random_ju() >> 1;
			b = random_ju() >> 1;
			c = random_ju() >> 1;
			d = random_ju() >> 1;
			if (k & 1U) a = ~a;
			if (k & 2U) b = ~b;
			if (k & 4U) c = ~c;
			if (k & 8U) d = ~d;
			check(a, b, c, d);
			for (i = 0; k < 8U && i < 12U; i++) {
				check(vs[i], a, b, c);
				check(a, vs[i], b, c);
				check(a, b, vs[i], c);
				check(a, b, c, vs[i]);
				for (ii = 0; k < 4U && ii < 12U; ii++) {
					check(vs[i], vs[ii], a, b);
					check(vs[i], a, vs[ii], b);
					check(vs[i], a, b, vs[ii]);
					check(a, vs[i], vs[ii], b);
					check(a, vs[i], b, vs[ii]);
					check(a, b, vs[i], vs[ii]);
					for (iii = 0; k < 2U && iii < 12U; iii++) {
						check(vs[i], vs[ii], vs[iii], a);
						check(vs[i], vs[ii], a, vs[iii]);
						check(vs[i], a, vs[ii], vs[iii]);
						check(a, vs[i], vs[ii], vs[iii]);
						for (iv = 0; !j && k < 1U && iv < 12U; iv++)
							check(vs[i], vs[ii], vs[iii], vs[iv]);
					}
				}
			}
		}
	}

	return 0;
}

#endif
