/* See LICENSE file for copyright and license details. */
#include "common.h"
#include <errno.h>
#ifndef TEST

/* TODO Add man page */


static size_t
to_power_of_two(const struct libj2_j2u *a, char *buf, size_t bufsize, const char *digits, unsigned radix)
{
	unsigned i, shift, bits, mask;
	unsigned ret, cur_shift;
	uintmax_t v;

	shift = 0;
	for (i = radix; i >>= 1;)
		shift += 1U;

	mask = radix - 1U;
	bits = libj2_fls_j2u(a);
	if (bits % shift)
		bits += shift - bits % shift;
	cur_shift = bits;
	ret = bits / shift;

	do {
		if (!bufsize)
			break;
		cur_shift -= shift;
		if (cur_shift >= LIBJ2_JU_BIT) {
			v = a->high >> (cur_shift - LIBJ2_JU_BIT);
		} else if (cur_shift + shift <= LIBJ2_JU_BIT) {
			v = a->low >> cur_shift;
		} else {
			v = a->low >> cur_shift;
			v |= a->high << (LIBJ2_JU_BIT % shift);
		}
		v &= mask;
		*buf++ = digits[v];
		bufsize--;
	} while (cur_shift);

	return (size_t)ret;
}


static size_t
to_generic(const struct libj2_j2u *a, char *buf, size_t bufsize, const char *digits, unsigned radix)
{
	struct libj2_j2u v = *a, digit;
	uintmax_t b = (uintmax_t)radix;
	char charstack[LIBJ2_J2U_BIT];
	size_t n = 0, i;

	while (v.high) {
		libj2_j2u_divmod_ju_to_j2u_j2u(&v, b, &v, &digit);
		charstack[n++] = digits[digit.low];
	}
	while (v.low) {
		charstack[n++] = digits[v.low % b];
		v.low /= b;
	}

	for (i = n; i && bufsize; bufsize--)
		*buf++ = charstack[--i];

	return n;
}


static size_t
to_decimal(const struct libj2_j2u *a, char *buf, size_t bufsize)
{
#define C(X)  X"0" X"1" X"2" X"3" X"4" X"5" X"6" X"7" X"8" X"9"
#define B(X)  C(X"0") C(X"1") C(X"2") C(X"3") C(X"4") C(X"5") C(X"6") C(X"7") C(X"8") C(X"9")
#define A()   B("0") B("1") B("2") B("3") B("4") B("5") B("6") B("7") B("8") B("9")

	static const char text[] = A();

#undef A
#undef B
#undef C

	struct libj2_j2u v = *a, digits;
	char charstack[LIBJ2_J2U_BIT];
	size_t n = 0, i;

	while (v.high) {
		libj2_j2u_divmod_ju_to_j2u_j2u(&v, 1000, &v, &digits);
		charstack[n++] = text[digits.low * 3U + 2U];
		charstack[n++] = text[digits.low * 3U + 1U];
		charstack[n++] = text[digits.low * 3U + 0U];
	}
	while (v.low) {
		digits.low = v.low % 1000;
		v.low /= 1000;
		charstack[n++] = text[digits.low * 3U + 2U];
		charstack[n++] = text[digits.low * 3U + 1U];
		charstack[n++] = text[digits.low * 3U + 0U];
	}

	while (charstack[n - 1U] == '0')
		n -= 1U;
	for (i = n; i && bufsize; bufsize--)
		*buf++ = charstack[--i];

	return n;
}


size_t
libj2_j2u_to_str(const struct libj2_j2u *a, char *buf, size_t bufsize, const char *digits)
{
	char symbols[256];
	unsigned i, radix = 0;
	size_t n, bufsize_m1;

	if (!buf)
		bufsize = 0;
	if (!digits)
		digits = "0123456789";

	for (i = 0; i < sizeof(symbols); i++)
		symbols[i] = 0;
	while (digits[radix]) {
		if (symbols[(unsigned char)digits[radix]])
			return 0;
		symbols[(unsigned char)digits[radix]] = 1;
		radix++;
	}

	if (radix < 2)
		return 0;

	if (libj2_j2u_is_zero(a)) {
		if (bufsize) {
			buf[0] = digits[0];
			buf[bufsize > 1] = '\0';
		}
		return 1U;
	}

	bufsize_m1 = bufsize - (size_t)(bufsize > 0);
	if ((radix & (radix - 1U)) == 0U) {
		n = to_power_of_two(a, buf, bufsize_m1, digits, radix);
		goto out;
	}
	if (radix != 10)
		goto generic;
	for (i = 0; i < 10; i++)
		if (digits[i] != (char)((unsigned)'0' + i))
			goto generic;
	n = to_decimal(a, buf, bufsize_m1);
	goto out;
generic:
	n = to_generic(a, buf, bufsize_m1, digits, radix);
out:
	if (bufsize)
		buf[n < bufsize_m1 ? n : bufsize_m1] = '\0';
	return n;
}


#else

#define BUFFER_SIZE (128U + LIBJ2_J2U_BIT)


static uintmax_t
random_ju(void)
{
	size_t n = LIBJ2_JU_BIT;
	uintmax_t r = 0;
	while (n--)
		if (rand() < rand())
			r |= (uintmax_t)1 << n;
	return r;
}


static size_t
j2u_to_str(struct libj2_j2u *a, char *buf, size_t bufsize, const char *digits)
{
	char buf2[BUFFER_SIZE];
	struct libj2_j2i b = {.high = a->high, .low = a->low};
	size_t ret = libj2_j2u_to_str(a, buf, bufsize, digits);

	if (!libj2_j2i_is_positive(&b))
		return ret;

	memset(buf2, '~', sizeof(buf2));
	EXPECT(libj2_j2i_to_str(&b, buf2, bufsize, digits) == ret);
	if (ret)
		EXPECT(!strncmp(&buf2[0], buf, bufsize));

	if (bufsize && ret) {
		libj2_minus_j2i(&b);
		memset(buf2, '~', sizeof(buf2));
		EXPECT(libj2_j2i_to_str(&b, buf2, bufsize, digits) == ret + 1U);
		if (bufsize > 1U) {
			EXPECT(buf2[0] == '-');
			EXPECT(!strncmp(&buf2[1], buf, bufsize - 2U));
			if (bufsize < ret + 2U)
				EXPECT(buf2[bufsize - 1U] == '\0');
		} else if (bufsize == 1U) {
			EXPECT(buf2[0] == '\0');
		}
	}

	return ret;
}


static void
check_(struct libj2_j2u *a, size_t bufsize, const char *digits, const char *expected_s, size_t expected_n)
{
	char buf[BUFFER_SIZE], *end;
	struct libj2_j2u a_saved = *a, v;
	size_t n;

	memset(buf, '~', sizeof(buf));
	EXPECT(j2u_to_str(a, buf, bufsize, digits) == expected_n);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	if (expected_s) {
		n = strlen(expected_s);
		EXPECT(!memcmp(buf, expected_s, n));
		EXPECT(buf[n] == '\0');
		EXPECT(buf[n + 1U] == '~');

		if (!n)
			return;

		v = (struct libj2_j2u){111, 222};
		end = NULL;
		EXPECT(libj2_str_to_j2u(expected_s, strlen(expected_s), &end, digits, NULL, &v) == 0);
		EXPECT(libj2_j2u_eq_j2u(&v, a));
		EXPECT(end);
		EXPECT(!*end);
	} else {
		EXPECT(buf[0] == '~');
		return;
	}

	for (; n; n--) {
		memset(buf, '~', sizeof(buf));
		EXPECT(j2u_to_str(a, buf, n + 1U, digits) == expected_n);
		EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
		EXPECT(!memcmp(buf, expected_s, n));
		EXPECT(buf[n] == '\0');
		EXPECT(buf[n + 1U] == '~');
	}

	memset(buf, '~', sizeof(buf));
	EXPECT(j2u_to_str(a, buf, 1, digits) == expected_n);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(buf[0] == '\0');
	EXPECT(buf[1] == '~');

	memset(buf, '~', sizeof(buf));
	EXPECT(j2u_to_str(a, buf, 0, digits) == expected_n);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(buf[0] == '~');
}


static void
check(struct libj2_j2u *a, size_t bufsize, const char *digits, const char *expected_s, size_t expected_n)
{
	char buf[BUFFER_SIZE], alphabet[17];
	size_t i;
	struct libj2_j2u a_saved = *a;

	check_(a, bufsize, digits, expected_s, expected_n);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	if (!digits)
		digits = "0123456789";
	if (strlen(digits) > sizeof(alphabet) - 1U)
		return;
	if (!expected_s)
		return;

	for (i = 0; digits[i]; i++) {
		alphabet[i] = (char)((unsigned)'a' + i);
		if (i < 10) {
			if (digits[i] != (char)((unsigned)'0' + i))
				return;
		} else if (digits[i] != (char)((unsigned)'a' + i - 10)) {
			if (digits[i] != (char)((unsigned)'A' + i - 10))
				return;
		}
	}
	alphabet[i] = '\0';

	for (i = 0; expected_s[i]; i++) {
		if (expected_s[i] <= '9')
			buf[i] = (char)('a' - '0' + expected_s[i]);
		else if (expected_s[i] <= 'Z')
			buf[i] = (char)('k' - 'A' + expected_s[i]);
		else
			buf[i] = (char)('k' - 'a' + expected_s[i]);
	}
	buf[i] = '\0';

	check_(a, bufsize, alphabet, buf, expected_n);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
}


static void
check_zero_low(const struct libj2_j2u *a_with_low, const char *digits, const char *expected)
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE], *e;
	struct libj2_j2u a;
	size_t i, j, ndigits = strlen(digits);
	int borrow;

	for (i = 0; i < ndigits; i++)
		EXPECT(digits[i] == (char)((unsigned)'0' + i));

	a = *a_with_low;
	a.high = 0;
	EXPECT(j2u_to_str(&a, buf1, BUFFER_SIZE, digits) > 0);
	i = strlen(expected);
	j = strlen(buf1);
	EXPECT(j <= i);

	memcpy(buf2, expected, i + 1U);
	borrow = 0;
	while (i--, j--) {
		int x = (int)(buf2[i] - '0');
		int y = (int)(buf1[j] - '0');
		int z = x - y - borrow;
		borrow = z < 0;
		if (borrow)
			z += (int)ndigits;
		buf2[i] = digits[z];
	}
	if (borrow) {
		while (buf2[i] == '0')
			buf2[i--] = digits[ndigits - 1U];
		buf2[i] = (char)((int)buf2[i] - 1);
	}
	e = buf2;
	while (e[0] == '0' && e[1])
		e++;
	EXPECT(*e);

	a = *a_with_low;
	a.low = 0;
	check(&a, BUFFER_SIZE, digits, e, strlen(e));
}


int
main(void)
{
	char expected[BUFFER_SIZE];
	struct libj2_j2u a;
	unsigned i, j;
	uintmax_t t;
	int n, m;

	srand((unsigned)time(NULL));

	libj2_j2u_zero(&a);
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "") == 0);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "0") == 0);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "01") == 1);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "01234") == 1);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "01234567") == 1);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "0123456789") == 1);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(j2u_to_str(&a, NULL, SIZE_MAX, "00") == 0);
	EXPECT(libj2_j2u_is_zero(&a));

	libj2_j2u_zero(&a);
	check(&a, BUFFER_SIZE, "", NULL, 0);
	check(&a, BUFFER_SIZE, "0", NULL, 0);
	check(&a, BUFFER_SIZE, "01", "0", 1);
	check(&a, BUFFER_SIZE, "01234", "0", 1);
	check(&a, BUFFER_SIZE, "01234567", "0", 1);
	check(&a, BUFFER_SIZE, "0123456789", "0", 1);
	check(&a, BUFFER_SIZE, "0123456789ab", "0", 1);
	check(&a, BUFFER_SIZE, NULL, "0", 1);

	libj2_j2u_zero(&a);
	check(&a, 2, "", NULL, 0);
	check(&a, 2, "0", NULL, 0);
	check(&a, 2, "01", "0", 1);
	check(&a, 2, "01234", "0", 1);
	check(&a, 2, "01234567", "0", 1);
	check(&a, 2, "0123456789", "0", 1);
	check(&a, 2, "0123456789ab", "0", 1);
	check(&a, 2, NULL, "0", 1);

	libj2_j2u_zero(&a);
	check(&a, 2, "ab", "a", 1);
	check(&a, 2, "abcde", "a", 1);
	check(&a, 2, "abcdefgh", "a", 1);
	check(&a, 2, "abcdefghij", "a", 1);
	check(&a, 2, "abcdefghijkl", "a", 1);

	libj2_j2u_zero(&a);
	check(&a, 1, "", NULL, 0);
	check(&a, 1, "0", NULL, 0);
	check(&a, 1, "01", "", 1);
	check(&a, 1, "01234", "", 1);
	check(&a, 1, "01234567", "", 1);
	check(&a, 1, "0123456789", "", 1);
	check(&a, 1, "0123456789ab", "", 1);
	check(&a, 1, NULL, "", 1);

	for (i = 0; i < 32; i++) {
		a.high = UINTMAX_MAX ^ (UINTMAX_MAX >> 1);
		a.high |= random_ju();
		a.low = 0;

		for (j = 0; j < LIBJ2_JU_BIT - 1U; j++) {
			n = sprintf(expected, "%jx%0*jx", a.high, (int)LIBJ2_JU_BIT / 4, a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789abcdef", expected, (size_t)n);

			n = sprintf(expected, "%jX%0*jX", a.high, (int)LIBJ2_JU_BIT / 4, a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789ABCDEF", expected, (size_t)n);

			a.high >>= 1;
		}

		a.high = UINTMAX_MAX ^ (UINTMAX_MAX >> 1);
		a.high |= random_ju();
		a.low = random_ju();

		for (j = 0; j < LIBJ2_JU_BIT - 1U; j++) {
			n = sprintf(expected, "%jx%0*jx", a.high, (int)LIBJ2_JU_BIT / 4, a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789abcdef", expected, (size_t)n);

			n = sprintf(expected, "%jX%0*jX", a.high, (int)LIBJ2_JU_BIT / 4, a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789ABCDEF", expected, (size_t)n);

			a.high >>= 1;
		}

		for (j = 0; j < LIBJ2_J2U_BIT; j++) {
			a.low >>= 1;
			a.low |= (a.high & 1U) << (LIBJ2_JU_BIT - 1U);
			a.high >>= 1;

			n = sprintf(expected, "%jx", a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789abcdef", expected, (size_t)n);

			n = sprintf(expected, "%jX", a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789ABCDEF", expected, (size_t)n);

			n = sprintf(expected, "%jo", a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "01234567", expected, (size_t)n);

			n = sprintf(expected, "%ju", a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, "0123456789", expected, (size_t)n);

			n = sprintf(expected, "%ju", a.low);
			EXPECT(n > 0);
			check(&a, BUFFER_SIZE, NULL, expected, (size_t)n);
		}

		a.high = 0;
		a.low = random_ju();
		a.low |= UINTMAX_MAX ^ (UINTMAX_MAX >> 1);
		n = sprintf(expected, "%jo", a.low);
		EXPECT(n > 0);
		libj2_j2u_lsh(&a, LIBJ2_JU_BIT - LIBJ2_JU_BIT % 3U);
		t = ((uintmax_t)1 << ((LIBJ2_JU_BIT - LIBJ2_JU_BIT % 3) / 3U)) - 1U;
		t &= random_ju();
		m = sprintf(&expected[n], "%0*jo", (int)LIBJ2_JU_BIT / 3, t);
		EXPECT(m > 0);
		n += m;
		libj2_j2u_or_ju(&a, t);
		check(&a, BUFFER_SIZE, "01234567", expected, (size_t)n);
		while (libj2_j2u_rsh(&a, 3), !libj2_j2u_is_zero(&a)) {
			expected[--n] = '\0';
			check(&a, BUFFER_SIZE, "01234567", expected, (size_t)n);
		}

		a.high = 0;
		do {
			a.low = random_ju();
		} while (!a.low);
		n = sprintf(expected, "%ju", a.low);
		EXPECT(n > 0);
		while (!libj2_j2u_mul_ju_overflow_p(&a, 10)) {
			libj2_j2u_mul_ju(&a, 10);
			j = (unsigned)random_ju() % 10U;
			if (libj2_j2u_add_ju_overflow_p(&a, j)) {
				expected[n++] = '0';
				break;
			}
			libj2_j2u_add_ju(&a, j);
			expected[n++] = (char)((unsigned)'0' + j);
		}
		expected[n] = '\0';
		check(&a, BUFFER_SIZE, "0123456789", expected, (size_t)n);
		check(&a, BUFFER_SIZE, NULL, expected, (size_t)n);
		check_zero_low(&a, "0123456789", expected);
		while (libj2_j2u_div_ju(&a, 10), !libj2_j2u_is_zero(&a)) {
			expected[--n] = '\0';
			check(&a, BUFFER_SIZE, NULL, expected, (size_t)n);
		}

		a.high = 0;
		do {
			a.low = random_ju() % 5U;
		} while (!a.low);
		n = 0;
		expected[n++] = (char)((unsigned)'0' + a.low);
		expected[n] = '\0';
		check(&a, BUFFER_SIZE, "01234", expected, (size_t)n);
		while (!libj2_j2u_mul_ju_overflow_p(&a, 5)) {
			libj2_j2u_mul_ju(&a, 5);
			j = (unsigned)random_ju() % 5U;
			if (libj2_j2u_add_ju_overflow_p(&a, j)) {
				expected[n++] = '0';
				expected[n] = '\0';
				check(&a, BUFFER_SIZE, "01234", expected, (size_t)n);
				break;
			}
			libj2_j2u_add_ju(&a, j);
			expected[n++] = (char)((unsigned)'0' + j);
			expected[n] = '\0';
			check(&a, BUFFER_SIZE, "01234", expected, (size_t)n);
		}
		check_zero_low(&a, "01234", expected);

		a.high = 0;
		do {
			a.low = random_ju() % 11U;
		} while (!a.low);
		n = 0;
		expected[n++] = (char)((unsigned)'0' + a.low);
		expected[n] = '\0';
		check(&a, BUFFER_SIZE, "0123456789:", expected, (size_t)n);
		while (!libj2_j2u_mul_ju_overflow_p(&a, 11)) {
			libj2_j2u_mul_ju(&a, 11);
			j = (unsigned)random_ju() % 11U;
			if (libj2_j2u_add_ju_overflow_p(&a, j)) {
				expected[n++] = '0';
				expected[n] = '\0';
				check(&a, BUFFER_SIZE, "0123456789:", expected, (size_t)n);
				break;
			}
			libj2_j2u_add_ju(&a, j);
			expected[n++] = (char)((unsigned)'0' + j);
			expected[n] = '\0';
			check(&a, BUFFER_SIZE, "0123456789:", expected, (size_t)n);
		}
		check_zero_low(&a, "0123456789:", expected);
	}

	return 0;
}

#endif
