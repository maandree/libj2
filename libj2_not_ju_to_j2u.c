/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_not_ju_to_j2u(uintmax_t a, struct libj2_j2u *res);


#else

int
main(void)
{
	struct libj2_j2u r;

	r = (struct libj2_j2u){111, 222};
	libj2_not_ju_to_j2u(0, &r);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == UINTMAX_MAX);

	r = (struct libj2_j2u){111, 222};
	libj2_not_ju_to_j2u(UINTMAX_MAX, &r);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == 0);

	r = (struct libj2_j2u){111, 222};
	libj2_not_ju_to_j2u(UINTMAX_C(0x5245FBA4), &r);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == ~(uintmax_t)UINTMAX_C(0x5245FBA4));

	return 0;
}

#endif
