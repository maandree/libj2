/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_add_ji(struct libj2_j2i *a, intmax_t b);
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
self_check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
           uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	uintmax_t a_neg = a_high >> (LIBJ2_JU_BIT - 1U);
	uintmax_t b_neg = b_high >> (LIBJ2_JU_BIT - 1U);
	uintmax_t carry = 0;
	unsigned i;
	int overflow;

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a_low >> i) & 1U;
		carry += (b_low >> i) & 1U;
		EXPECT((carry & 1U) == ((r_low >> i) & 1U));
		carry >>= 1;
	}

	for (i = 0; i < LIBJ2_JU_BIT - 1U; i++) {
		carry += (a_high >> i) & 1U;
		carry += (b_high >> i) & 1U;
		EXPECT((carry & 1U) == ((r_high >> i) & 1U));
		carry >>= 1;
	}

	carry += (a_high >> i) & 1U;
	carry += (b_high >> i) & 1U;
	r_high |= (carry & 1U) << i;
	carry >>= 1;

	if (a_neg)
		carry ^= 1U;

	if (a_neg ^ b_neg)
		overflow = 0;
	else if (a_neg)
		overflow = -!(r_high >> (LIBJ2_JU_BIT - 1U));
	else
		overflow = !!(r_high >> (LIBJ2_JU_BIT - 1U));

	EXPECT(r_overflow == overflow);
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t ub)
{
	intmax_t b = ub > (uintmax_t)INTMAX_MAX ? (intmax_t)ub : -(intmax_t)~ub - 1;
	struct libj2_j2i a, r;
	uintmax_t expected_high, expected_low;
	int expected_overflow;

#if INTMAX_MIN + 1 != -INTMAX_MAX
	if (ub == ~(UINTMAX_MAX >> 1))
		return;
#endif

	expected_high = a_high + (uintmax_t)(a_low > UINTMAX_MAX - ub);
	expected_low = a_low + ub;
	if (b < 0)
		expected_high += UINTMAX_MAX;
	if (a_high >> (LIBJ2_JU_BIT - 1U) && b < 0)
		expected_overflow = expected_high >> (LIBJ2_JU_BIT - 1U) ? 0 : -1;
	else if (b < 0 || a_high >> (LIBJ2_JU_BIT - 1U))
		expected_overflow = 0;
	else
		expected_overflow = expected_high >> (LIBJ2_JU_BIT - 1U) ? +1 : 0;

	self_check(a_high, a_low, b < 0 ? UINTMAX_MAX : 0U, ub, expected_high, expected_low, expected_overflow);

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_j2i_add_ji(&a, b);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_j2i_add_ji_overflow(&a, b) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

#if 0 /* TODO saturated addition */
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_j2i_sat_add_ji(&a, b);
	EXPECT(a.high == (expected_overflow ? UINTMAX_MAX : expected_high));
	EXPECT(a.low == (expected_overflow ? UINTMAX_MAX : expected_low));
#endif

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_j2i_add_ji_overflow_p((const struct libj2_j2i *)&a, b) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	r = (struct libj2_j2i){111, 222};
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_j2i_add_ji_to_j2i(&a, b, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_j2i_add_ji_to_j2i(&a, b, &a);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2i){111, 222};
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_j2i_add_ji_to_j2i_overflow(&a, b, &r) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_j2i_add_ji_to_j2i_overflow(&a, b, &a) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

#if 0 /* TODO saturated addition */
	r = (struct libj2_j2i){111, 222};
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_j2i_sat_add_ji_to_j2i(&a, b, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == (expected_overflow ? UINTMAX_MAX : expected_high));
	EXPECT(r.low == (expected_overflow ? UINTMAX_MAX : expected_low));

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_j2i_sat_add_ji_to_j2i(&a, b, &a);
	EXPECT(a.high == (expected_overflow ? UINTMAX_MAX : expected_high));
	EXPECT(a.low == (expected_overflow ? UINTMAX_MAX : expected_low));
#endif

	r = (struct libj2_j2i){111, 222};
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_ji_add_j2i_to_j2i(b, &a, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_ji_add_j2i_to_j2i(b, &a, &a);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2i){111, 222};
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_ji_add_j2i_to_j2i_overflow(b, &a, &r) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_ji_add_j2i_to_j2i_overflow(b, &a, &a) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

#if 0 /* TODO saturated addition */
	r = (struct libj2_j2i){111, 222};
	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_ji_sat_add_j2i_to_j2i(b, &a, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == (expected_overflow ? UINTMAX_MAX : expected_high));
	EXPECT(r.low == (expected_overflow ? UINTMAX_MAX : expected_low));

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	libj2_ji_sat_add_j2i_to_j2i(b, &a, &a);
	EXPECT(a.high == (expected_overflow ? UINTMAX_MAX : expected_high));
	EXPECT(a.low == (expected_overflow ? UINTMAX_MAX : expected_low));
#endif

	a = (struct libj2_j2i){.high = a_high, .low = a_low};
	EXPECT(libj2_ji_add_j2i_overflow_p(b, (const struct libj2_j2i *)&a) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
}


int
main(void)
{
	uintmax_t a, b, c, max, min, umax, vs[12];
	unsigned i, j, k;

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

	for (i = 0; i < 12U; i++)
		for (j = 0; j < 12U; j++)
			for (k = 0; k < 12U; k++)
				check(vs[i], vs[j], vs[k]);

	for (k = 0; k < 256; k++) {
		a = random_ju();
		b = random_ju();
		c = random_ju();
		for (i = 0; i < 12U; i++) {
			for (j = 0; j < 12U; j++) {
				check(a, vs[i], vs[j]);
				check(vs[i], a, vs[j]);
				check(vs[i], vs[j], a);
			}
			check(a, b, vs[i]);
			check(a, vs[i], b);
			check(vs[i], a, b);
		}
		check(a, b, c);
	}

	return 0;
}

#endif
