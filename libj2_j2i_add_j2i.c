/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_add_j2i(struct libj2_j2i *a, const struct libj2_j2i *b);


#else

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


static void
check_(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
       uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	struct libj2_j2i a, b, r, a_saved, b_saved, expected, expected_plus_one, expected_minus_one;
	int carry;

	a_saved = (struct libj2_j2i){.high = a_high, .low = a_low};
	b_saved = (struct libj2_j2i){.high = b_high, .low = b_low};
	expected = (struct libj2_j2i){.high = r_high, .low = r_low};

	libj2_j2i_add_ji_to_j2i(&expected, +1, &expected_plus_one);
	libj2_j2i_add_ji_to_j2i(&expected, -1, &expected_minus_one);

	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i(&a, &b);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i(&a, &b, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i(&a, &b, &a);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i(&a, &b, &b);
	EXPECT(libj2_j2i_eq_j2i(&b, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2i_add_j2i_overflow(&a, &b) == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2i_sat_add_j2i(&a, &b);
	EXPECT(r_overflow > 0 ? libj2_j2i_is_max(&a) :
	       r_overflow ? libj2_j2i_is_min(&a) : libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2i_add_j2i_overflow_p((const struct libj2_j2i *)&a, (const struct libj2_j2i *)&b) == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2i_add_j2i_to_j2i_overflow(&a, &b, &r) == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2i_add_j2i_to_j2i_overflow(&a, &b, &a) == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	EXPECT(libj2_j2i_add_j2i_to_j2i_overflow(&a, &b, &b) == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2i_sat_add_j2i_to_j2i(&a, &b, &r);
	EXPECT(r_overflow > 0 ? libj2_j2i_is_max(&r) :
	       r_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2i_sat_add_j2i_to_j2i(&a, &b, &a);
	EXPECT(r_overflow > 0 ? libj2_j2i_is_max(&a) :
	       r_overflow ? libj2_j2i_is_min(&a) : libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	a = a_saved;
	b = b_saved;
	libj2_j2i_sat_add_j2i_to_j2i(&a, &b, &b);
	EXPECT(r_overflow > 0 ? libj2_j2i_is_max(&b) :
	       r_overflow ? libj2_j2i_is_min(&b) : libj2_j2i_eq_j2i(&b, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	carry = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_carry(&a, &b, &carry);
	EXPECT(carry == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = 0;
	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &r, &carry);
	EXPECT(carry == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &a, &carry);
	EXPECT(carry == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = 0;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &b, &carry);
	EXPECT(carry == r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	carry = +1;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_carry(&a, &b, &carry);
	EXPECT(carry >= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_plus_one));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = +1;
	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &r, &carry);
	EXPECT(carry >= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected_plus_one));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = +1;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &a, &carry);
	EXPECT(carry >= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_plus_one));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = +1;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &b, &carry);
	EXPECT(carry >= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &expected_plus_one));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	carry = -1;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_carry(&a, &b, &carry);
	EXPECT(carry <= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_minus_one));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = -1;
	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &r, &carry);
	EXPECT(carry <= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected_minus_one));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = -1;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &a, &carry);
	EXPECT(carry <= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_minus_one));
	EXPECT(libj2_j2i_eq_j2i(&b, &b_saved));

	carry = -1;
	a = a_saved;
	b = b_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &b, &b, &carry);
	EXPECT(carry <= r_overflow);
	EXPECT(libj2_j2i_eq_j2i(&b, &expected_minus_one));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low)
{
	uintmax_t a_neg = a_high >> (LIBJ2_JU_BIT - 1U);
	uintmax_t b_neg = b_high >> (LIBJ2_JU_BIT - 1U);
	uintmax_t r_high = 0, r_low = 0, carry = 0;
	int r_overflow = 0;
	unsigned i;

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a_low >> i) & 1U;
		carry += (b_low >> i) & 1U;
		r_low |= (carry & 1U) << i;
		carry >>= 1;
	}

	for (i = 0; i < LIBJ2_JU_BIT - 1U; i++) {
		carry += (a_high >> i) & 1U;
		carry += (b_high >> i) & 1U;
		r_high |= (carry & 1U) << i;
		carry >>= 1;
	}

	carry += (a_high >> i) & 1U;
	carry += (b_high >> i) & 1U;
	r_high |= (carry & 1U) << i;
	carry >>= 1;

	if (a_neg)
		carry ^= 1U;

	if (a_neg ^ b_neg)
		r_overflow = 0;
	else if (a_neg)
		r_overflow = -!(r_high >> (LIBJ2_JU_BIT - 1U));
	else
		r_overflow = !!(r_high >> (LIBJ2_JU_BIT - 1U));

	check_(a_high, a_low, b_high, b_low, r_high, r_low, r_overflow);
}


static void
check_manual(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
             uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	check_(a_high, a_low, b_high, b_low, r_high, r_low, r_overflow);
	check(a_high, a_low, b_high, b_low);
}


static void
check_double(uintmax_t high, uintmax_t low)
{
	struct libj2_j2i a, r, a_saved, expected, b;
	uintmax_t expected_high = (high << 1 | low >> (LIBJ2_JU_BIT - 1U));
	uintmax_t expected_low = low << 1;
	int expected_overflow = (int)(high >> (LIBJ2_JU_BIT - 2U));
	struct libj2_j2i expected_plus_one, expected_minus_one;
	int carry;

	expected_overflow ^= expected_overflow >> 1;
	expected_overflow &= 1;

	if (high >> (LIBJ2_JU_BIT - 1U))
		expected_overflow = -expected_overflow;

	a_saved = (struct libj2_j2i){.high = high, .low = low};
	expected = (struct libj2_j2i){.high = expected_high, .low = expected_low};

	libj2_j2i_add_ji_to_j2i(&expected, +1, &expected_plus_one);
	libj2_j2i_add_ji_to_j2i(&expected, -1, &expected_minus_one);

	a = a_saved;
	b = a_saved;
	libj2_j2i_add_j2i(&a, &b);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	a = a_saved;
	libj2_j2i_add_j2i(&a, &a);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i(&a, &a, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	a = a_saved;
	libj2_j2i_add_j2i_to_j2i(&a, &a, &a);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	a = a_saved;
	EXPECT(libj2_j2i_add_j2i_overflow(&a, &a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	a = a_saved;
	libj2_j2i_sat_add_j2i(&a, &a);
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&a) :
	       expected_overflow ? libj2_j2i_is_min(&a) : libj2_j2i_eq_j2i(&a, &expected));

	a = a_saved;
	EXPECT(libj2_j2i_add_j2i_overflow_p((const struct libj2_j2i *)&a, (const struct libj2_j2i *)&a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	EXPECT(libj2_j2i_add_j2i_to_j2i_overflow(&a, &a, &r) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	a = a_saved;
	EXPECT(libj2_j2i_add_j2i_to_j2i_overflow(&a, &a, &a) == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	libj2_j2i_sat_add_j2i_to_j2i(&a, &a, &r);
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&r) :
	       expected_overflow ? libj2_j2i_is_min(&r) : libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	a = a_saved;
	libj2_j2i_sat_add_j2i_to_j2i(&a, &a, &a);
	EXPECT(expected_overflow > 0 ? libj2_j2i_is_max(&a) :
	       expected_overflow ? libj2_j2i_is_min(&a) : libj2_j2i_eq_j2i(&a, &expected));

	carry = 0;
	a = a_saved;
	libj2_j2i_add_j2i_carry(&a, &a, &carry);
	EXPECT(carry == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	carry = 0;
	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &a, &r, &carry);
	EXPECT(carry == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	carry = 0;
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &a, &a, &carry);
	EXPECT(carry == expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected));

	carry = +1;
	a = a_saved;
	libj2_j2i_add_j2i_carry(&a, &a, &carry);
	EXPECT(carry >= expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_plus_one));

	carry = +1;
	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &a, &r, &carry);
	EXPECT(carry >= expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected_plus_one));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	carry = +1;
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &a, &a, &carry);
	EXPECT(carry >= expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_plus_one));

	carry = -1;
	a = a_saved;
	libj2_j2i_add_j2i_carry(&a, &a, &carry);
	EXPECT(carry <= expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_minus_one));

	carry = -1;
	r = (struct libj2_j2i){111, 222};
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &a, &r, &carry);
	EXPECT(carry <= expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected_minus_one));
	EXPECT(libj2_j2i_eq_j2i(&a, &a_saved));

	carry = -1;
	a = a_saved;
	libj2_j2i_add_j2i_to_j2i_carry(&a, &a, &a, &carry);
	EXPECT(carry <= expected_overflow);
	EXPECT(libj2_j2i_eq_j2i(&a, &expected_minus_one));
}


int
main(void)
{
	uintmax_t a, b, c, d, max, min, umax, vs[12];
	unsigned i, ii, ij, jj, k;
	struct libj2_j2i u, v;
	int carry;

	srand((unsigned)time(NULL));

	umax = UINTMAX_MAX;
	max = umax >> 1;
	min = ~max;

	vs[0] = 0U;
	vs[1] = 1U;
	vs[2] = 2U;
	vs[3] = umax - 0U;
	vs[4] = umax - 1U;
	vs[5] = umax - 2U;
	vs[6] = max - 0U;
	vs[7] = max - 1U;
	vs[8] = max - 2U;
	vs[9] = min + 0U;
	vs[10] = min + 1U;
	vs[11] = min + 2U;

	check_manual(0, 0, 0, 0, 0, 0, 0);
	check_manual(0, 1, 0, 1, 0, 2, 0);
	check_manual(0, UINTMAX_MAX, 0, 1, 1, 0, 0);
	check_manual(0, UINTMAX_MAX, 0, UINTMAX_MAX, 1, UINTMAX_MAX - 1U, 0);
	check_manual(UINTMAX_MAX >> 1, UINTMAX_MAX, UINTMAX_MAX >> 1, UINTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX - 1U, +1);
	check_manual((UINTMAX_MAX >> 1) + 1U, 0, (UINTMAX_MAX >> 1) + 1U, 0, 0, 0, -1);

	for (i = 0; i < 256; i++)
		check(random_ju() >> 1, random_ju(), random_ju() >> 1, random_ju());

	check_double(0, 0);
	check_double(0, UINTMAX_MAX);
	check_double(UINTMAX_MAX, UINTMAX_MAX);
	check_double(UINTMAX_MAX, 0);
	check_double(UINTMAX_MAX >> 1, 0);
	check_double(UINTMAX_MAX >> 1, UINTMAX_MAX);
	check_double((UINTMAX_MAX >> 1) + 1U, 0);
	for (i = 0; i < 256; i++) {
		check_double(0, random_ju());
		check_double(random_ju(), 0);
		check_double(random_ju(), UINTMAX_MAX);
		check_double(random_ju(), random_ju());
		check_double(UINTMAX_MAX >> 1, random_ju());
		check_double(UINTMAX_MAX, random_ju());
		check_double((UINTMAX_MAX >> 1) + 1U, random_ju());
	}

	check_manual((UINTMAX_MAX >> 1) - 1U, UINTMAX_MAX - 1U, 1, 1, UINTMAX_MAX >> 1, UINTMAX_MAX, 0);
	check_manual((UINTMAX_MAX >> 1) - 1U, UINTMAX_MAX - 1U, 1, 2, ~(uintmax_t)INTMAX_MAX, 0, 1);
	check_manual((UINTMAX_MAX >> 1) - 1U, UINTMAX_MAX - 1U, 1, 3, ~(uintmax_t)INTMAX_MAX, 1, 1);

	for (k = 0; k < 16U; k++) {
		a = random_ju() >> 1;
		b = random_ju() >> 1;
		c = random_ju() >> 1;
		d = random_ju() >> 1;
		if (k & 1U) a = ~a;
		if (k & 2U) b = ~b;
		if (k & 4U) c = ~c;
		if (k & 8U) d = ~d;
		check(a, b, c, d);
		for (i = 0; k < 8U && i < 12U; i++) {
			check(a, b, c, vs[i]);
			check(a, b, vs[i], c);
			check(a, vs[i], b, c);
			check(vs[i], a, b, c);
			for (ii = 0; k < 4U && ii < 12U; ii++) {
				check(a, b, vs[i], vs[ii]);
				check(a, vs[i], b, vs[ii]);
				check(a, vs[i], vs[ii], b);
				check(vs[i], a, b, vs[ii]);
				check(vs[i], a, vs[ii], b);
				check(vs[i], vs[ii], a, b);
				for (ij = 0; k < 2U && ij < 12U; ij++) {
					check(vs[i], vs[ii], vs[ij], a);
					check(vs[i], vs[ii], a, vs[ij]);
					check(vs[i], a, vs[ii], vs[ij]);
					check(a, vs[i], vs[ii], vs[ij]);
					for (jj = 0; k < 1U && jj < 12U; jj++)
						check(vs[i], vs[ii], vs[ij], vs[jj]);
				}
			}
		}
	}

	carry = +1;
	libj2_j2i_max(&u);
	libj2_j2i_zero(&v);
	libj2_j2i_add_j2i_to_j2i_carry(&u, &v, &u, &carry);
	EXPECT(carry == +1);
	EXPECT(libj2_j2i_is_min(&u));
	EXPECT(libj2_j2i_is_zero(&v));

	carry = +1;
	libj2_j2i_max(&u);
	libj2_j2i_zero(&v);
	libj2_j2i_add_j2i_carry(&u, &v, &carry);
	EXPECT(carry == +1);
	EXPECT(libj2_j2i_is_min(&u));
	EXPECT(libj2_j2i_is_zero(&v));

	carry = -1;
	libj2_j2i_min(&u);
	libj2_j2i_zero(&v);
	libj2_j2i_add_j2i_to_j2i_carry(&u, &v, &u, &carry);
	EXPECT(carry == -1);
	EXPECT(libj2_j2i_is_max(&u));
	EXPECT(libj2_j2i_is_zero(&v));

	carry = -1;
	libj2_j2i_min(&u);
	libj2_j2i_zero(&v);
	libj2_j2i_add_j2i_carry(&u, &v, &carry);
	EXPECT(carry == -1);
	EXPECT(libj2_j2i_is_max(&u));
	EXPECT(libj2_j2i_is_zero(&v));

	return 0;
}

#endif
