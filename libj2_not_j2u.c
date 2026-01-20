/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_not_j2u(struct libj2_j2u *a);


#else

int
main(void)
{
	struct libj2_j2u a;

	a.high = 0;
	a.low = 0;
	libj2_not_j2u(&a);
	EXPECT(a.high == UINTMAX_MAX);
	EXPECT(a.low == UINTMAX_MAX);
	libj2_not_j2u(&a);
	EXPECT(a.high == 0);
	EXPECT(a.low == 0);

	a.high = UINTMAX_C(0x45FF23);
	a.low = UINTMAX_C(0x5245FBA4);
	libj2_not_j2u(&a);
	EXPECT(a.high == ~(uintmax_t)UINTMAX_C(0x45FF23));
	EXPECT(a.low == ~(uintmax_t)UINTMAX_C(0x5245FBA4));

	return 0;
}

#endif
