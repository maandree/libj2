/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_lrot(struct libj2_j2u *a, unsigned b);
/* TODO Add man pages
   libj2_j2u_lrot
   libj2_j2u_lrot_to_j2u
   libj2_ju_lrot_to_j2u
 */


#else

static void
set(struct libj2_j2u *a, const char *pattern, unsigned shift)
{
	unsigned i, j = (LIBJ2_J2U_BIT - (shift % LIBJ2_J2U_BIT)) % LIBJ2_J2U_BIT;

	a->high = 0;
	a->low = 0;

	for (i = 0; i < LIBJ2_JU_BIT; i++, j++)
		if (pattern[j % LIBJ2_J2U_BIT] == '1')
			a->low |= (uintmax_t)1 << i;

	for (i = 0; i < LIBJ2_JU_BIT; i++, j++)
		if (pattern[j % LIBJ2_J2U_BIT] == '1')
			a->high |= (uintmax_t)1 << i;

}


int
main(void)
{
	struct libj2_j2u a, r, a_saved, expected;
	char pattern[LIBJ2_J2U_BIT + 1U];
	unsigned i, j, k;

	srand((unsigned)time(NULL));

	for (i = 0; i < 128U; i++) {
		for (j = 0; j < LIBJ2_J2U_BIT; j++)
			pattern[j] = '0' + (rand() < rand());
		pattern[LIBJ2_J2U_BIT] = '\0';
		set(&a, pattern, 0);
		a_saved = a;
		for (j = 0; j <= 2U * LIBJ2_J2U_BIT; j++) {
			set(&expected, pattern, j);

			r = a;
			libj2_j2u_lrot(&r, j);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));

			r = (struct libj2_j2u){111, 222};
			libj2_j2u_lrot_to_j2u(&a, j, &r);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));
			EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

			r = a;
			libj2_j2u_lrot_to_j2u(&r, j, &r);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));

			k = 2U * LIBJ2_J2U_BIT - j;

			r = a;
			libj2_j2u_rrot(&r, k);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));

			r = (struct libj2_j2u){111, 222};
			libj2_j2u_rrot_to_j2u(&a, k, &r);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));
			EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

			r = a;
			libj2_j2u_rrot_to_j2u(&r, k, &r);
			EXPECT(libj2_j2u_eq_j2u(&r, &expected));
		}
	}

	return 0;
}

#endif
