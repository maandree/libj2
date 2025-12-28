/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_minus_j2u(struct libj2_j2u *a);


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
minus_j2u(struct libj2_j2u *a)
{
	struct libj2_j2u r, a_saved = *a;
	r = (struct libj2_j2u){111, 222};
	libj2_minus_j2u_to_j2u(a, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	libj2_minus_j2u(a);
	EXPECT(libj2_j2u_eq_j2u(a, &r));
}


int
main(void)
{
	unsigned i;
	struct libj2_j2u a, b;
	uintmax_t v;

	libj2_j2u_zero(&a);
	minus_j2u(&a);
	EXPECT(libj2_j2u_is_zero(&a));

	a = (struct libj2_j2u){.high = 0, .low = 1};
	minus_j2u(&a);
	EXPECT(libj2_j2u_eq_j2u(&a, &(struct libj2_j2u){.high = UINTMAX_MAX, .low = UINTMAX_MAX}));

	a = (struct libj2_j2u){.high = UINTMAX_MAX, .low = UINTMAX_MAX};
	minus_j2u(&a);
	EXPECT(libj2_j2u_eq_j2u(&a, &(struct libj2_j2u){.high = 0, .low = 1}));

	for (i = 0; i < 256; i++) {
		a.high = 0;
		a.low = v = random_ju();
		minus_j2u(&a);
		EXPECT(a.high == UINTMAX_MAX);
		EXPECT(a.low == 0U - v);

		a.high = UINTMAX_MAX;
		a.low = v = random_ju();
		minus_j2u(&a);
		EXPECT(a.high == 0);
		EXPECT(a.low == 0U - v);
	}

	for (i = 0; i < 256; i++) {
		a.high = b.high = random_ju() >> 1;
		a.low = b.low = random_ju();
		minus_j2u(&a);
		libj2_j2u_add_j2u(&a, &b);
		EXPECT(libj2_j2u_is_zero(&a));

		a.high = b.high ^= UINTMAX_MAX;
		a.low = b.low ^= UINTMAX_MAX;
		minus_j2u(&a);
		libj2_j2u_add_j2u(&a, &b);
		EXPECT(libj2_j2u_is_zero(&a));
	}

	return 0;
}

#endif
