/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline unsigned libj2_ffs_j2u(const struct libj2_j2u *a);


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
	struct libj2_j2u a, b, a_saved, b_saved;
	unsigned i, j;

	srand((unsigned)time(NULL));

	libj2_ju_to_j2u(0, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 0);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_ju_to_j2u(1, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 1);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_ju_to_j2u(2, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 2);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_ju_to_j2u(3, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 1);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_ju_to_j2u(4, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 3);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_ju_to_j2u(5, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 1);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_ju_to_j2u(6, &a);
	a_saved = a;
	EXPECT(libj2_ffs_j2u(&a) == 2);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	libj2_j2u_max(&a);
	EXPECT(libj2_ffs_j2u(&a) == 1);
	EXPECT(libj2_j2u_is_max(&a));

	for (i = 0; i < LIBJ2_J2U_BIT; i++) {
		libj2_j2u_zero(&a);
		libj2_j2u_or_bit(&a, i);
		a_saved = a;
		EXPECT(libj2_ffs_j2u(&a) == i + 1U);
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	}

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		libj2_j2u_zero(&a);
		libj2_j2u_or_bit(&a, i);
		a.high = UINTMAX_MAX;
		a_saved = a;
		EXPECT(libj2_ffs_j2u(&a) == i + 1U);
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
	}

	for (i = 0; i < LIBJ2_J2U_BIT; i++) {
		libj2_j2u_max(&a);
		libj2_j2u_lsh(&a, i);
		a_saved = a;
		EXPECT(libj2_ffs_j2u(&a) == i + 1U);
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

		for (j = 0; j < 32; j++) {
			EXPECT(libj2_j2u_test_bit(&a, i));
			b.high = random_ju();
			b.low = random_ju();
			libj2_j2u_and_j2u(&b, &a);
			libj2_j2u_or_bit(&b, i);
			EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
			b_saved = b;
			EXPECT(libj2_ffs_j2u(&b) == i + 1U);
			EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));
		}
	}

	return 0;
}

#endif
