/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_cmp_ju(const struct libj2_j2u *a, uintmax_t b);
/* TODO Add man page */


#else

static int
cmp(uintmax_t a_high, uintmax_t a_low, uintmax_t b)
{
	struct libj2_j2u a, c;
	int ret;

	a.high = a_high;
	a.low = a_low;

	ret = libj2_j2u_cmp_ju(&a, b);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_cmp_j2u(b, &a) == (ret ? -ret : 0));

	EXPECT(libj2_j2u_lt_ju(&a, b) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2u_le_ju(&a, b) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2u_gt_ju(&a, b) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2u_ge_ju(&a, b) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2u_eq_ju(&a, b) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2u_ne_ju(&a, b) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_lt_j2u(b, &a) == (ret > 0));
	EXPECT(libj2_ju_le_j2u(b, &a) == (ret >= 0));
	EXPECT(libj2_ju_gt_j2u(b, &a) == (ret < 0));
	EXPECT(libj2_ju_ge_j2u(b, &a) == (ret <= 0));
	EXPECT(libj2_ju_eq_j2u(b, &a) == (ret == 0));
	EXPECT(libj2_ju_ne_j2u(b, &a) == (ret != 0));

	c = (struct libj2_j2u){111, 222};
	libj2_j2u_max_ju_to_j2u(&a, b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_ju(&c, b) == 1);

	c = a;
	libj2_j2u_max_ju(&c, b);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_ju(&c, b) == 1);

	c = (struct libj2_j2u){111, 222};
	libj2_j2u_min_ju_to_j2u(&a, b, &c);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_ju(&c, b) == 1);

	c = a;
	libj2_j2u_min_ju(&c, b);
	if (ret <= 0)
		EXPECT(libj2_j2u_eq_j2u(&c, &a) == 1);
	if (ret >= 0)
		EXPECT(libj2_j2u_eq_ju(&c, b) == 1);

	return ret;
}


int
main(void)
{
	const uintmax_t max = UINTMAX_MAX;

	EXPECT(cmp(0, 0, 0) == 0);
	EXPECT(cmp(0, 1, 0) == +1);
	EXPECT(cmp(1, 0, 0) == +1);
	EXPECT(cmp(1, 1, 0) == +1);
	EXPECT(cmp(0, max, 0) == +1);
	EXPECT(cmp(max, 0, 0) == +1);
	EXPECT(cmp(max, max, 0) == +1);
	EXPECT(cmp(max, max - 1U, 0) == +1);

	EXPECT(cmp(0, 0, 1) == -1);
	EXPECT(cmp(0, 1, 1) == 0);
	EXPECT(cmp(1, 0, 1) == +1);
	EXPECT(cmp(1, 1, 1) == +1);
	EXPECT(cmp(0, max, 1) == +1);
	EXPECT(cmp(max, 0, 1) == +1);
	EXPECT(cmp(max, max, 1) == +1);
	EXPECT(cmp(max, max - 1U, 1) == +1);

	EXPECT(cmp(0, 0, 2) == -1);
	EXPECT(cmp(0, 1, 2) == -1);
	EXPECT(cmp(1, 0, 2) == +1);
	EXPECT(cmp(1, 1, 2) == +1);
	EXPECT(cmp(0, max, 2) == +1);
	EXPECT(cmp(max, 0, 2) == +1);
	EXPECT(cmp(max, max, 2) == +1);
	EXPECT(cmp(max, max - 1U, 2) == +1);

	EXPECT(cmp(0, 0, max) == -1);
	EXPECT(cmp(0, 1, max) == -1);
	EXPECT(cmp(1, 0, max) == +1);
	EXPECT(cmp(1, 1, max) == +1);
	EXPECT(cmp(0, max, max) == 0);
	EXPECT(cmp(max, 0, max) == +1);
	EXPECT(cmp(max, max, max) == +1);
	EXPECT(cmp(max, max - 1U, max) == +1);

	EXPECT(cmp(0, 0, max - 1U) == -1);
	EXPECT(cmp(0, 1, max - 1U) == -1);
	EXPECT(cmp(1, 0, max - 1U) == +1);
	EXPECT(cmp(1, 1, max - 1U) == +1);
	EXPECT(cmp(0, max, max - 1U) == +1);
	EXPECT(cmp(max, 0, max - 1U) == +1);
	EXPECT(cmp(max, max, max - 1U) == +1);
	EXPECT(cmp(max, max - 1U, max - 1U) == +1);

	return 0;
}

#endif
