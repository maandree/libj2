/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_abs_diff_j2i_to_j2u(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2u *res);


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
calc_expected(const struct libj2_j2i *large, const struct libj2_j2i *small, struct libj2_j2u *expected)
{
	struct libj2_j2u l, s;
	struct libj2_j2i e;

	if (!libj2_j2i_is_negative(small)) {
		libj2_j2i_sub_j2i_to_j2i(large, small, &e);
		libj2_j2i_to_j2u(&e, expected);
	} else if (!libj2_j2i_is_positive(large)) {
		libj2_abs_j2i_to_j2u(large, &s);
		libj2_abs_j2i_to_j2u(small, &l);
		libj2_j2u_sub_j2u_to_j2u(&l, &s, expected);
	} else {
		libj2_j2i_to_j2u(large, expected);
		libj2_abs_j2i_to_j2u(small, &s);
		libj2_j2u_add_j2u(expected, &s);
	}
}


static void
check(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2u r, expected;
	struct libj2_j2i a_saved = *a, b_saved = *b;

	if (libj2_j2i_ge_j2i(a, b))
		calc_expected(a, b, &expected);
	else
		calc_expected(b, a, &expected);

	r = (struct libj2_j2u){111, 222};
	libj2_j2i_abs_diff_j2i_to_j2u(a, b, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	r = (struct libj2_j2u){111, 222};
	libj2_j2i_abs_diff_j2i_to_j2u(b, a, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, &expected));

	r = (struct libj2_j2u){111, 222};
	libj2_j2i_abs_diff_j2i_to_j2u(a, a, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2u_is_zero(&r));
}


int
main(void)
{
	struct libj2_j2i a, b;
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
