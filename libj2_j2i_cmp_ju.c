/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_cmp_ju(const struct libj2_j2i *a, uintmax_t b);
/* TODO Add man page */


#else

static int
cmp_(uintmax_t a_high, uintmax_t a_low, uintmax_t b)
{
	struct libj2_j2i a;
	int ret;

	a.high = a_high;
	a.low = a_low;

	ret = libj2_j2i_cmp_ju(&a, b);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_lt_ju(&a, b) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_le_ju(&a, b) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_gt_ju(&a, b) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_ge_ju(&a, b) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_eq_ju(&a, b) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_j2i_ne_ju(&a, b) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_cmp_j2i(b, &a) == (ret ? -ret : 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_lt_j2i(b, &a) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_le_j2i(b, &a) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_gt_j2i(b, &a) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_ge_j2i(b, &a) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_eq_j2i(b, &a) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	EXPECT(libj2_ju_ne_j2i(b, &a) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);

	return ret;
}


static int
cmp(uintmax_t a_high, uintmax_t a_low, uintmax_t b)
{
	struct libj2_j2i a;
	int ret;

	a.high = a_high;
	a.low = a_low;

	ret = cmp_(a.high, a.low, b);

	if (a.high || a.low) {
		libj2_minus_j2i(&a);
		EXPECT(cmp_(a.high, a.low, b) == -1);
	}

	return ret;
}


int
main(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;

	EXPECT(cmp(0, 0, 0) == 0);
	EXPECT(cmp(0, 0, 1) == -1);
	EXPECT(cmp(0, 0, umax) == -1);

	EXPECT(cmp(0, 1, 0) == +1);
	EXPECT(cmp(0, 1, 1) == 0);
	EXPECT(cmp(0, 1, umax) == -1);

	EXPECT(cmp(1, 0, 0) == +1);
	EXPECT(cmp(1, 0, 1) == +1);
	EXPECT(cmp(1, 0, umax) == +1);

	EXPECT(cmp(1, 1, 0) == +1);
	EXPECT(cmp(1, 1, 1) == +1);
	EXPECT(cmp(1, 1, umax) == +1);

	EXPECT(cmp(0, umax, 0) == +1);
	EXPECT(cmp(0, umax, 1) == +1);
	EXPECT(cmp(0, umax, umax) == 0);

	EXPECT(cmp(max, 0, 0) == +1);
	EXPECT(cmp(max, 0, 1) == +1);
	EXPECT(cmp(max, 0, umax) == +1);

	EXPECT(cmp(max, umax, 0) == +1);
	EXPECT(cmp(max, umax, 1) == +1);
	EXPECT(cmp(max, umax, umax) == +1);

	EXPECT(cmp(max, umax - 1U, 0) == +1);
	EXPECT(cmp(max, umax - 1U, 1) == +1);
	EXPECT(cmp(max, umax - 1U, umax) == +1);

	EXPECT(cmp_(~max, 0, 0) == -1);
	EXPECT(cmp_(~max, 0, 1) == -1);
	EXPECT(cmp_(~max, 0, umax) == -1);

	return 0;
}

#endif
