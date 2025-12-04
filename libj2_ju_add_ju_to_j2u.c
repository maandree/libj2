/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ju_add_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res);
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
self_check(uintmax_t a, uintmax_t b, uintmax_t r_high, uintmax_t r_low)
{
	uintmax_t carry = 0;
	unsigned i;

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		carry += (a >> i) & 1U;
		carry += (b >> i) & 1U;
		EXPECT((carry & 1U) == ((r_low >> i) & 1U));
		carry >>= 1;
	}

	EXPECT(r_high == carry);
}


static void
check(uintmax_t a, uintmax_t b)
{
	struct libj2_j2u r;
	uintmax_t expected_high = (uintmax_t)(a > UINTMAX_MAX - b);
	uintmax_t expected_low = a + b;

	self_check(a, b, expected_high, expected_low);

	r = (struct libj2_j2u){111, 222};
	libj2_ju_add_ju_to_j2u(a, b, &r);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);
}


static void
check_manual(uintmax_t a, uintmax_t b, uintmax_t expected_high, uintmax_t expected_low)
{
	struct libj2_j2u r;

	r = (struct libj2_j2u){111, 222};
	libj2_ju_add_ju_to_j2u(a, b, &r);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);
	check(a, b);
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	check_manual(0, 0, 0, 0);
	check_manual(0, UINTMAX_MAX, 0, UINTMAX_MAX);
	check_manual(UINTMAX_MAX, 0, 0, UINTMAX_MAX);
	check_manual(UINTMAX_MAX, 1, 1, 0);
	check_manual(1, UINTMAX_MAX, 1, 0);
	check_manual(UINTMAX_MAX, UINTMAX_MAX, 1, UINTMAX_MAX - 1U);

	for (i = 0; i < 256; i++) {
		check(0, random_ju());
		check(random_ju(), 0);
		check(random_ju(), 1);
		check(random_ju(), random_ju());
		check(random_ju(), UINTMAX_MAX);
		check(UINTMAX_MAX, random_ju());
	}

	return 0;
}

#endif
