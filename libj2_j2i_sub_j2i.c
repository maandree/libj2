/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_sub_j2i(struct libj2_j2i *a, const struct libj2_j2i *b);


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
validate(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low, uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	int a_neg, b_neg, overflow;
	struct libj2_j2u a, b;
	struct libj2_j2i t, r;

	t = (struct libj2_j2i){.high = a_high, .low = a_low};
	if ((a_neg = libj2_j2i_is_negative(&t)))
		libj2_minus_j2i_to_j2u(&t, &a);
	else
		libj2_j2i_to_j2u(&t, &a);

	t = (struct libj2_j2i){.high = b_high, .low = b_low};
	if ((b_neg = libj2_j2i_is_negative(&t)))
		libj2_minus_j2i_to_j2u(&t, &b);
	else
		libj2_j2i_to_j2u(&t, &b);

	if (a_neg && b_neg) {
		overflow = 0;
		libj2_minus_j2u(&a);
		libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, (void *)&r);
		EXPECT(libj2_j2i_gt_j2i(&r, (const void *)&a));
	} else if (a_neg) {
		overflow = -libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, (void *)&r);
		EXPECT(overflow == 0 || overflow == -1);
		libj2_minus_j2i(&r);
		if (!libj2_j2i_is_negative(&r))
			overflow = -1;
		else if (overflow)
			EXPECT(libj2_j2i_gt_j2i(&r, (const void *)&a));
		if (!overflow)
			EXPECT(libj2_j2i_le_j2i(&r, (const void *)&a));
	} else if (b_neg) {
		overflow = +libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, (void *)&r);
		EXPECT(overflow == 0 || overflow == +1);
		if (!libj2_j2i_is_positive(&r))
			overflow = +1;
		else if (overflow)
			EXPECT(libj2_j2i_lt_j2i(&r, (const void *)&a));
		if (!overflow)
			EXPECT(libj2_j2i_gt_j2i(&r, (const void *)&a));
	} else {
		overflow = 0;
		libj2_minus_j2u(&b);
		libj2_j2u_add_j2u_to_j2u(&a, &b, (void *)&r);
		EXPECT(libj2_j2i_le_j2u(&r, &a));
	}

	EXPECT(r.high == r_high);
	EXPECT(r.low == r_low);
	EXPECT(overflow == r_overflow);
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2i a, a_saved, b, b_saved, r, expected;
	int expected_overflow;

	a.high = a_high;
	a.low = a_low;
	b.high = b_high;
	b.low = b_low;
	a_saved = a;
	b_saved = b;

#define CONST_ARG (const struct libj2_j2i *)

	expected = (struct libj2_j2i){111, 222};
	expected_overflow = libj2_j2i_sub_j2i_to_j2i_overflow(CONST_ARG &a, CONST_ARG &b, &expected);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_ne_j2i(&expected, &(struct libj2_j2i){111, 222}));

	validate(a.high, a.low, b.high, b.low, expected.high, expected.low, expected_overflow);

	r = a;
	EXPECT(libj2_j2i_sub_j2i_to_j2i_overflow(CONST_ARG &r, CONST_ARG &b, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = b;
	EXPECT(libj2_j2i_sub_j2i_to_j2i_overflow(CONST_ARG &a, CONST_ARG &r, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_sub_j2i_to_j2i_overflow(CONST_ARG &r, CONST_ARG &r, &r) == 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_sat_sub_j2i_to_j2i(CONST_ARG &a, CONST_ARG &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&r) :
	       expected_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sat_sub_j2i_to_j2i(CONST_ARG &r, CONST_ARG &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&r) :
	       expected_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));

	r = b;
	libj2_j2i_sat_sub_j2i_to_j2i(CONST_ARG &a, CONST_ARG &r, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&r) :
	       expected_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sat_sub_j2i_to_j2i(CONST_ARG &r, CONST_ARG &r, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_sub_j2i_to_j2i(CONST_ARG &a, CONST_ARG &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sub_j2i_to_j2i(CONST_ARG &r, CONST_ARG &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = b;
	libj2_j2i_sub_j2i_to_j2i(CONST_ARG &a, CONST_ARG &r, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sub_j2i_to_j2i(CONST_ARG &r, CONST_ARG &r, &r);
	EXPECT(libj2_j2i_is_zero(&r));

	EXPECT(libj2_j2i_sub_j2i_overflow_p(CONST_ARG &a, CONST_ARG &b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	EXPECT(libj2_j2i_sub_j2i_overflow_p(CONST_ARG &a, CONST_ARG &a) == 0);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	r = a;
	EXPECT(libj2_j2i_sub_j2i_overflow(&r, CONST_ARG &b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_sub_j2i_overflow(&r, CONST_ARG &r) == 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = a;
	libj2_j2i_sat_sub_j2i(&r, CONST_ARG &b);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&r) :
	       expected_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sat_sub_j2i(&r, CONST_ARG &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = a;
	libj2_j2i_sub_j2i(&r, CONST_ARG &b);
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sub_j2i(&r, CONST_ARG &r);
	EXPECT(libj2_j2i_is_zero(&r));

	EXPECT(libj2_j2i_rsub_j2i_overflow_p(&b, CONST_ARG &a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	EXPECT(libj2_j2i_rsub_j2i_overflow_p(&a, CONST_ARG &a) == 0);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	r = b;
	EXPECT(libj2_j2i_rsub_j2i_overflow(&r, CONST_ARG &a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_rsub_j2i_overflow(&r, CONST_ARG &r) == 0);
	EXPECT(libj2_j2i_is_zero(&r));

	r = b;
	libj2_j2i_sat_rsub_j2i(&r, CONST_ARG &a);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&r) :
	       expected_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sat_rsub_j2i(&r, CONST_ARG &r);
	EXPECT(libj2_j2i_is_zero(&r));

	r = b;
	libj2_j2i_rsub_j2i(&r, CONST_ARG &a);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_rsub_j2i(&r, CONST_ARG &r);
	EXPECT(libj2_j2i_is_zero(&r));
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

	for (j = 0; j < 128U; j++) {
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
