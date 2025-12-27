/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_ji_cmp_j2u(intmax_t a, const struct libj2_j2u *b);


#else

static int
cmp_(intmax_t a, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2u b;
	int ret;

	b.high = b_high;
	b.low = b_low;

	ret = libj2_ji_cmp_j2u(a, &b);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_ji_lt_j2u(a, &b) == (ret < 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_ji_le_j2u(a, &b) == (ret <= 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_ji_gt_j2u(a, &b) == (ret > 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_ji_ge_j2u(a, &b) == (ret >= 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_ji_eq_j2u(a, &b) == (ret == 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_ji_ne_j2u(a, &b) == (ret != 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_cmp_ji(&b, a) == (ret ? -ret : 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_lt_ji(&b, a) == (ret > 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_le_ji(&b, a) == (ret >= 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_gt_ji(&b, a) == (ret < 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_ge_ji(&b, a) == (ret <= 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_eq_ji(&b, a) == (ret == 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_ne_ji(&b, a) == (ret != 0));
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	return ret;
}


static int
cmp(uintmax_t a_unsigned, uintmax_t b_high, uintmax_t b_low)
{
	intmax_t a = (intmax_t)a_unsigned;
	int ret;

	ret = cmp_(a, b_high, b_low);

	if (a)
		EXPECT(cmp_(-a, b_high, b_low) == -1);

	return ret;
}


int
main(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;

	EXPECT(cmp(0, 0, 0) == 0);
	EXPECT(cmp(0, 0, 1) == -1);
	EXPECT(cmp(0, 1, 0) == -1);
	EXPECT(cmp(0, 1, 1) == -1);
	EXPECT(cmp(0, 0, umax) == -1);
	EXPECT(cmp(0, max, 0) == -1);
	EXPECT(cmp(0, max, umax) == -1);
	EXPECT(cmp(0, max, umax - 1U) == -1);
	EXPECT(cmp(0, umax, 0) == -1);
	EXPECT(cmp(0, umax, umax) == -1);
	EXPECT(cmp(0, umax, umax - 1U) == -1);

	EXPECT(cmp(1, 0, 0) == +1);
	EXPECT(cmp(1, 0, 1) == 0);
	EXPECT(cmp(1, 1, 0) == -1);
	EXPECT(cmp(1, 1, 1) == -1);
	EXPECT(cmp(1, 0, umax) == -1);
	EXPECT(cmp(1, max, 0) == -1);
	EXPECT(cmp(1, max, umax) == -1);
	EXPECT(cmp(1, max, umax - 1U) == -1);
	EXPECT(cmp(1, umax, 0) == -1);
	EXPECT(cmp(1, umax, umax) == -1);
	EXPECT(cmp(1, umax, umax - 1U) == -1);

	EXPECT(cmp(max, 0, 0) == +1);
	EXPECT(cmp(max, 0, 1) == +1);
	EXPECT(cmp(max, 1, 0) == -1);
	EXPECT(cmp(max, 1, 1) == -1);
	EXPECT(cmp(max, 0, max) == 0);
	EXPECT(cmp(max, 0, umax) == -1);
	EXPECT(cmp(max, max, 0) == -1);
	EXPECT(cmp(max, max, umax) == -1);
	EXPECT(cmp(max, max, umax - 1U) == -1);
	EXPECT(cmp(max, umax, 0) == -1);
	EXPECT(cmp(max, umax, umax) == -1);
	EXPECT(cmp(max, umax, umax - 1U) == -1);

	EXPECT(cmp_(INTMAX_MIN, 0, 0) == -1);
	EXPECT(cmp_(INTMAX_MIN, 0, 1) == -1);
	EXPECT(cmp_(INTMAX_MIN, 1, 0) == -1);
	EXPECT(cmp_(INTMAX_MIN, 1, 1) == -1);
	EXPECT(cmp_(INTMAX_MIN, 0, umax) == -1);
	EXPECT(cmp_(INTMAX_MIN, max, 0) == -1);
	EXPECT(cmp_(INTMAX_MIN, max, umax) == -1);
	EXPECT(cmp_(INTMAX_MIN, max, umax - 1U) == -1);
	EXPECT(cmp_(INTMAX_MIN, umax, 0) == -1);
	EXPECT(cmp_(INTMAX_MIN, umax, umax) == -1);
	EXPECT(cmp_(INTMAX_MIN, umax, umax - 1U) == -1);
	EXPECT(cmp_(INTMAX_MIN, ~max, 0) == -1);
	EXPECT(cmp_(INTMAX_MIN, 0, ~max) == -1);

	return 0;
}

#endif
