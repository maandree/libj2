/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_lsh(struct libj2_j2i *a, unsigned b);


#else

static void
check(const struct libj2_j2i *a, unsigned shift, const struct libj2_j2i *expected, int overflow)
{
	struct libj2_j2i a_saved = *a, r;
	intmax_t v;

	r = *a;
	libj2_j2i_lsh(&r, shift);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = *a;
	EXPECT(libj2_j2i_lsh_overflow_p((const struct libj2_j2i *)&r, shift) == overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, a));

	r = *a;
	EXPECT(libj2_j2i_lsh_overflow(&r, shift) == overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = *a;
	libj2_j2i_sat_lsh(&r, shift);
	EXPECT(overflow > 0 ? libj2_j2i_is_max(&r) :
	       overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, expected));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_lsh_to_j2i((const struct libj2_j2i *)a, shift, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = *a;
	libj2_j2i_lsh_to_j2i(&r, shift, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2i_lsh_to_j2i_overflow((const struct libj2_j2i *)a, shift, &r) == overflow);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = *a;
	EXPECT(libj2_j2i_lsh_to_j2i_overflow(&r, shift, &r) == overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = (struct libj2_j2i){111, 222};
	libj2_j2i_sat_lsh_to_j2i((const struct libj2_j2i *)a, shift, &r);
	EXPECT(libj2_j2i_eq_j2i(a, &a_saved));
	EXPECT(overflow > 0 ? libj2_j2i_is_max(&r) :
	       overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, expected));

	r = *a;
	libj2_j2i_sat_lsh_to_j2i(&r, shift, &r);
	EXPECT(overflow > 0 ? libj2_j2i_is_max(&r) :
	       overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, expected));

	if (libj2_j2i_is_negative(a)) {
		if (a->high != UINTMAX_MAX || ~a->low > UINTMAX_MAX >> 1)
			return;
		v = -(intmax_t)~a->low - 1;
	} else {
		if (a->high || a->low > UINTMAX_MAX >> 1)
			return;
		v = (intmax_t)a->low;
	}

	EXPECT(libj2_ji_lsh_overflow_p(v, shift) == overflow);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_lsh_to_j2i(v, shift, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = (struct libj2_j2i){111, 222};
	EXPECT(libj2_ji_lsh_to_j2i_overflow(v, shift, &r) == overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, expected));

	r = (struct libj2_j2i){111, 222};
	libj2_ji_sat_lsh_to_j2i(v, shift, &r);
	EXPECT(overflow > 0 ? libj2_j2i_is_max(&r) :
	       overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, expected));
}


int
main(void)
{
	struct libj2_j2i a, b;
	struct libj2_j2u t;
	unsigned i, j, k, s;
	int overflow;

	srand((unsigned)time(NULL));

	for (j = 0; j <= LIBJ2_J2I_BIT + 4U; j++) {
		libj2_j2i_zero(&a);
		libj2_j2i_zero(&b);
		check(&a, j, &b, 0);

		libj2_not_j2u((void *)&a);
		libj2_not_j2u((void *)&b);
		libj2_j2u_lsh((void *)&b, j);
		check(&a, j, &b, j >= LIBJ2_J2I_BIT ? -1 : 0);

		for (i = 0; i < LIBJ2_J2I_BIT; i++) {
			libj2_j2i_zero(&a);
			libj2_j2u_or_bit((void *)&a, i);
			libj2_j2i_zero(&b);
			if (i + j < LIBJ2_J2I_BIT)
				libj2_j2u_or_bit((void *)&b, i + j);
			overflow = i == LIBJ2_J2I_VBIT ? j ? -1 : 0 : i + j < LIBJ2_J2I_VBIT ? 0 : +1;
			check(&a, j, &b, overflow);

			libj2_j2i_zero(&a);
			libj2_j2u_or_bit((void *)&a, i);
			libj2_not_j2u((void *)&a);
			libj2_j2i_zero(&b);
			if (i + j < LIBJ2_J2I_BIT)
				libj2_j2u_or_bit((void *)&b, i + j);
			for (k = 0; k < j; k++)
				libj2_j2u_or_bit((void *)&b, k);
			libj2_not_j2u((void *)&b);
			overflow = i == LIBJ2_J2I_VBIT ? j ? +1 : 0 : i + j < LIBJ2_J2I_VBIT ? 0 : -1;
			check(&a, j, &b, overflow);
		}
	}

	for (i = 0; i < 32; i++) {
		for (j = 0; j < LIBJ2_J2I_BIT - 1U; j++) {
			for (k = 0; k <= LIBJ2_J2I_BIT + 1U; k++) {
				libj2_j2i_zero(&a);
				libj2_j2i_zero(&b);
				for (s = 0; s <= j; s++) {
					if (rand() < rand())
						continue;
					libj2_j2u_or_bit((void *)&a, s);
					libj2_j2u_or_bit((void *)&b, s + k);
				}
				overflow = libj2_co_j2u((const void *)&a) > libj2_co_j2u((const void *)&b);
				overflow |= libj2_j2i_is_negative(&b);
				check(&a, k, &b, overflow);

				libj2_not_j2u((void *)&a);
				libj2_not_j2u((void *)&b);
				libj2_ju_lsh_to_j2u(1, k, &t);
				libj2_j2u_sub_ju(&t, 1);
				libj2_not_j2u(&t);
				libj2_j2u_and_j2u((void *)&b, &t);
				overflow = -overflow;
				if (a.high == UINTMAX_MAX && a.low == UINTMAX_MAX && k >= LIBJ2_J2I_BIT)
					overflow = -1;
				check(&a, k, &b, overflow);
			}
		}
	}

	return 0;
}

#endif
