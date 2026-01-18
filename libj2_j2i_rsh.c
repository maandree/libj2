/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_rsh(struct libj2_j2i *a, unsigned b);


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
set(struct libj2_j2i *a, const char *bits, size_t leading_signbits)
{
	size_t leading_ones = leading_signbits;
	size_t i, n;
	int punderflow = 0;
	int nunderflow = 0;
	int negative = 0;

	a->high = 0;
	a->low = 0;

	n = strlen(bits);
	if (n > LIBJ2_J2I_BIT) {
		bits = &bits[n - LIBJ2_J2I_BIT];
		n = LIBJ2_J2I_BIT;
	}

	if (n == LIBJ2_J2I_BIT)
		negative = bits[0] == '1';

	while (n && leading_signbits--) {
		--n;
		punderflow |= bits[n] == '1';
		nunderflow |= bits[n] == '0';
	}

	for (i = 0; n && i < LIBJ2_JU_BIT; i++)
		if (bits[--n] == '1')
			a->low |= (uintmax_t)1 << i;

	for (i = 0; n && i < LIBJ2_JU_BIT; i++)
		if (bits[--n] == '1')
			a->high |= (uintmax_t)1 << i;

	if (!negative)
		return +punderflow;

	for (i = LIBJ2_JU_BIT; i-- && leading_ones; leading_ones--)
		a->high |= (uintmax_t)1 << i;

	for (i = LIBJ2_JU_BIT; i-- && leading_ones; leading_ones--)
		a->low |= (uintmax_t)1 << i;

	return -nunderflow;
}


static void
check(const char *pattern)
{
	struct libj2_j2i a, a_saved, r, expected;
	unsigned i;
	int underflow;

	set(&a, pattern, 0);
	a_saved = a;
	for (i = 0; i < LIBJ2_J2I_BIT + 8U; i++) {
		underflow = set(&expected, pattern, i);

		EXPECT(libj2_j2i_is_negative(&a) ? underflow <= 0 : underflow >= 0);

		r = a;
		libj2_j2i_rsh(&r, i);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));

		r = a;
		EXPECT(libj2_j2i_rsh_underflow(&r, i) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));

		r = a;
		EXPECT(libj2_j2i_rsh_underflow_p((const struct libj2_j2i *)&r, i) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&r, &a));

		r = (struct libj2_j2i){111, 222};
		libj2_j2i_rsh_to_j2i(&a, i, &r);
		EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));

		r = (struct libj2_j2i){111, 222};
		EXPECT(libj2_j2i_rsh_to_j2i_underflow(&a, i, &r) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));

		r = a;
		libj2_j2i_rsh_to_j2i(&r, i, &r);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));

		r = a;
		EXPECT(libj2_j2i_rsh_to_j2i_underflow(&r, i, &r) == underflow);
		EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	}
}


int
main(void)
{
	size_t i, j;
	char pattern[LIBJ2_J2I_BIT + 1U];

	srand((unsigned)time(NULL));

	for (i = 0; patterns[i]; i++)
		check(patterns[i]);

	for (i = 0; i < 64; i++) {
		for (j = 1; j < LIBJ2_J2I_BIT; j++)
			pattern[j] = '0' + (rand() < rand());
		pattern[LIBJ2_J2I_BIT] = '\0';

		pattern[0] = '0';
		check(pattern);

		pattern[0] = '1';
		check(pattern);
	}

	return 0;
}

#endif
