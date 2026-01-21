/* See LICENSE file for copyright and license details. */
#include "common.h"
#include <errno.h>
#ifndef TEST


static int
from_generic(const unsigned char *s, size_t slen, const unsigned char **end,
             const intmax_t symbols[256], unsigned radix, struct libj2_j2u *a)
{
	const uintmax_t high_required_at = (UINTMAX_MAX - radix + 1U) / radix;
	uintmax_t radix_pow[9];
	uintmax_t v;
	size_t i, x;

	for (i = 0; i < slen; i++)
		if (symbols[s[i]] < 0)
			break;
	slen = i;
	*end = &s[slen];

	for (;;) {
		if (!slen)
			return 0;
		a->low *= (uintmax_t)radix;
		a->low += (uintmax_t)symbols[*s++];
		slen--;
		if (a->low > high_required_at) {
			if (!slen)
				return 0;
			break;
		}
	}

	radix_pow[0] = 1U;
	radix_pow[1] = (uintmax_t)radix;
	radix_pow[2] = (uintmax_t)radix * radix_pow[1];
	radix_pow[3] = (uintmax_t)radix * radix_pow[2];
	radix_pow[4] = (uintmax_t)radix * radix_pow[3];
	radix_pow[5] = (uintmax_t)radix * radix_pow[4];
	radix_pow[6] = (uintmax_t)radix * radix_pow[5];
	radix_pow[7] = (uintmax_t)radix * radix_pow[6];
	radix_pow[8] = (uintmax_t)radix * radix_pow[7];

	x = slen & 7U;
	x = x ? x : 8U;
	slen -= x;
	if (libj2_j2u_mul_ju_overflow(a, radix_pow[x]))
		return ERANGE;
	v = 0;
	switch (x) {
		while (slen) {
			slen -= 8U;
			if (libj2_j2u_mul_ju_overflow(a, radix_pow[8]))
				return ERANGE;
			v = 0;
			/* This isn't even a case, but GCC warns fall-through here */
			/* fall-through */
		case 8:
			v += (uintmax_t)symbols[*s++] * radix_pow[7]; /* fall-through */
		case 7:
			v += (uintmax_t)symbols[*s++] * radix_pow[6]; /* fall-through */
		case 6:
			v += (uintmax_t)symbols[*s++] * radix_pow[5]; /* fall-through */
		case 5:
			v += (uintmax_t)symbols[*s++] * radix_pow[4]; /* fall-through */
		case 4:
			v += (uintmax_t)symbols[*s++] * radix_pow[3]; /* fall-through */
		case 3:
			v += (uintmax_t)symbols[*s++] * radix_pow[2]; /* fall-through */
		case 2:
			v += (uintmax_t)symbols[*s++] * radix_pow[1]; /* fall-through */
		case 1:
			v += (uintmax_t)symbols[*s++];
			if (libj2_j2u_add_ju_overflow(a, v))
				return ERANGE;
		}
	}

	return 0;
}


static int
from_power_of_two(const unsigned char *s, size_t slen, const unsigned char **end,
                  const intmax_t symbols[256], unsigned radix, struct libj2_j2u *a)
{
	uintmax_t high_required_at;
	uintmax_t v;
	unsigned shift, u, shift_mul[9];
	size_t i, x;

	shift = 0;
	for (u = radix; u >>= 1;)
		shift += 1U;

	for (i = 0; i < slen; i++)
		if (symbols[s[i]] < 0)
			break;
	slen = i;
	*end = &s[slen];

	high_required_at = (uintmax_t)1 << (LIBJ2_JU_BIT - shift);
	for (;;) {
		if (!slen)
			return 0;
		a->low <<= shift;
		a->low |= (uintmax_t)symbols[*s++];
		slen--;
		if (a->low >= high_required_at) {
			if (!slen)
				return 0;
			break;
		}
	}

	shift_mul[0] = 0U;
	shift_mul[1] = shift_mul[0] + shift;
	shift_mul[2] = shift_mul[1] + shift;
	shift_mul[3] = shift_mul[2] + shift;
	shift_mul[4] = shift_mul[3] + shift;
	shift_mul[5] = shift_mul[4] + shift;
	shift_mul[6] = shift_mul[5] + shift;
	shift_mul[7] = shift_mul[6] + shift;
	shift_mul[8] = shift_mul[7] + shift;

	x = slen & 7U;
	x = x ? x : 8U;
	slen -= x;
	if (libj2_j2u_lsh_overflow(a, shift_mul[x]))
		return ERANGE;
	v = 0;
	switch (x) {
		while (slen) {
			slen -= 8U;
			if (libj2_j2u_lsh_overflow(a, shift_mul[8]))
				return ERANGE;
			v = 0;
			/* This isn't even a case, but GCC warns fall-through here */
			/* fall-through */
		case 8:
			v |= (uintmax_t)symbols[*s++] << shift_mul[7]; /* fall-through */
		case 7:
			v |= (uintmax_t)symbols[*s++] << shift_mul[6]; /* fall-through */
		case 6:
			v |= (uintmax_t)symbols[*s++] << shift_mul[5]; /* fall-through */
		case 5:
			v |= (uintmax_t)symbols[*s++] << shift_mul[4]; /* fall-through */
		case 4:
			v |= (uintmax_t)symbols[*s++] << shift_mul[3]; /* fall-through */
		case 3:
			v |= (uintmax_t)symbols[*s++] << shift_mul[2]; /* fall-through */
		case 2:
			v |= (uintmax_t)symbols[*s++] << shift_mul[1]; /* fall-through */
		case 1:
			v |= (uintmax_t)symbols[*s++];
			libj2_j2u_or_ju(a, v);
		}
	}

	return 0;
}


int
libj2_str_to_j2u_sign(const char *str, size_t slen, char **end, const char *digits1,
                      const char *digits2, struct libj2_j2u *a, int *negative)
{
	const unsigned char *s = (const unsigned char *)str;
	intmax_t symbols[256];
	unsigned i, radix = 0;
	struct libj2_j2u a_discard;
	char *end_discard;
	int r;

	if (negative)
		*negative = 0;

	if (!end)
		end = &end_discard;
	if (!a)
		a = &a_discard;
	libj2_j2u_zero(a);

	if (!s)
		slen = 0;
	if (!digits1) {
		digits1 = "0123456789";
		if (digits2)
			goto einval;
	}

	for (i = 0; i < sizeof(symbols) / sizeof(*symbols); i++)
		symbols[i] = -2;
	symbols[' '] = -1;
	symbols['\r'] = -1;
	symbols['\t'] = -1;
	symbols['\f'] = -1;
	symbols['\v'] = -1;
	symbols['\n'] = -1;
	symbols['+'] = -1;
	if (negative)
		symbols['-'] =  -3;
	while (digits1[radix]) {
		if (symbols[(unsigned char)digits1[radix]] >= 0)
			goto einval;
		symbols[(unsigned char)digits1[radix]] = (intmax_t)radix;
		radix++;
	}

	if (digits2) {
		for (i = 0; digits2[i]; i++) {
			if (symbols[(unsigned char)digits2[i]] >= 256)
				goto einval;
			else if (symbols[(unsigned char)digits2[i]] >= 0)
				if (symbols[(unsigned char)digits2[i]] != (intmax_t)i)
					goto einval;
			symbols[(unsigned char)digits2[i]] = (intmax_t)(i | 256U);
		}
		if (i != radix)
			goto einval;
		for (i = 0; digits2[i]; i++)
			symbols[(unsigned char)digits2[i]] &= 255;
	}

	if (radix < 2) {
	einval:
		*(const unsigned char **)(void *)end = s;
		return EINVAL;
	}

	for (;; slen--, s++) {
		if (!slen)
			goto einval;
		if (symbols[*s] == -3) {
			*negative ^= 1;
		} else if (symbols[*s] != -1) {
			if (symbols[*s] >= 0)
				break;
			goto einval;
		}
	}
	if (symbols[(unsigned char)'-'] == -3)
		symbols[(unsigned char)'-'] = -1;

	while (slen && symbols[*s] == 0) {
		s++;
		slen--;
	}

	if ((radix & (radix - 1U)) == 0U)
		r = from_power_of_two(s, slen, (void *)end, symbols, radix, a);
	else
		r = from_generic(s, slen, (void *)end, symbols, radix, a);
	if (r == ERANGE)
		libj2_j2u_max(a);
	return r;
}


#else

int
main(void)
{
	/* Primarily tested via libj2_str_to_j2u */

	struct libj2_j2u a;
	int neg;

	EXPECT(libj2_str_to_j2u_sign("-1", SIZE_MAX, NULL, NULL, NULL, &a, NULL) == EINVAL);

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("-1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("0", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 0));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("-0", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 0));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("--1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("---1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign(" - - - 123", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 123));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("-", SIZE_MAX, NULL, "*+-", NULL, &a, &neg) == 0);
	EXPECT(neg == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("-+1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("+-1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign("- 1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	neg = 333;
	EXPECT(libj2_str_to_j2u_sign(" -1", SIZE_MAX, NULL, NULL, NULL, &a, &neg) == 0);
	EXPECT(neg == 1);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	return 0;
}

#endif
