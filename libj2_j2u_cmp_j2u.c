/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_cmp_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b);
/* TODO Add man page */


#else

static int
cmp(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2u a, b, c;
	int ret;

	a.high = a_high;
	a.low = a_low;
	b.high = b_high;
	b.low = b_low;

	ret = libj2_j2u_cmp_j2u(&a, &b);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_cmp_j2u(&b, &a) == (ret ? -ret : 0));

	EXPECT(libj2_j2u_lt_j2u(&a, &b) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_le_j2u(&a, &b) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_gt_j2u(&a, &b) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_ge_j2u(&a, &b) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_eq_j2u(&a, &b) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_ne_j2u(&a, &b) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_lt_j2u(&b, &a) == (ret > 0));
	EXPECT(libj2_j2u_le_j2u(&b, &a) == (ret >= 0));
	EXPECT(libj2_j2u_gt_j2u(&b, &a) == (ret < 0));
	EXPECT(libj2_j2u_ge_j2u(&b, &a) == (ret <= 0));
	EXPECT(libj2_j2u_eq_j2u(&b, &a) == (ret == 0));
	EXPECT(libj2_j2u_ne_j2u(&b, &a) == (ret != 0));

	c = (struct libj2_j2u){111, 222};
	libj2_j2u_max_j2u_to_j2u(&a, &b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = (struct libj2_j2u){111, 222};
	libj2_j2u_max_j2u_to_j2u(&b, &a, &c);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = a;
	libj2_j2u_max_j2u(&c, &b);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = b;
	libj2_j2u_max_j2u(&c, &a);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = (struct libj2_j2u){111, 222};
	libj2_j2u_min_j2u_to_j2u(&a, &b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = (struct libj2_j2u){111, 222};
	libj2_j2u_min_j2u_to_j2u(&b, &a, &c);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = a;
	libj2_j2u_min_j2u(&c, &b);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	c = b;
	libj2_j2u_min_j2u(&c, &a);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &b) == 1);

	return ret;
}


int
main(void)
{
	const uintmax_t max = UINTMAX_MAX;

	EXPECT(cmp(0, 0, 0, 0) == 0);
	EXPECT(cmp(0, 0, 0, 1) == -1);
	EXPECT(cmp(0, 0, 1, 0) == -1);
	EXPECT(cmp(0, 0, 1, 1) == -1);
	EXPECT(cmp(0, 0, 0, max) == -1);
	EXPECT(cmp(0, 0, max, 0) == -1);
	EXPECT(cmp(0, 0, max, max) == -1);
	EXPECT(cmp(0, 0, max, max - 1U) == -1);

	EXPECT(cmp(0, 1, 0, 1) == 0);
	EXPECT(cmp(0, 1, 1, 0) == -1);
	EXPECT(cmp(0, 1, 1, 1) == -1);
	EXPECT(cmp(0, 1, 0, max) == -1);
	EXPECT(cmp(0, 1, max, 0) == -1);
	EXPECT(cmp(0, 1, max, max) == -1);
	EXPECT(cmp(0, 1, max, max - 1U) == -1);

	EXPECT(cmp(1, 0, 1, 0) == 0);
	EXPECT(cmp(1, 0, 1, 1) == -1);
	EXPECT(cmp(1, 0, 0, max) == +1);
	EXPECT(cmp(1, 0, max, 0) == -1);
	EXPECT(cmp(1, 0, max, max) == -1);
	EXPECT(cmp(1, 0, max, max - 1U) == -1);

	EXPECT(cmp(1, 1, 1, 1) == 0);
	EXPECT(cmp(1, 1, 0, max) == +1);
	EXPECT(cmp(1, 1, max, 0) == -1);
	EXPECT(cmp(1, 1, max, max) == -1);
	EXPECT(cmp(1, 1, max, max - 1U) == -1);

	EXPECT(cmp(0, max, 0, max) == 0);
	EXPECT(cmp(0, max, max, 0) == -1);
	EXPECT(cmp(0, max, max, max) == -1);
	EXPECT(cmp(0, max, max, max - 1U) == -1);

	EXPECT(cmp(max, 0, max, 0) == 0);
	EXPECT(cmp(max, 0, max, max) == -1);
	EXPECT(cmp(max, 0, max, max - 1U) == -1);

	EXPECT(cmp(max, max, max, max) == 0);
	EXPECT(cmp(max, max, max, max - 1U) == +1);

	EXPECT(cmp(max, max - 1U, max, max - 1U) == 0);

	return 0;
}

#endif
