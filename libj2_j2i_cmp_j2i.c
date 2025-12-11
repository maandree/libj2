/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_cmp_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b);
/* TODO Add man page */


#else

static int
cmp_(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2i a, b, c;
	int ret;

	a.high = a_high;
	a.low = a_low;
	b.high = b_high;
	b.low = b_low;

	ret = libj2_j2i_cmp_j2i(&a, &b);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_cmp_j2i(&b, &a) == (ret ? -ret : 0));

	EXPECT(libj2_j2i_lt_j2i(&a, &b) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_le_j2i(&a, &b) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_gt_j2i(&a, &b) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_ge_j2i(&a, &b) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_eq_j2i(&a, &b) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_ne_j2i(&a, &b) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_lt_j2i(&b, &a) == (ret > 0));
	EXPECT(libj2_j2i_le_j2i(&b, &a) == (ret >= 0));
	EXPECT(libj2_j2i_gt_j2i(&b, &a) == (ret < 0));
	EXPECT(libj2_j2i_ge_j2i(&b, &a) == (ret <= 0));
	EXPECT(libj2_j2i_eq_j2i(&b, &a) == (ret == 0));
	EXPECT(libj2_j2i_ne_j2i(&b, &a) == (ret != 0));

	c = (struct libj2_j2i){111, 222};
	libj2_j2i_max_j2i_to_j2i(&a, &b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = (struct libj2_j2i){111, 222};
	libj2_j2i_max_j2i_to_j2i(&b, &a, &c);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = a;
	libj2_j2i_max_j2i(&c, &b);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = b;
	libj2_j2i_max_j2i(&c, &a);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = (struct libj2_j2i){111, 222};
	libj2_j2i_min_j2i_to_j2i(&a, &b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = (struct libj2_j2i){111, 222};
	libj2_j2i_min_j2i_to_j2i(&b, &a, &c);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = a;
	libj2_j2i_min_j2i(&c, &b);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	c = b;
	libj2_j2i_min_j2i(&c, &a);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret <= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2i_eq_j2i(&c, &b) == 1);

	return ret;
}


static int
cmp(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2i a = {.high = a_high, .low = a_low};
	struct libj2_j2i b = {.high = b_high, .low = b_low};
	int ret;

	libj2_minus_j2i(&a);
	libj2_minus_j2i(&b);

	ret = cmp_(a_high, a_low, b_high, b_low);

	EXPECT(cmp_(a_high, a_low, b.high, b.low) == (libj2_j2i_is_zero(&b) ? ret : +1));

	if (!a_high && !a_low)
		return ret;

	EXPECT(cmp_(a.high, a.low, b_high, b_low) == -1);
	EXPECT(cmp_(a.high, a.low, b.high, b.low) == -ret);

	return ret;
}


int
main(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = (uintmax_t)INTMAX_MAX;
	const uintmax_t min = (uintmax_t)INTMAX_MIN;

	EXPECT(cmp(0, 0, 0, 0) == 0);
	EXPECT(cmp(0, 0, 0, 1) == -1);
	EXPECT(cmp(0, 0, 1, 0) == -1);
	EXPECT(cmp(0, 0, 1, 1) == -1);
	EXPECT(cmp(0, 0, 0, umax) == -1);
	EXPECT(cmp(0, 0, max, 0) == -1);
	EXPECT(cmp(0, 0, max, umax) == -1);
	EXPECT(cmp(0, 0, max, umax - 1U) == -1);

	EXPECT(cmp(0, 1, 0, 1) == 0);
	EXPECT(cmp(0, 1, 1, 0) == -1);
	EXPECT(cmp(0, 1, 1, 1) == -1);
	EXPECT(cmp(0, 1, 0, umax) == -1);
	EXPECT(cmp(0, 1, max, 0) == -1);
	EXPECT(cmp(0, 1, max, umax) == -1);
	EXPECT(cmp(0, 1, max, umax - 1U) == -1);

	EXPECT(cmp(1, 0, 1, 0) == 0);
	EXPECT(cmp(1, 0, 1, 1) == -1);
	EXPECT(cmp(1, 0, 0, umax) == +1);
	EXPECT(cmp(1, 0, max, 0) == -1);
	EXPECT(cmp(1, 0, max, umax) == -1);
	EXPECT(cmp(1, 0, max, umax - 1U) == -1);

	EXPECT(cmp(1, 1, 1, 1) == 0);
	EXPECT(cmp(1, 1, 0, umax) == +1);
	EXPECT(cmp(1, 1, max, 0) == -1);
	EXPECT(cmp(1, 1, max, umax) == -1);
	EXPECT(cmp(1, 1, max, umax - 1U) == -1);

	EXPECT(cmp(0, umax, 0, umax) == 0);
	EXPECT(cmp(0, umax, max, 0) == -1);
	EXPECT(cmp(0, umax, max, umax) == -1);
	EXPECT(cmp(0, umax, max, umax - 1U) == -1);

	EXPECT(cmp(max, 0, max, 0) == 0);
	EXPECT(cmp(max, 0, max, umax) == -1);
	EXPECT(cmp(max, 0, max, umax - 1U) == -1);

	EXPECT(cmp(max, umax, max, umax) == 0);
	EXPECT(cmp(max, umax, max, umax - 1U) == +1);

	EXPECT(cmp(max, umax - 1U, max, umax - 1U) == 0);

	EXPECT(cmp_(min, 0, 0, 0) == -1);
	EXPECT(cmp_(min, 0, 0, 1) == -1);
	EXPECT(cmp_(min, 0, 1, 0) == -1);
	EXPECT(cmp_(min, 0, 1, 1) == -1);
	EXPECT(cmp_(min, 0, max, umax) == -1);
	EXPECT(cmp_(min, 0, min, 1) == -1);

	EXPECT(cmp_(0, 0, min, 0) == +1);
	EXPECT(cmp_(0, 1, min, 0) == +1);
	EXPECT(cmp_(1, 0, min, 0) == +1);
	EXPECT(cmp_(1, 1, min, 0) == +1);
	EXPECT(cmp_(max, umax, min, 0) == +1);
	EXPECT(cmp_(min, 1, min, 0) == +1);

	EXPECT(cmp_(min, 0, min, 0) == 0);
	EXPECT(cmp_(min, 1, min, 1) == 0);

	return 0;
}

#endif
