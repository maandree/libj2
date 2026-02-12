/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ji_abs_diff_ju_to_j2u(intmax_t a, uintmax_t b, struct libj2_j2u *res);


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


int
main(void)
{
	struct libj2_j2u r, expected;
	uintmax_t a;
	intmax_t b;
	unsigned i;

	srand((unsigned)time(NULL));

	r = (struct libj2_j2u){111, 222};
	libj2_ji_abs_diff_ju_to_j2u(0, 0, &r);
	EXPECT(libj2_j2u_eq_ju(&r, 0));

	r = (struct libj2_j2u){111, 222};
	libj2_ji_abs_diff_ju_to_j2u(0, UINTMAX_MAX, &r);
	EXPECT(libj2_j2u_eq_ju(&r, UINTMAX_MAX));

	r = (struct libj2_j2u){111, 222};
	libj2_ji_abs_diff_ju_to_j2u(INTMAX_MAX, 0, &r);
	EXPECT(libj2_j2u_eq_ji(&r, INTMAX_MAX));

	r = (struct libj2_j2u){111, 222};
	libj2_ji_abs_diff_ju_to_j2u(-INTMAX_MAX, 0, &r);
	EXPECT(libj2_j2u_eq_ju(&r, INTMAX_MAX));

	r = (struct libj2_j2u){111, 222};
	libj2_ji_abs_diff_ju_to_j2u(INTMAX_MAX, UINTMAX_MAX, &r);
	EXPECT(libj2_j2u_eq_ju(&r, (uintmax_t)INTMAX_MAX + 1U));

	r = (struct libj2_j2u){111, 222};
	libj2_ji_abs_diff_ju_to_j2u(-INTMAX_MAX, UINTMAX_MAX, &r);
	libj2_ju_to_j2u(UINTMAX_MAX, &expected);
	libj2_j2u_add_ju(&expected, (uintmax_t)INTMAX_MAX);
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	for (i = 0; i < 256U; i++) {
		a = random_ju();
		b = (intmax_t)(random_ju() >> 1);

		r = (struct libj2_j2u){111, 222};
		libj2_ji_abs_diff_ju_to_j2u(-b, a, &r);
		libj2_ju_to_j2u(a, &expected);
		libj2_j2u_add_ju(&expected, (uintmax_t)b);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = (struct libj2_j2u){111, 222};
		libj2_ji_abs_diff_ju_to_j2u(b, a, &r);
		if ((uintmax_t)b < a) {
			libj2_ju_to_j2u(a, &expected);
			libj2_j2u_sub_ju(&expected, (uintmax_t)b);
		} else {
			libj2_ju_to_j2u((uintmax_t)b, &expected);
			libj2_j2u_sub_ju(&expected, a);
		}
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		if (a <= (uintmax_t)INTMAX_MAX) {
			r = (struct libj2_j2u){111, 222};
			libj2_ji_abs_diff_ju_to_j2u((intmax_t)a, (uintmax_t)b, &r);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));
		}
	}

	return 0;
}

#endif
