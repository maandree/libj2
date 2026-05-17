/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_xor_sign(struct libj2_j2i *a);


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
check(struct libj2_j2i *a)
{
	struct libj2_j2i r, saved, x;
	struct libj2_j2u u;

	saved = *a;

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_xor_sign_to_j2i((const struct libj2_j2i *)a, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &saved));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_xor_sign_to_j2u((const struct libj2_j2i *)a, &u);
	libj2_j2u_to_j2i(&u, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &saved));
	EXPECT(libj2_j2i_eq_j2i(&r, &saved));

	r = *a;
	libj2_j2i_xor_sign(&r);
	EXPECT(libj2_j2i_eq_j2i(&r, &saved));

	libj2_j2i_to_j2u(a, &u);
	libj2_not_j2u(&u);
	libj2_j2u_to_j2i(&u, a);
	x = *a;

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_xor_sign_to_j2i((const struct libj2_j2i *)a, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &x));
	EXPECT(libj2_j2i_eq_j2i(&r, &saved));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_xor_sign_to_j2u((const struct libj2_j2i *)a, &u);
	libj2_j2u_to_j2i(&u, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &x));
	EXPECT(libj2_j2i_eq_j2i(&r, &saved));

	r = x;
	libj2_j2i_xor_sign(&r);
	EXPECT(libj2_j2i_eq_j2i(&r, &saved));
}


int
main(void)
{
	struct libj2_j2i a;
	unsigned i;

	srand((unsigned)time(NULL));

	for (i = 0; i < 256; i++) {
		a.high = random_ju() >> 1;
		a.low = random_ju();
		check(&a);

		a.high = random_ju() >> 1;
		a.low = 0;
		check(&a);

		a.high = 0;
		a.low = random_ju();
		check(&a);

		a.high = random_ju() >> 1;
		a.low = UINTMAX_MAX;
		check(&a);

		a.high = random_ju() >> 1;
		a.low = 1;
		check(&a);

		a.high = 1U;
		a.low = random_ju();
		check(&a);

		a.high = UINTMAX_MAX >> 1;
		a.low = random_ju();
		check(&a);
	}

	a.high = 0;
	a.low = 0;
	check(&a);

	a.high = UINTMAX_MAX >> 1;
	a.low = UINTMAX_MAX;
	check(&a);

	return 0;
}

#endif
