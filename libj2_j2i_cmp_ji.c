/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_cmp_ji(const struct libj2_j2i *a, intmax_t b);


#else

static int
cmp_(uintmax_t a_high, uintmax_t a_low, intmax_t b)
{
	struct libj2_j2i a, c;
	int ret;

	a.high = a_high;
	a.low = a_low;

	ret = libj2_j2i_cmp_ji(&a, b);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ji_cmp_j2i(b, &a) == (ret ? -ret : 0));

	EXPECT(libj2_j2i_lt_ji(&a, b) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_le_ji(&a, b) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_gt_ji(&a, b) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_ge_ji(&a, b) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_eq_ji(&a, b) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_ne_ji(&a, b) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ji_lt_j2i(b, &a) == (ret > 0));
	EXPECT(libj2_ji_le_j2i(b, &a) == (ret >= 0));
	EXPECT(libj2_ji_gt_j2i(b, &a) == (ret < 0));
	EXPECT(libj2_ji_ge_j2i(b, &a) == (ret <= 0));
	EXPECT(libj2_ji_eq_j2i(b, &a) == (ret == 0));
	EXPECT(libj2_ji_ne_j2i(b, &a) == (ret != 0));

	c = (struct libj2_j2i){111, 222};
	libj2_j2i_max_ji_to_j2i(&a, b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_ji(&c, b) == 1);

	c = a;
	libj2_j2i_max_ji(&c, b);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_ji(&c, b) == 1);

	c = (struct libj2_j2i){111, 222};
	libj2_j2i_min_ji_to_j2i(&a, b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_ji(&c, b) == 1);

	c = a;
	libj2_j2i_min_ji(&c, b);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_ji(&c, b) == 1);

	return ret;
}


static int
cmp(uintmax_t a_high, uintmax_t a_low, uintmax_t b)
{
	struct libj2_j2i a;
	int ret;

	ret = cmp_(a_high, a_low, +(intmax_t)b);

	EXPECT(cmp_(a_high, a_low, -(intmax_t)b) == (b ? +1 : ret));

	if (!a_high && !a_low)
		return ret;

	a.high = a_high;
	a.low = a_low;
	libj2_minus_j2i(&a);

	EXPECT(cmp_(a.high, a.low, +(intmax_t)b) == -1);
	EXPECT(cmp_(a.high, a.low, -(intmax_t)b) == -ret);

	return ret;
}


int
main(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = (uintmax_t)INTMAX_MAX;
	const uintmax_t min = (uintmax_t)INTMAX_MIN;

	EXPECT(cmp(0, 0, 0) == 0);
	EXPECT(cmp(0, 1, 0) == +1);
	EXPECT(cmp(1, 0, 0) == +1);
	EXPECT(cmp(1, 1, 0) == +1);
	EXPECT(cmp(0, umax, 0) == +1);
	EXPECT(cmp(max, 0, 0) == +1);
	EXPECT(cmp(max, umax, 0) == +1);
	EXPECT(cmp(max, umax - 1U, 0) == +1);

	EXPECT(cmp(0, 0, 1) == -1);
	EXPECT(cmp(0, 1, 1) == 0);
	EXPECT(cmp(1, 0, 1) == +1);
	EXPECT(cmp(1, 1, 1) == +1);
	EXPECT(cmp(0, umax, 1) == +1);
	EXPECT(cmp(max, 0, 1) == +1);
	EXPECT(cmp(max, umax, 1) == +1);
	EXPECT(cmp(max, umax - 1U, 1) == +1);

	EXPECT(cmp(0, 0, 2) == -1);
	EXPECT(cmp(0, 1, 2) == -1);
	EXPECT(cmp(1, 0, 2) == +1);
	EXPECT(cmp(1, 1, 2) == +1);
	EXPECT(cmp(0, umax, 2) == +1);
	EXPECT(cmp(max, 0, 2) == +1);
	EXPECT(cmp(max, umax, 2) == +1);
	EXPECT(cmp(max, umax - 1U, 2) == +1);

	EXPECT(cmp(0, 0, max) == -1);
	EXPECT(cmp(0, 1, max) == -1);
	EXPECT(cmp(1, 0, max) == +1);
	EXPECT(cmp(1, 1, max) == +1);
	EXPECT(cmp(0, umax, max) == +1);
	EXPECT(cmp(0, max, max) == 0);
	EXPECT(cmp(0, max + 1U, max) == +1);
	EXPECT(cmp(max, 0, max) == +1);
	EXPECT(cmp(max, umax, max) == +1);
	EXPECT(cmp(max, umax - 1U, max) == +1);

	EXPECT(cmp(0, 0, max - 1U) == -1);
	EXPECT(cmp(0, 1, max - 1U) == -1);
	EXPECT(cmp(1, 0, max - 1U) == +1);
	EXPECT(cmp(1, 1, max - 1U) == +1);
	EXPECT(cmp(0, umax, max - 1U) == +1);
	EXPECT(cmp(max, 0, max - 1U) == +1);
	EXPECT(cmp(max, umax, max - 1U) == +1);
	EXPECT(cmp(max, umax - 1U, max - 1U) == +1);

	EXPECT(cmp_(min, 0, 0) == -1);
	EXPECT(cmp_(min, 0, 1) == -1);
	EXPECT(cmp_(min, 0, (intmax_t)max) == -1);

	EXPECT(cmp_(0, 0, (intmax_t)min) == +1);
	EXPECT(cmp_(0, 1, (intmax_t)min) == +1);
	EXPECT(cmp_(1, 0, (intmax_t)min) == +1);
	EXPECT(cmp_(1, 1, (intmax_t)min) == +1);
	EXPECT(cmp_(max, umax, (intmax_t)min) == +1);
	EXPECT(cmp_(min, 1, (intmax_t)min) == -1);

	EXPECT(cmp_(min, 0, (intmax_t)min) == -1);
	EXPECT(cmp_(umax, min, (intmax_t)min) == 0);

	return 0;
}

#endif
