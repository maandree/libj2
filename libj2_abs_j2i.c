/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_abs_j2i(struct libj2_j2i *a);
/* TODO Add man page */


#else


static void
check(uintmax_t high, uintmax_t low)
{
	struct libj2_j2i a, r;
	struct libj2_j2u u;

	a.high = high;
	a.low = low;
	libj2_abs_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	libj2_minus_j2i(&a);
	libj2_abs_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2i){111, 222};
	a.high = high;
	a.low = low;
	libj2_abs_j2i_to_j2i((const struct libj2_j2i *)&a, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2i(&a, &r));
	libj2_minus_j2i(&a);
	libj2_abs_j2i_to_j2i((const struct libj2_j2i *)&a, &r);
	libj2_minus_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2i(&a, &r));

	u = (struct libj2_j2u){111, 222};
	a.high = high;
	a.low = low;
	libj2_abs_j2i_to_j2u((const struct libj2_j2i *)&a, &u);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2u(&a, &u));
	libj2_minus_j2i(&a);
	libj2_abs_j2i_to_j2u((const struct libj2_j2i *)&a, &u);
	libj2_minus_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2u(&a, &u));

	a.high = high;
	a.low = low;
	libj2_minus_abs_j2i(&a);
	libj2_minus_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	libj2_minus_j2i(&a);
	libj2_minus_abs_j2i(&a);
	libj2_minus_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2i){111, 222};
	a.high = high;
	a.low = low;
	libj2_minus_abs_j2i_to_j2i((const struct libj2_j2i *)&a, &r);
	libj2_minus_j2i(&r);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2i(&a, &r));
	libj2_minus_j2i(&a);
	libj2_minus_abs_j2i_to_j2i((const struct libj2_j2i *)&a, &r);
	libj2_minus_j2i(&a);
	libj2_minus_j2i(&r);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2i(&a, &r));
}


static void
check_min(void)
{
	const uintmax_t high = ~(UINTMAX_MAX >> 1);
	const uintmax_t low = 0;
	struct libj2_j2i a, r;
	struct libj2_j2u u;

	a.high = high;
	a.low = low;
	libj2_abs_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2i){111, 222};
	a.high = high;
	a.low = low;
	libj2_abs_j2i_to_j2i((const struct libj2_j2i *)&a, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2i(&a, &r));

	u = (struct libj2_j2u){111, 222};
	a.high = high;
	a.low = low;
	libj2_abs_j2i_to_j2u((const struct libj2_j2i *)&a, &u);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2u_eq_j2u((const void *)&a, &u));

	a.high = high;
	a.low = low;
	libj2_minus_abs_j2i(&a);
	libj2_minus_j2i(&a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2i){111, 222};
	a.high = high;
	a.low = low;
	libj2_minus_abs_j2i_to_j2i((const struct libj2_j2i *)&a, &r);
	libj2_minus_j2i(&r);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
	EXPECT(libj2_j2i_eq_j2i(&a, &r));
}


int
main(void)
{
	check(0, 0);
	check(0, 1);
	check(1, 0);
	check(1, 1);
	check(1, 2);
	check(0, UINTMAX_MAX - 0U);
	check(0, UINTMAX_MAX - 1U);
	check(1, UINTMAX_MAX - 0U);
	check(1, UINTMAX_MAX - 1U);
	check((UINTMAX_MAX >> 1) - 0U, 0);
	check((UINTMAX_MAX >> 1) - 0U, 1);
	check((UINTMAX_MAX >> 1) - 0U, UINTMAX_MAX - 0U);
	check((UINTMAX_MAX >> 1) - 0U, UINTMAX_MAX - 1U);
	check((UINTMAX_MAX >> 1) - 1U, 0);
	check((UINTMAX_MAX >> 1) - 1U, 01);
	check((UINTMAX_MAX >> 1) - 1U, UINTMAX_MAX - 0U);
	check((UINTMAX_MAX >> 1) - 1U, UINTMAX_MAX - 1U);

	check_min();

	return 0;
}

#endif
