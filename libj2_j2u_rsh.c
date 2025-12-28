/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_rsh(struct libj2_j2u *a, unsigned b);


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


static int
set(struct libj2_j2u *a, const char *bits, size_t leading_zeroes)
{
	size_t i, n;
	int underflow = 0;

	a->high = 0;
	a->low = 0;

	n = strlen(bits);
	if (n > LIBJ2_J2U_BIT) {
		bits = &bits[n - LIBJ2_J2U_BIT];
		n = LIBJ2_J2U_BIT;
	}

	while (n && leading_zeroes--)
		underflow |= bits[--n] == '1';

	for (i = 0; n && i < LIBJ2_JU_BIT; i++)
		if (bits[--n] == '1')
			a->low |= (uintmax_t)1 << i;

	for (i = 0; n && i < LIBJ2_JU_BIT; i++)
		if (bits[--n] == '1')
			a->high |= (uintmax_t)1 << i;

	return underflow;
}


static void
check(const char *pattern)
{
	struct libj2_j2u a, a_saved, r, expected;
	unsigned i;
	int underflows;

	set(&a, pattern, 0);
	a_saved = a;
	for (i = 0; i < LIBJ2_J2U_BIT + 8U; i++) {
		underflows = set(&expected, pattern, i);

		r = a;
		libj2_j2u_rsh(&r, i);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		EXPECT(libj2_j2u_rsh_underflow(&r, i) == underflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		EXPECT(libj2_j2u_rsh_underflow_p((const struct libj2_j2u *)&r, i) == underflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &a));

		r = (struct libj2_j2u){111, 222};
		libj2_j2u_rsh_to_j2u(&a, i, &r);
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = (struct libj2_j2u){111, 222};
		EXPECT(libj2_j2u_rsh_to_j2u_underflow(&a, i, &r) == underflows);
		EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		libj2_j2u_rsh_to_j2u(&r, i, &r);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));

		r = a;
		EXPECT(libj2_j2u_rsh_to_j2u_underflow(&r, i, &r) == underflows);
		EXPECT(libj2_j2u_eq_j2u(&r, &expected));
	}
}


int
main(void)
{
	size_t i, j;
	char pattern[LIBJ2_J2U_BIT + 1U];

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
