/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_imply_j2u(struct libj2_j2u *a, const struct libj2_j2u *b);


#else

static void
check(struct libj2_j2u *a, struct libj2_j2u *b, const struct libj2_j2u *expected)
{
	struct libj2_j2u a_saved = *a, b_saved = *b, r;

	r = *a;
	libj2_j2u_imply_j2u(&r, b);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = *a;
	libj2_j2u_imply_j2u(&r, &r);
	EXPECT(libj2_j2u_is_max(&r));

	r = (struct libj2_j2u){111, 222};
	libj2_j2u_imply_j2u_to_j2u(a, b, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = *a;
	libj2_j2u_imply_j2u_to_j2u(&r, b, &r);
	EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = *b;
	libj2_j2u_imply_j2u_to_j2u(a, &r, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, expected));

	r = (struct libj2_j2u){111, 222};
	libj2_j2u_imply_j2u_to_j2u(a, a, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_is_max(&r));

	r = *a;
	libj2_j2u_imply_j2u_to_j2u(&r, &r, &r);
	EXPECT(libj2_j2u_is_max(&r));

	if (a->high == 0U) {
		r = (struct libj2_j2u){111, 222};
		libj2_ju_imply_j2u_to_j2u(a->low, b, &r);
		EXPECT(libj2_j2u_eq_j2u(b, &b_saved));
		EXPECT(libj2_j2u_eq_j2u(&r, expected));

		r = *b;
		libj2_ju_imply_j2u_to_j2u(a->low, &r, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, expected));
	}

	if (b->high == 0U) {
		r = *a;
		libj2_j2u_imply_ju(&r, b->low);
		EXPECT(libj2_j2u_eq_j2u(&r, expected));

		r = (struct libj2_j2u){111, 222};
		libj2_j2u_imply_ju_to_j2u(a, b->low, &r);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&r, expected));

		r = *a;
		libj2_j2u_imply_ju_to_j2u(&r, b->low, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, expected));
	}
}

int
main(void)
{
	unsigned truthtable[] = {1, 1, 0, 1};
	unsigned i, j;
	uintmax_t a_bit, b_bit, r_bit;
	struct libj2_j2u a, b, r, a_saved;

	srand((unsigned)time(NULL));

	for (j = 0; j < 128; j++) {
		a.high = a.low = 0;
		b.high = b.low = 0;
		r.high = r.low = 0;
		for (i = 0; i < LIBJ2_J2U_BIT; i++) {
			a_bit = (uintmax_t)(rand() < rand());
			b_bit = (uintmax_t)(rand() < rand());
			r_bit = truthtable[a_bit * 2U + b_bit];
			if (i < LIBJ2_JU_BIT) {
				a.low |= a_bit << i;
				b.low |= b_bit << i;
				r.low |= r_bit << i;
			} else {
				a.high |= a_bit << (i - LIBJ2_JU_BIT);
				b.high |= b_bit << (i - LIBJ2_JU_BIT);
				r.high |= r_bit << (i - LIBJ2_JU_BIT);
			}
		}

		check(&a, &b, &r);

		a_saved = a;
		a.high = 0U;
		r.high = 0U;
		for (i = 0; i < LIBJ2_JU_BIT; i++) {
			r_bit = truthtable[(b.high >> i) & 1U];
			r.high |= r_bit << i;
		}
		check(&a, &b, &r);
		a = a_saved;

		b.high = 0U;
		r.high = 0U;
		for (i = 0; i < LIBJ2_JU_BIT; i++) {
			r_bit = truthtable[((a.high >> i) & 1U) * 2U];
			r.high |= r_bit << i;
		}
		check(&a, &b, &r);

		r.high = 0U;
		r.low = 0U;
		for (i = 0; i < LIBJ2_JU_BIT; i++) {
			r_bit = truthtable[((a.high >> i) & 1U) * 3U];
			r.high |= r_bit << i;
			r_bit = truthtable[((a.low >> i) & 1U) * 3U];
			r.low |= r_bit << i;
		}
		check(&a, &a, &r);
	}

	return 0;
}

#endif
