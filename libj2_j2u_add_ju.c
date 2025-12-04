/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_add_ju(struct libj2_j2u *a, uintmax_t b);
/* TODO Add man page */


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
check_zero_low(uintmax_t high, uintmax_t low)
{
	struct libj2_j2u a, r;

	a = (struct libj2_j2u){.high = high, .low = 0};
	libj2_j2u_add_ju(&a, low);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	a = (struct libj2_j2u){.high = high, .low = 0};
	EXPECT(libj2_j2u_add_ju_overflow(&a, low) == 0);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = 0};
	libj2_j2u_add_ju_to_j2u(&a, low, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == 0);
	EXPECT(r.high == high);
	EXPECT(r.low == low);

	a = (struct libj2_j2u){.high = high, .low = 0};
	libj2_j2u_add_ju_to_j2u(&a, low, &a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = 0};
	EXPECT(libj2_j2u_add_ju_to_j2u_overflow(&a, low, &r) == 0);
	EXPECT(a.high == high);
	EXPECT(a.low == 0);
	EXPECT(r.high == high);
	EXPECT(r.low == low);

	a = (struct libj2_j2u){.high = high, .low = 0};
	EXPECT(libj2_j2u_add_ju_to_j2u_overflow(&a, low, &a) == 0);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = 0};
	libj2_ju_add_j2u_to_j2u(low, &a, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == 0);
	EXPECT(r.high == high);
	EXPECT(r.low == low);

	a = (struct libj2_j2u){.high = high, .low = 0};
	libj2_ju_add_j2u_to_j2u(low, &a, &a);
	EXPECT(a.high == high);
	EXPECT(a.low == low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = 0};
	EXPECT(libj2_ju_add_j2u_to_j2u_overflow(low, &a, &r) == 0);
	EXPECT(a.high == high);
	EXPECT(a.low == 0);
	EXPECT(r.high == high);
	EXPECT(r.low == low);

	a = (struct libj2_j2u){.high = high, .low = 0};
	EXPECT(libj2_ju_add_j2u_to_j2u_overflow(low, &a, &a) == 0);
	EXPECT(a.high == high);
	EXPECT(a.low == low);
}


static void
check_max_low(uintmax_t high, uintmax_t low)
{
	struct libj2_j2u a, r;
	uintmax_t expected_high = high + (uintmax_t)!!low;
	uintmax_t expected_low = low - 1U;
	int expected_overflow = high == UINTMAX_MAX && low;

	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	libj2_j2u_add_ju(&a, low);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	EXPECT(libj2_j2u_add_ju_overflow(&a, low) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	libj2_j2u_add_ju_to_j2u(&a, low, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == UINTMAX_MAX);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	libj2_j2u_add_ju_to_j2u(&a, low, &a);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	EXPECT(libj2_j2u_add_ju_to_j2u_overflow(&a, low, &r) == expected_overflow);
	EXPECT(a.high == high);
	EXPECT(a.low == UINTMAX_MAX);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	EXPECT(libj2_j2u_add_ju_to_j2u_overflow(&a, low, &a) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	libj2_ju_add_j2u_to_j2u(low, &a, &r);
	EXPECT(a.high == high);
	EXPECT(a.low == UINTMAX_MAX);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	libj2_ju_add_j2u_to_j2u(low, &a, &a);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	EXPECT(libj2_ju_add_j2u_to_j2u_overflow(low, &a, &r) == expected_overflow);
	EXPECT(a.high == high);
	EXPECT(a.low == UINTMAX_MAX);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = high, .low = UINTMAX_MAX};
	EXPECT(libj2_ju_add_j2u_to_j2u_overflow(low, &a, &a) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);
}


static void
self_check(uintmax_t a_high, uintmax_t a_low, uintmax_t b_high, uintmax_t b_low,
           uintmax_t r_high, uintmax_t r_low, int r_overflow)
{
	uintmax_t carry = 0;
	unsigned i;

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a_low >> i) & 1U;
		carry += (b_low >> i) & 1U;
		EXPECT((carry & 1U) == ((r_low >> i) & 1U));
		carry >>= 1;
	}

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a_high >> i) & 1U;
		carry += (b_high >> i) & 1U;
		EXPECT((carry & 1U) == ((r_high >> i) & 1U));
		carry >>= 1;
	}

	EXPECT((uintmax_t)r_overflow == carry);
}


static void
check(uintmax_t a_high, uintmax_t a_low, uintmax_t b)
{
	struct libj2_j2u a, r;
	uintmax_t expected_high = a_high + (uintmax_t)(a_low > UINTMAX_MAX - b);
	uintmax_t expected_low = a_low + b;
	int expected_overflow = a_high && !expected_high;

	self_check(a_high, a_low, 0, b, expected_high, expected_low, expected_overflow);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_add_ju(&a, b);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_add_ju_overflow(&a, b) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_add_ju_to_j2u(&a, b, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_j2u_add_ju_to_j2u(&a, b, &a);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_add_ju_to_j2u_overflow(&a, b, &r) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_j2u_add_ju_to_j2u_overflow(&a, b, &a) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_ju_add_j2u_to_j2u(b, &a, &r);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	libj2_ju_add_j2u_to_j2u(b, &a, &a);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);

	r = (struct libj2_j2u){111, 222};
	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_ju_add_j2u_to_j2u_overflow(b, &a, &r) == expected_overflow);
	EXPECT(a.high == a_high);
	EXPECT(a.low == a_low);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

	a = (struct libj2_j2u){.high = a_high, .low = a_low};
	EXPECT(libj2_ju_add_j2u_to_j2u_overflow(b, &a, &a) == expected_overflow);
	EXPECT(a.high == expected_high);
	EXPECT(a.low == expected_low);
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	check_zero_low(0, 0);
	check_zero_low(0, UINTMAX_MAX);
	check_zero_low(UINTMAX_MAX, 0);
	check_zero_low(UINTMAX_MAX, UINTMAX_MAX);
	for (i = 0; i < 256; i++) {
		check_zero_low(0, random_ju());
		check_zero_low(random_ju(), 0);
		check_zero_low(random_ju(), random_ju());
		check_zero_low(random_ju(), UINTMAX_MAX);
		check_zero_low(UINTMAX_MAX, random_ju());
	}

	check_max_low(0, 0);
	check_max_low(0, UINTMAX_MAX);
	check_max_low(UINTMAX_MAX, 0);
	check_max_low(UINTMAX_MAX, UINTMAX_MAX);
	for (i = 0; i < 256; i++) {
		check_max_low(0, random_ju());
		check_max_low(random_ju(), 0);
		check_max_low(random_ju(), 1);
		check_max_low(random_ju(), random_ju());
		check_max_low(random_ju(), UINTMAX_MAX);
		check_max_low(UINTMAX_MAX, random_ju());
	}

	for (i = 0; i < 256; i++)
		check(random_ju(), random_ju(), random_ju());

	return 0;
}

#endif
