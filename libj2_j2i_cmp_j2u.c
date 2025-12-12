/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2i_cmp_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b);
/* TODO Add man page */


#else

static int
cmp_(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2i a;
	struct libj2_j2u b;
	int ret;

	a.high = a_high;
	a.low = a_low;
	b.high = b_high;
	b.low = b_low;

	ret = libj2_j2i_cmp_j2u(&a, &b);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_lt_j2u(&a, &b) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_le_j2u(&a, &b) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_gt_j2u(&a, &b) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_ge_j2u(&a, &b) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_eq_j2u(&a, &b) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2i_ne_j2u(&a, &b) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_cmp_j2i(&b, &a) == (ret ? -ret : 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_lt_j2i(&b, &a) == (ret > 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_le_j2i(&b, &a) == (ret >= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_gt_j2i(&b, &a) == (ret < 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_ge_j2i(&b, &a) == (ret <= 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_eq_j2i(&b, &a) == (ret == 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	EXPECT(libj2_j2u_ne_j2i(&b, &a) == (ret != 0));
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(b.high == b_high);
	EXPECT(b.low == b_low);

	return ret;
}


static int
cmp(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	struct libj2_j2i a;
	int ret;

	a.high = a_high;
	a.low = a_low;

	ret = cmp_(a.high, a.low, b_high, b_low);

	if (a.high || a.low) {
		libj2_minus_j2i(&a);
		EXPECT(cmp_(a.high, a.low, b_high, b_low) == -1);
	}

	return ret;
}


int
main(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;

	EXPECT(cmp(0, 0, 0, 0) == 0);
	EXPECT(cmp(0, 0, 0, 1) == -1);
	EXPECT(cmp(0, 0, 1, 0) == -1);
	EXPECT(cmp(0, 0, 1, 1) == -1);
	EXPECT(cmp(0, 0, 0, umax) == -1);
	EXPECT(cmp(0, 0, max, 0) == -1);
	EXPECT(cmp(0, 0, max, umax) == -1);
	EXPECT(cmp(0, 0, max, umax - 1U) == -1);
	EXPECT(cmp(0, 0, umax, 0) == -1);
	EXPECT(cmp(0, 0, umax, umax) == -1);
	EXPECT(cmp(0, 0, umax, umax - 1U) == -1);

	EXPECT(cmp(0, 1, 0, 0) == +1);
	EXPECT(cmp(0, 1, 0, 1) == 0);
	EXPECT(cmp(0, 1, 1, 0) == -1);
	EXPECT(cmp(0, 1, 1, 1) == -1);
	EXPECT(cmp(0, 1, 0, umax) == -1);
	EXPECT(cmp(0, 1, max, 0) == -1);
	EXPECT(cmp(0, 1, max, umax) == -1);
	EXPECT(cmp(0, 1, max, umax - 1U) == -1);
	EXPECT(cmp(0, 1, umax, 0) == -1);
	EXPECT(cmp(0, 1, umax, umax) == -1);
	EXPECT(cmp(0, 1, umax, umax - 1U) == -1);

	EXPECT(cmp(1, 0, 0, 0) == +1);
	EXPECT(cmp(1, 0, 0, 1) == +1);
	EXPECT(cmp(1, 0, 1, 0) == 0);
	EXPECT(cmp(1, 0, 1, 1) == -1);
	EXPECT(cmp(1, 0, 0, umax) == +1);
	EXPECT(cmp(1, 0, max, 0) == -1);
	EXPECT(cmp(1, 0, max, umax) == -1);
	EXPECT(cmp(1, 0, max, umax - 1U) == -1);
	EXPECT(cmp(1, 0, umax, 0) == -1);
	EXPECT(cmp(1, 0, umax, umax) == -1);
	EXPECT(cmp(1, 0, umax, umax - 1U) == -1);

	EXPECT(cmp(1, 1, 0, 0) == +1);
	EXPECT(cmp(1, 1, 0, 1) == +1);
	EXPECT(cmp(1, 1, 1, 0) == +1);
	EXPECT(cmp(1, 1, 1, 1) == 0);
	EXPECT(cmp(1, 1, 0, umax) == +1);
	EXPECT(cmp(1, 1, max, 0) == -1);
	EXPECT(cmp(1, 1, max, umax) == -1);
	EXPECT(cmp(1, 1, max, umax - 1U) == -1);
	EXPECT(cmp(1, 1, umax, 0) == -1);
	EXPECT(cmp(1, 1, umax, umax) == -1);
	EXPECT(cmp(1, 1, umax, umax - 1U) == -1);

	EXPECT(cmp(0, umax, 0, 0) == +1);
	EXPECT(cmp(0, umax, 0, 1) == +1);
	EXPECT(cmp(0, umax, 1, 0) == -1);
	EXPECT(cmp(0, umax, 1, 1) == -1);
	EXPECT(cmp(0, umax, 0, umax) == 0);
	EXPECT(cmp(0, umax, max, 0) == -1);
	EXPECT(cmp(0, umax, max, umax) == -1);
	EXPECT(cmp(0, umax, max, umax - 1U) == -1);
	EXPECT(cmp(0, umax, umax, 0) == -1);
	EXPECT(cmp(0, umax, umax, umax) == -1);
	EXPECT(cmp(0, umax, umax, umax - 1U) == -1);

	EXPECT(cmp(max, 0, 0, 0) == +1);
	EXPECT(cmp(max, 0, 0, 1) == +1);
	EXPECT(cmp(max, 0, 1, 0) == +1);
	EXPECT(cmp(max, 0, 1, 1) == +1);
	EXPECT(cmp(max, 0, 0, umax) == +1);
	EXPECT(cmp(max, 0, max, 0) == 0);
	EXPECT(cmp(max, 0, max, umax) == -1);
	EXPECT(cmp(max, 0, max, umax - 1U) == -1);
	EXPECT(cmp(max, 0, umax, 0) == -1);
	EXPECT(cmp(max, 0, umax, umax) == -1);
	EXPECT(cmp(max, 0, umax, umax - 1U) == -1);

	EXPECT(cmp(max, umax, 0, 0) == +1);
	EXPECT(cmp(max, umax, 0, 1) == +1);
	EXPECT(cmp(max, umax, 1, 0) == +1);
	EXPECT(cmp(max, umax, 1, 1) == +1);
	EXPECT(cmp(max, umax, 0, umax) == +1);
	EXPECT(cmp(max, umax, max, 0) == +1);
	EXPECT(cmp(max, umax, max, umax) == 0);
	EXPECT(cmp(max, umax, max, umax - 1U) == +1);
	EXPECT(cmp(max, umax, umax, 0) == -1);
	EXPECT(cmp(max, umax, umax, umax) == -1);
	EXPECT(cmp(max, umax, umax, umax - 1U) == -1);

	EXPECT(cmp(max, umax - 1U, 0, 0) == +1);
	EXPECT(cmp(max, umax - 1U, 0, 1) == +1);
	EXPECT(cmp(max, umax - 1U, 1, 0) == +1);
	EXPECT(cmp(max, umax - 1U, 1, 1) == +1);
	EXPECT(cmp(max, umax - 1U, 0, umax) == +1);
	EXPECT(cmp(max, umax - 1U, max, 0) == +1);
	EXPECT(cmp(max, umax - 1U, max, umax) == -1);
	EXPECT(cmp(max, umax - 1U, max, umax - 1U) == 0);
	EXPECT(cmp(max, umax - 1U, umax, 0) == -1);
	EXPECT(cmp(max, umax - 1U, umax, umax) == -1);
	EXPECT(cmp(max, umax - 1U, umax, umax - 1U) == -1);

	EXPECT(cmp_(~max, 0, 0, 0) == -1);
	EXPECT(cmp_(~max, 0, 0, 1) == -1);
	EXPECT(cmp_(~max, 0, 1, 0) == -1);
	EXPECT(cmp_(~max, 0, 1, 1) == -1);
	EXPECT(cmp_(~max, 0, 0, umax) == -1);
	EXPECT(cmp_(~max, 0, max, 0) == -1);
	EXPECT(cmp_(~max, 0, max, umax) == -1);
	EXPECT(cmp_(~max, 0, max, umax - 1U) == -1);
	EXPECT(cmp_(~max, 0, umax, 0) == -1);
	EXPECT(cmp_(~max, 0, umax, umax) == -1);
	EXPECT(cmp_(~max, 0, umax, umax - 1U) == -1);
	EXPECT(cmp_(~max, 0, ~max, 0) == -1);

	return 0;
}

#endif
