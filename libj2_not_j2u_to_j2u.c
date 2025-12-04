/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_not_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2u a, r, a_saved;

	a.high = 0;
	a.low = 0;
	a_saved = a;
	r = (struct libj2_j2u){111, 222};
	libj2_not_j2u_to_j2u(&a, &r);
	EXPECT(r.high == UINTMAX_MAX);
	EXPECT(r.low == UINTMAX_MAX);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a.high = UINTMAX_MAX;
	a.low = UINTMAX_MAX;
	a_saved = a;
	r = (struct libj2_j2u){111, 222};
	libj2_not_j2u_to_j2u(&a, &r);
	EXPECT(r.high == 0);
	EXPECT(r.low == 0);
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	a.high = UINTMAX_C(0x45FF23);
	a.low = UINTMAX_C(0x5245FBA4);
	a_saved = a;
	r = (struct libj2_j2u){111, 222};
	libj2_not_j2u_to_j2u(&a, &r);
	EXPECT(r.high == ~(uintmax_t)UINTMAX_C(0x45FF23));
	EXPECT(r.low == ~(uintmax_t)UINTMAX_C(0x5245FBA4));
	EXPECT(libj2_j2u_eq_j2u(&a, &a_saved));

	return 0;
}

#endif
