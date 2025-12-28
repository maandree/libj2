/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_minus_j2i_to_j2u(const struct libj2_j2i *a, struct libj2_j2u *res);


#else

static void
check_ji_ju(intmax_t ji, uintmax_t ju)
{
	struct libj2_j2i a, a_saved, b;
	struct libj2_j2u r;

	r = (struct libj2_j2u){111, 222};
	libj2_ji_to_j2i(ji, &a);
	a_saved = a;
	libj2_minus_j2i_to_j2u((const struct libj2_j2i *)&a, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2u_eq_ju(&r, ju));

	b = (struct libj2_j2i){111, 222};
	libj2_minus_j2u_to_j2i((const struct libj2_j2u *)&r, &b);
	EXPECT(libj2_j2u_eq_ju(&r, ju));
	EXPECT(libj2_j2i_eq_j2i(&b, &a_saved));
}


static void
check_j2i_j2u(uintmax_t a_high, uintmax_t a_low, int a_minus, uintmax_t r_high, uintmax_t r_low)
{
	struct libj2_j2i a, a_saved, b;
	struct libj2_j2u r;

	r = (struct libj2_j2u){111, 222};
	a.high = a_high;
	a.low = a_low;
	if (a_minus)
		libj2_minus_j2i(&a);
	a_saved = a;
	libj2_minus_j2i_to_j2u((const struct libj2_j2i *)&a, &r);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(r.high == r_high);
	EXPECT(r.low == r_low);

	b = (struct libj2_j2i){111, 222};
	libj2_minus_j2u_to_j2i((const struct libj2_j2u *)&r, &b);
	EXPECT(r.high == r_high);
	EXPECT(r.low == r_low);
	EXPECT(libj2_j2i_eq_j2i(&b, &a_saved));
}


int
main(void)
{
	check_ji_ju(0, 0);
	check_ji_ju(-1, 1);
	check_ji_ju(-2, 2);

	check_j2i_j2u(UINTMAX_MAX >> 1, UINTMAX_MAX, 1, UINTMAX_MAX >> 1, UINTMAX_MAX);
	check_j2i_j2u(UINTMAX_MAX ^ (UINTMAX_MAX >> 1), 0, 0, UINTMAX_MAX ^ (UINTMAX_MAX >> 1), 0);
	check_j2i_j2u(0, 1, 0, UINTMAX_MAX, UINTMAX_MAX);
	check_j2i_j2u(0, 2, 0, UINTMAX_MAX, UINTMAX_MAX - 1U);
	check_j2i_j2u(UINTMAX_MAX >> 1, UINTMAX_MAX, 0, UINTMAX_MAX ^ (UINTMAX_MAX >> 1), 1);
	check_j2i_j2u(UINTMAX_MAX ^ (UINTMAX_MAX >> 1), 0, 0, UINTMAX_MAX ^ (UINTMAX_MAX >> 1), 0);

	return 0;
}

#endif
