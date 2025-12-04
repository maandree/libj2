/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_test_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b);
/* TODO Add man page */


#else

static void
set_pattern(struct libj2_j2u *a, unsigned off, unsigned mod)
{
	unsigned i;
	a->high = 0;
	a->low = 0;
	for (i = 0; i < LIBJ2_J2U_BIT; i++) {
		if (i % mod != off)
			continue;
		if (i < LIBJ2_JU_BIT)
			a->low |= (uintmax_t)1 << i;
		else
			a->high |= (uintmax_t)1 << (i - LIBJ2_JU_BIT);
	}
}

CONST static int
expected(unsigned a_off, unsigned a_mod, unsigned b_off, unsigned b_mod)
{
	unsigned a, b;
	if (a_off >= a_mod || b_off >= b_mod)
		return 0;
	if (a_mod == b_mod)
		return a_off == b_off;
	a = a_off;
	b = b_off;
	while (a < LIBJ2_J2U_BIT && b < LIBJ2_J2U_BIT) {
		if (a == b)
			return 1;
		if (a < b)
			a += a_mod;
		else
			b += b_mod;
	}
	return 0;
}

int
main(void)
{
	struct libj2_j2u a, b, a_saved, b_saved;
	unsigned i, j, u, v, ii, jj;
	unsigned mods[] = {1, 2, 3, 4, 5, 6, 7, 8, 16, 32, 33, 64, 12, LIBJ2_J2U_BIT,
	                   LIBJ2_J2U_BIT - 1U, LIBJ2_J2U_BIT - 2U, LIBJ2_J2U_BIT - 3U};

	EXPECT(expected(0, 4, 0, 5) == 1);
	EXPECT(expected(0, 4, 1, 4) == 0);
	EXPECT(expected(0, 4, 0, 4) == 1);
	EXPECT(expected(0, 2, 0, 3) == 1);

	for (ii = 0; ii < sizeof(mods) / sizeof(*mods); ii++) {
		i = mods[ii];
		for (u = 0; u <= i; u++) {
			set_pattern(&a, u, i);
			a_saved = a;
			EXPECT(libj2_j2u_test_j2u(&a, &a) == (u < i));
			EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
			b.high = ~a.high;
			b.low = ~a.low;
			b_saved = b;
			EXPECT(libj2_j2u_test_j2u(&a, &b) == 0);
			EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
			EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));
			for (jj = 0; jj < sizeof(mods) / sizeof(*mods); jj++) {
				j = mods[jj];
				for (v = 0; v <= j; v++) {
					set_pattern(&b, v, j);
					b_saved = b;
					EXPECT(libj2_j2u_test_j2u(&a, &b) == expected(u, i, v, j));
					EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
					EXPECT(libj2_j2u_eq_j2u(&b, &b_saved));
				}
			}
		}
	}

	return 0;
}

#endif
