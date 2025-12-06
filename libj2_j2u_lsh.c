/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_lsh(struct libj2_j2u *a, unsigned b);
/* TODO Add man page */


#else

static const char *patterns[] = {
	"0",
	"1111111111111111111111111111111111111111111111111111111111111111",
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111",
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111",
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111"
	"1111111111111111111111111111111111111111111111111111111111111111",
	"1010101010101001010100100010101010101011000101101011101001000110",
	"1110100100100010000010111111011101101001000010001000011110101010",
	"11111111111100001001011",
	"0010011011001",
	"110010001011110100101001010011010111101",
	NULL
};


PURE static size_t
count_ones(const char *bits)
{
	size_t n = strlen(bits);
	if (n > LIBJ2_J2U_BIT)
		bits = &bits[n - LIBJ2_J2U_BIT];
	n = 0;
	while (*bits)
		if (*bits++ == '1')
			n += 1U;
	return n;
}


static int
set(struct libj2_j2u *a, const char *bits, size_t trailing_zeroes)
{
	size_t i, n;
	char *all_bits, *p;

	n = LIBJ2_J2U_BIT + strlen(bits) + trailing_zeroes;
	EXPECT((all_bits = malloc(n + 1U)));
	memset(all_bits, '0', LIBJ2_J2U_BIT);
	p = stpcpy(&all_bits[LIBJ2_J2U_BIT], bits);
	memset(p, '0', trailing_zeroes);
	p = &p[trailing_zeroes];

	n = 0;

	a->low = 0;
	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		if (*--p == '1') {
			a->low |= (uintmax_t)1 << i;
			n += 1U;
		}
	}

	a->high = 0;
	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		if (*--p == '1') {
			a->high |= (uintmax_t)1 << i;
			n += 1U;
		}
	}

	free(all_bits);
	return n < count_ones(bits);
}


static void
self_check(void)
{
	struct libj2_j2u a = {111, 222};
	EXPECT(set(&a, "11", 8) == 0);
	EXPECT(a.high == 0);
	EXPECT(a.low == (3U << 8));
	EXPECT(set(&a, "1101", LIBJ2_JU_BIT) == 0);
	EXPECT(a.high == 13U);
	EXPECT(a.low == 0);
	EXPECT(set(&a, "1", LIBJ2_JU_BIT - 1) == 0);
	EXPECT(a.high == 0);
	EXPECT(a.low == (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)));
	EXPECT(set(&a, "111", LIBJ2_JU_BIT - 2) == 0);
	EXPECT(a.high == 1);
	EXPECT(a.low == (UINTMAX_MAX ^ (UINTMAX_MAX >> 2)));
	EXPECT(set(&a, "1", LIBJ2_J2U_BIT) == 1);
	EXPECT(a.high == 0);
	EXPECT(a.low == 0);
}


static void
check(const char *pattern)
{
	struct libj2_j2u a, a_saved, r, expected;
	unsigned i;
	int overflows;

	set(&a, pattern, 0);
	a_saved = a;
	for (i = 0; i < LIBJ2_J2U_BIT + 8U; i++) {
		overflows = set(&expected, pattern, i);

		r = a;
		libj2_j2u_lsh(&r, i);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		EXPECT(libj2_j2u_lsh_overflow(&r, i) == overflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		libj2_j2u_sat_lsh(&r, i);
		EXPECT(overflows ? libj2_j2u_is_max(&r) : libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		EXPECT(libj2_j2u_lsh_overflow_p((const struct libj2_j2u *)&r, i) == overflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &a));

		r = (struct libj2_j2u){111, 222};
		libj2_j2u_lsh_to_j2u(&a, i, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

		r = (struct libj2_j2u){111, 222};
		EXPECT(libj2_j2u_lsh_to_j2u_overflow(&a, i, &r) == overflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

		r = (struct libj2_j2u){111, 222};
		libj2_j2u_sat_lsh_to_j2u(&a, i, &r);
		EXPECT(overflows ? libj2_j2u_is_max(&r) : libj2_j2u_eq_j2u(&r, &expected));
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

		r = a;
		libj2_j2u_lsh_to_j2u(&r, i, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		EXPECT(libj2_j2u_lsh_to_j2u_overflow(&r, i, &r) == overflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		libj2_j2u_sat_lsh_to_j2u(&r, i, &r);
		EXPECT(overflows ? libj2_j2u_is_max(&r) : libj2_j2u_eq_j2u(&r, &expected));
	}
}


int
main(void)
{
	size_t i, j;
	char pattern[LIBJ2_J2U_BIT + 1U];

	self_check();
	srand((unsigned)time(NULL));

	for (i = 0; patterns[i]; i++)
		check(patterns[i]);

	for (i = 0; i < 64; i++) {
		for (j = 0; j < LIBJ2_J2U_BIT; j++)
			pattern[j] = '0' + (rand() < rand());
		pattern[LIBJ2_J2U_BIT] = '\0';
		check(pattern);
	}

	return 0;
}

#endif
