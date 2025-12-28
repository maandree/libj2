/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ji_add_ji_to_j2i(intmax_t a, intmax_t b, struct libj2_j2i *res);


#else

static intmax_t
random_ji(void)
{
	size_t n = LIBJ2_JU_BIT - 1U;
	intmax_t r = 0;
	while (n--)
		if (rand() < rand())
			r |= (intmax_t)1 << n;
	if (rand() < rand()) {
		r = -r;
#if INTMAX_MIN + 1 == -INTMAX_MAX
		r -= 1;
#endif
	}
	return r;
}


static void
get_expected(intmax_t a, intmax_t b, uintmax_t *expected_high, uintmax_t *expected_low)
{
	uintmax_t pos, neg;
	if (a >= 0 && b >= 0) {
		*expected_high = 0;
		*expected_low = (uintmax_t)a + (uintmax_t)b;
	} else if (a <= 0 && b <= 0) {
		*expected_high = UINTMAX_MAX;
		*expected_low = (uintmax_t)a + (uintmax_t)b;
	} else if (a < 0) {
		pos = (uintmax_t)b;
		neg = (uintmax_t)-(a + 1) + 1U;
		goto pos_neg;
	} else {
		pos = (uintmax_t)a;
		neg = (uintmax_t)-(b + 1) + 1U;
	pos_neg:
		if (pos >= neg)
			*expected_high = 0;
		else
			*expected_high = UINTMAX_MAX;
		*expected_low = pos - neg;
	}
}


static void
check(intmax_t a, intmax_t b)
{
	struct libj2_j2i r;
	uintmax_t expected_high, expected_low;

	get_expected(a, b, &expected_high, &expected_low);

	r = (struct libj2_j2i){111, 222};
	libj2_ji_add_ji_to_j2i(a, b, &r);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

#if INTMAX_MIN + 1 == -INTMAX_MAX
	if (a == INTMAX_MIN || b == INTMAX_MIN)
		return;
#endif

	r = (struct libj2_j2i){111, 222};
	libj2_ji_add_ji_to_j2i(-a, -b, &r);
	libj2_minus_j2i(&r);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);
}


static void
check_manual(intmax_t a, intmax_t b, uintmax_t expected_high, uintmax_t expected_low)
{
	struct libj2_j2i r;

	r = (struct libj2_j2i){111, 222};
	libj2_ji_add_ji_to_j2i(a, b, &r);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

#if INTMAX_MIN + 1 == -INTMAX_MAX
	if (a == INTMAX_MIN || b == INTMAX_MIN)
		goto check;
#endif

	r = (struct libj2_j2i){111, 222};
	libj2_ji_add_ji_to_j2i(-a, -b, &r);
	libj2_minus_j2i(&r);
	EXPECT(r.high == expected_high);
	EXPECT(r.low == expected_low);

check:
	check(a, b);
}


int
main(void)
{
	unsigned i;

	srand((unsigned)time(NULL));

	check_manual(0, 0, 0, 0);
	check_manual(0, INTMAX_MAX, 0, (uintmax_t)INTMAX_MAX);
	check_manual(INTMAX_MAX, 0, 0, (uintmax_t)INTMAX_MAX);
	check_manual(INTMAX_MAX, 1, 0, UINTMAX_MAX ^ (UINTMAX_MAX >> 1));
	check_manual(1, INTMAX_MAX, 0, UINTMAX_MAX ^ (UINTMAX_MAX >> 1));
	check_manual(INTMAX_MAX, INTMAX_MAX, 0, (uintmax_t)INTMAX_MAX << 1);

	check_manual(0, -INTMAX_MAX, UINTMAX_MAX, (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)) + 1U);
	check_manual(-INTMAX_MAX, 0, UINTMAX_MAX, (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)) + 1U);
	check_manual(INTMAX_MAX, -1, 0, (uintmax_t)INTMAX_MAX - 1U);
	check_manual(-1, INTMAX_MAX, 0, (uintmax_t)INTMAX_MAX - 1U);
	check_manual(-INTMAX_MAX, 1, UINTMAX_MAX, (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)) + 2U);
	check_manual(1, -INTMAX_MAX, UINTMAX_MAX, (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)) + 2U);
	check_manual(INTMAX_MAX, -INTMAX_MAX, 0, 0);

#if INTMAX_MIN + 1 == -INTMAX_MAX
	check_manual(0, INTMAX_MIN, UINTMAX_MAX, UINTMAX_MAX ^ (UINTMAX_MAX >> 1));
	check_manual(INTMAX_MIN, 0, UINTMAX_MAX, UINTMAX_MAX ^ (UINTMAX_MAX >> 1));
	check_manual(INTMAX_MIN, 1, UINTMAX_MAX, (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)) + 1U);
	check_manual(1, INTMAX_MIN, UINTMAX_MAX, (UINTMAX_MAX ^ (UINTMAX_MAX >> 1)) + 1U);
	check_manual(INTMAX_MIN, INTMAX_MAX, UINTMAX_MAX, UINTMAX_MAX);
	check_manual(INTMAX_MIN, -INTMAX_MAX, UINTMAX_MAX, 1);
	check_manual(INTMAX_MIN, INTMAX_MIN, UINTMAX_MAX, 0);
#endif

	for (i = 0; i < 256; i++) {
		check(0, random_ji());
		check(1, random_ji());
		check(random_ji(), 0);
		check(random_ji(), 1);
		check(random_ji(), random_ji());
		check(random_ji(), INTMAX_MAX);
		check(INTMAX_MAX, random_ji());
	}

	return 0;
}

#endif
