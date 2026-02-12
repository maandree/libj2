/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_abs_diff_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res);


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


static void
check_(const struct libj2_j2u *a, const struct libj2_j2u *b, const struct libj2_j2u *expected)
{
	struct libj2_j2u r, a_saved = *a, b_saved = *b;

	r = (struct libj2_j2u){111, 222};
	libj2_j2u_abs_diff_j2u_to_j2u(a, b, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = *a;
	libj2_j2u_abs_diff_j2u_to_j2u(&r, b, &r);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = *b;
	libj2_j2u_abs_diff_j2u_to_j2u(a, &r, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = *a;
	libj2_j2u_abs_diff_j2u(&r, b);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = (struct libj2_j2u){111, 222};
	libj2_j2u_abs_diff_j2u_to_j2u(a, a, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_is_zero(&r));

	r = *a;
	libj2_j2u_abs_diff_j2u_to_j2u(&r, &r, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	r = *a;
	libj2_j2u_abs_diff_j2u(&r, &r);
	EXPECT(libj2_j2u_is_zero(&r));
}


static void
check(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u expected;

	if (libj2_j2u_ge_j2u(a, b))
		libj2_j2u_sub_j2u_to_j2u(a, b, &expected);
	else
		libj2_j2u_sub_j2u_to_j2u(b, a, &expected);

	check_(a, b, &expected);
	check_(b, a, &expected);
}


int
main(void)
{
	struct libj2_j2u a, b;
	uintmax_t u, v;
	unsigned i;

	srand((unsigned)time(NULL));

	for (i = 0; i < 256U; i++) {
		a.high = random_ju();
		a.low = u = random_ju();
		b.high = random_ju();
		b.low = v = random_ju();
		check(&a, &b);
		b.low = 0;
		check(&a, &b);
		a.low = 0;
		check(&a, &b);

		b.high = 0;
		a.low = u;
		b.low = v;
		check(&a, &b);
		b.low = 0;
		check(&a, &b);
		a.low = 0;
		check(&a, &b);

		a.high = 0;
		a.low = u;
		b.low = v;
		check(&a, &b);
		b.low = 0;
		check(&a, &b);
	}

	return 0;
}

#endif
