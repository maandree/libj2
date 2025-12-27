/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_ji_sub_ji_to_j2i(intmax_t a, intmax_t b, struct libj2_j2i *res);
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
check(uintmax_t ua, uintmax_t ub)
{
	intmax_t a = ua >> (LIBJ2_JU_BIT - 1U) ? -(intmax_t)~ua - 1 : (intmax_t)ua;
	intmax_t b = ub >> (LIBJ2_JU_BIT - 1U) ? -(intmax_t)~ub - 1 : (intmax_t)ub;
	struct libj2_j2i r, expected;
	struct libj2_j2u wa, wb;

#if INTMAX_MIN + 1 != -INTMAX_MAX
	if (ua == (UINTMAX >> 1) + 1U || ub == (UINTMAX >> 1) + 1U)
		return;
#endif

	wa.low = ua;
	wb.low = ub;

	wa.high = a < 0 ? UINTMAX_MAX : 0;
	wb.high = b < 0 ? UINTMAX_MAX : 0;

	libj2_minus_j2u(&wb);
	libj2_j2u_add_j2u_to_j2u(&wa, &wb, (void *)&expected);
	libj2_ji_sub_ji_to_j2i(a, b, &r);
	EXPECT(libj2_j2i_eq_j2i(&r, &expected));
}


int
main(void)
{
	uintmax_t a, b, max, min, umax, vs[12];
	unsigned i, j, k;

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

	for (i = 0; i < 12U; i++)
		for (j = 0; j < 12U; j++)
			check(vs[i], vs[j]);
	for (j = 0; j < 256U; j++) {
		for (k = 0; k < 4U; k++) {
			a = random_ju() >> 1;
			b = random_ju() >> 1;
			if (k & 1U) a = ~a;
			if (k & 2U) b = ~b;
			check(a, b);
			for (i = 0; k < 2U && i < 12U; i++) {
				check(a, vs[i]);
				check(vs[i], a);
			}
		}
	}

	return 0;
}

#endif
