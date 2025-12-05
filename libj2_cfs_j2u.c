/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_cfs_j2u(struct libj2_j2u *a);
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
cfs(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	struct libj2_j2u a_saved = *a, r, b;

	*res = (struct libj2_j2u){111, 222};
	libj2_cfs_j2u_to_j2u(a, res);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));

	r = *a;
	libj2_cfs_j2u_to_j2u(&r, &r);
	EXPECT(libj2_j2u_eq_j2u(&r, res));

	r = *a;
	libj2_cfs_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(&r, res));

	r = (struct libj2_j2u){111, 222};
	libj2_not_j2u_to_j2u(a, &b);
	libj2_sfc_j2u_to_j2u((const struct libj2_j2u *)&b, &r);
	libj2_not_j2u(&b);
	libj2_not_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(&b, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, res));

	r = *a;
	libj2_not_j2u(&r);
	libj2_sfc_j2u_to_j2u(&r, &r);
	libj2_not_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(&r, res));

	r = *a;
	libj2_not_j2u(&r);
	libj2_sfc_j2u(&r);
	libj2_not_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(&r, res));

	b = (struct libj2_j2u){333, 444};
	libj2_kfs_j2u_to_j2u(a, &b);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	libj2_j2u_sub_j2u_to_j2u(a, &b, &r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, res));

	r = *a;
	libj2_kfs_j2u(&r);
	EXPECT(libj2_j2u_eq_j2u(a, &a_saved));
	EXPECT(libj2_j2u_eq_j2u(&r, &b));
}


int
main(void)
{
	struct libj2_j2u a, r, t;
	unsigned i, j;

	libj2_j2u_max(&a);
	for (i = 0; i < LIBJ2_J2U_BIT; i++) {
		cfs(&a, &r);
		libj2_j2u_lsh_to_j2u(&a, 1, &a);
		EXPECT(libj2_j2u_eq_j2u(&r, &a));
	}
	EXPECT(libj2_j2u_is_zero(&a));
	cfs(&a, &r);
	EXPECT(libj2_j2u_is_zero(&r));

	libj2_j2u_max(&a);
	a.high = 0;
	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		cfs(&a, &r);
		libj2_j2u_lsh_to_j2u(&a, 1, &a);
		a.high = 0;
		EXPECT(libj2_j2u_eq_j2u(&r, &a));
	}
	EXPECT(libj2_j2u_is_zero(&a));

	for (j = 1; j <= 3; j++) {
		for (i = 0; i < 256; i++) {
			a.high = (j & 1) ? random_ju() : 0;
			a.low = (j & 2) ? random_ju() : 0;
			while (!libj2_j2u_is_zero(&a)) {
				cfs(&a, &r);
				libj2_j2u_sub_ju_to_j2u(&a, 1, &t);
				libj2_j2u_and_j2u(&a, &t);
				EXPECT(libj2_j2u_eq_j2u(&r, &a));
			}
		}
	}

	return 0;
}

#endif
