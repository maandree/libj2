/* See LICENSE file for copyright and license details. */
#include "common.h"
#include <errno.h>
#ifndef TEST


int
libj2_str_to_j2i(const char *s, size_t slen, char **end, const char *digits1, const char *digits2, struct libj2_j2i *a)
{
	struct libj2_j2u u;
	int neg, r;

	r = libj2_str_to_j2u_sign(s, slen, end, digits1, digits2, &u, &neg);
	switch (r) {
	case 0:
		break;
	overflow:
		r = ERANGE;
		/* fall-through */
	case ERANGE:
		if (neg)
			libj2_j2i_min(a);
		else
			libj2_j2i_max(a);
		/* fall-through */
	default:
		return r;
	}

	if (neg) {
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
		if (libj2_co_j2u(&u) > 1U)
			goto may_overflow;
#else
		if (u.high) {
			if (u.low)
				goto may_overflow;
			if (u.high & (u.high - 1U))
				goto may_overflow;
		} else {
			if (u.low & (u.low - 1U))
				goto may_overflow;
		}
#endif
		if (0) {
		may_overflow:
			if (libj2_j2u_test_bit(&u, LIBJ2_J2U_BIT - 1U))
				goto overflow;
		}
		libj2_minus_j2u_to_j2i(&u, a);
	} else {
		if (libj2_j2u_test_bit(&u, LIBJ2_J2U_BIT - 1U))
			goto overflow;
		libj2_j2u_to_j2i(&u, a);
	}

	return r;

}


#else


int
main(void)
{
	/* Primarily tested via libj2_str_to_j2u(_sign) */

	char buf[128U + LIBJ2_J2U_BIT];
	struct libj2_j2i a, a_saved;
	struct libj2_j2u u;

	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_str_to_j2i("123", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_ji(&a, 123));

	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_str_to_j2i("+123", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_ji(&a, 123));

	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_str_to_j2i("-123", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_ji(&a, -123));

	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_str_to_j2i("--123", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_ji(&a, 123));

	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_str_to_j2i("-+-123", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_ji(&a, 123));

	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_str_to_j2i("---123", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_ji(&a, -123));

	libj2_j2i_max(&a);
	a_saved = a;
	libj2_j2i_to_j2u(&a, &u);
	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2u_to_str(&u, buf, sizeof(buf), NULL) < sizeof(buf));
	EXPECT(libj2_str_to_j2i(buf, SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	libj2_j2i_min(&a);
	a_saved = a;
	libj2_minus_j2i_to_j2u(&a, &u);
	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2u_to_str(&u, &buf[1], sizeof(buf) - 1U, NULL) < sizeof(buf) - 1U);
	buf[0] = '-';
	EXPECT(libj2_str_to_j2i(buf, SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	libj2_j2i_max(&a);
	a_saved = a;
	libj2_j2i_to_j2u(&a, &u);
	libj2_j2u_add_ju(&u, 1);
	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2u_to_str(&u, buf, sizeof(buf), NULL) < sizeof(buf));
	EXPECT(libj2_str_to_j2i(buf, SIZE_MAX, NULL, NULL, NULL, &a) == ERANGE);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	libj2_j2i_min(&a);
	a_saved = a;
	libj2_minus_j2i_to_j2u(&a, &u);
	libj2_j2u_add_ju(&u, 1);
	a = (struct libj2_j2i){111, 222};
	EXPECT(libj2_j2u_to_str(&u, &buf[1], sizeof(buf) - 1U, NULL) < sizeof(buf) - 1U);
	buf[0] = '-';
	EXPECT(libj2_str_to_j2i(buf, SIZE_MAX, NULL, NULL, NULL, &a) == ERANGE);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	return 0;
}

#endif
