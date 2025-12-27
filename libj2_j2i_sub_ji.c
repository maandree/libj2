/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_sub_ji(struct libj2_j2i *a, intmax_t b);
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
	} else if (a_neg) {
		overflow = -libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, (void *)&r);
		libj2_minus_j2i(&r);
		if (!libj2_j2i_is_negative(&r))
			overflow = -1;
	} else if (b_neg) {
		overflow = +libj2_j2u_add_j2u_to_j2u_overflow(&a, &b, (void *)&r);
		if (!libj2_j2i_is_positive(&r))
			overflow = +1;
	} else {
		overflow = 0;
		libj2_minus_j2u(&b);
		libj2_j2u_add_j2u_to_j2u(&a, &b, (void *)&r);
	}

	EXPECT(r.high == r_high);
	EXPECT(r.low == r_low);
	EXPECT(overflow == r_overflow);
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t ub)
{
	intmax_t b = ub >> (LIBJ2_JU_BIT - 1U) ? -(intmax_t)~ub - 1 : (intmax_t)ub;
	struct libj2_j2i a, a_saved, r, expected;
	int expected_overflow;

#if INTMAX_MIN + 1 != -INTMAX_MAX
	if (ub == (UINTMAX >> 1) + 1U)
		return;
#endif

	a.high = a_high;
	a.low = a_low;
	a_saved = a;
	expected = (struct libj2_j2i){111, 222};
	expected_overflow = libj2_j2i_sub_ji_to_j2i_overflow((const struct libj2_j2i *)&a, b, &expected);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_ne_j2i(&expected, &(struct libj2_j2i){111, 222}));

	validate(a.high, a.low, b < 0 ? UINTMAX_MAX : 0U, ub, expected.high, expected.low, expected_overflow);

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_sub_ji_to_j2i((const struct libj2_j2i *)&a, b, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sub_ji_to_j2i((const struct libj2_j2i *)&r, b, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	a_saved = a;
	EXPECT(libj2_j2i_sub_ji_overflow_p((const struct libj2_j2i *)&a, b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	r = a;
	EXPECT(libj2_j2i_sub_ji_overflow(&r, b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_j2i_sub_ji(&r, b);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	libj2_minus_j2i(&expected);

	a = a_saved;
	r = (struct libj2_j2i){111, 222};
	expected_overflow = libj2_ji_sub_j2i_to_j2i_overflow(b, (const struct libj2_j2i *)&a, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	validate(b < 0 ? UINTMAX_MAX : 0U, ub, a.high, a.low, expected.high, expected.low, expected_overflow);

	EXPECT(libj2_ji_sub_j2i_overflow_p(b, (const struct libj2_j2i *)&a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_sub_j2i_to_j2i(b, (const struct libj2_j2i *)&a, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	libj2_ji_sub_j2i_to_j2i(b, (const struct libj2_j2i *)&r, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_ji_sub_j2i_to_j2i_overflow(b, (const struct libj2_j2i *)&r, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	r = a;
	EXPECT(libj2_j2i_rsub_ji_overflow(&r, b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));

	EXPECT(libj2_j2i_rsub_ji_overflow_p((const struct libj2_j2i *)&a, b) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	r = a;
	libj2_j2i_rsub_ji(&r, b);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
}


int
main(void)
{
	uintmax_t a, b, c, max, min, umax, vs[12];
	unsigned i, ii, iii, k, j;

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
		for (k = 0; k < 8U; k++) {
			a = random_ju() >> 1;
			b = random_ju() >> 1;
			c = random_ju() >> 1;
			if (k & 1U) a = ~a;
			if (k & 2U) b = ~b;
			if (k & 4U) c = ~c;
			check(a, b, c);
			for (i = 0; k < 4U && i < 12U; i++) {
				check(a, b, vs[i]);
				check(a, vs[i], b);
				check(vs[i], a, b);
				for (ii = 0; k < 2U && ii < 12U; ii++) {
					check(vs[i], vs[ii], a);
					check(vs[i], a, vs[ii]);
					check(a, vs[i], vs[ii]);
					for (iii = 0; !j && k < 1U && iii < 12U; iii++)
						check(vs[i], vs[ii], vs[iii]);
				}
			}
		}
	}

	return 0;
}

#endif
