/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2u_to_j2i(const struct libj2_j2u *a, struct libj2_j2i *res);


#else

int
main(void)
{
	struct libj2_j2u u;
	struct libj2_j2i v;
	uintmax_t a, b, i;

	for (i = 0; i < 10U; i++) {
		v = (struct libj2_j2i){111, 222};
		u.high = a = UINTMAX_MAX - i;
		u.low = b = i;
		libj2_j2u_to_j2i(&u, &v);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		v = (struct libj2_j2i){111, 222};
		u.high = a = i;
		u.low = b = UINTMAX_MAX - i;
		libj2_j2u_to_j2i(&u, &v);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		v = (struct libj2_j2i){111, 222};
		u.high = a = (uintmax_t)INTMAX_MAX + i;
		u.low = b = i;
		libj2_j2u_to_j2i(&u, &v);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		v = (struct libj2_j2i){111, 222};
		u.high = a = (uintmax_t)INTMAX_MIN + i;
		u.low = b = i;
		libj2_j2u_to_j2i(&u, &v);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		v = (struct libj2_j2i){111, 222};
		u.high = a = (uintmax_t)INTMAX_MAX - i;
		u.low = b = i;
		libj2_j2u_to_j2i(&u, &v);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		v = (struct libj2_j2i){111, 222};
		u.high = a = (uintmax_t)INTMAX_MIN - i;
		u.low = b = i;
		libj2_j2u_to_j2i(&u, &v);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);
	}

	v = (struct libj2_j2i){111, 222};
	u.high = a = 100;
	u.low = b = 200;
	libj2_j2u_rsub_ju(&u, 0);
	libj2_j2u_to_j2i(&u, &v);
	libj2_minus_j2i(&v);
	EXPECT(v.high == a);
	EXPECT(v.low == b);

	return 0;
}

#endif
