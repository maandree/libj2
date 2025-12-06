/* See LICENSE file for copyright and license details. */
#include "common.h"
#include <errno.h>
#ifndef TEST

/* TODO Add man page */


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
libj2_str_to_j2u(const char *str, size_t slen, char **end, const char *digits1,
                 const char *digits2, struct libj2_j2u *a)
{
	const unsigned char *s = (const unsigned char *)str;
	intmax_t symbols[256];
	unsigned i, radix = 0;
	struct libj2_j2u a_discard;
	char *end_discard;
	int r;

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
		if (symbols[*s] != -1) {
			if (symbols[*s] >= 0)
				break;
			goto einval;
		}
	}

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

CONST int
main(void)
{
	/* Primarily tested in libj2_j2u_to_str.c */

	char buf[sizeof(uintmax_t) * 8U];
	struct libj2_j2u a;
	char *end;

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 6, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 5, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 4, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1000));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("10000", 4, &end, NULL, "0123456789", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(!strcmp(end, "10000"));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 3, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 100));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 2, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 1, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 0, NULL, NULL, NULL, &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" \r\n\v+\t\f + 10000", SIZE_MAX, &end, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" \r\n\v+\t\f + 10000 0", SIZE_MAX, &end, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));
	EXPECT(end);
	EXPECT(!strcmp(end, " 0"));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" \r\n\v+\t\f + 10000x0", SIZE_MAX, &end, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));
	EXPECT(end);
	EXPECT(!strcmp(end, "x0"));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" +-- ", SIZE_MAX, &end, "-+", NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 4));
	EXPECT(end);
	EXPECT(!strcmp(end, " "));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" +-- ", SIZE_MAX, &end, "- +", NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 136));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "Ab", "Ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1));
	EXPECT(end);
	EXPECT(*end == 'a');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "Ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "AB", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "AB", "AB", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'b');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "AB", "ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "ab", "AB", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "AB", "AB", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "AB", "ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "ABB", "abb", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'B');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "AB", "abc", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'B');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "ABC", "ab", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'B');

	sprintf(buf, "%jx%jx", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdef", NULL, &a) == 0);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	sprintf(buf, "%jx%jx", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdefg", NULL, &a) == ERANGE);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	sprintf(buf, "%jx%jx0", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdef", NULL, &a) == ERANGE);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	sprintf(buf, "1%jx%jx", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdef", NULL, &a) == ERANGE);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	return 0;
}

#endif
