/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_j2i_to_j2u(const struct libj2_j2i *a, struct libj2_j2u *res);


#else

int
main(void)
{
	struct libj2_j2u u;
	struct libj2_j2i v;
	uintmax_t a, b, i;

	for (i = 0; i < 10U; i++) {
		u = (struct libj2_j2u){111, 222};
		v.high = a = UINTMAX_MAX - i;
		v.low = b = i;
		libj2_j2i_to_j2u(&v, &u);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		u = (struct libj2_j2u){111, 222};
		v.high = a = i;
		v.low = b = UINTMAX_MAX - i;
		libj2_j2i_to_j2u(&v, &u);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		u = (struct libj2_j2u){111, 222};
		v.high = a = (uintmax_t)INTMAX_MAX + i;
		v.low = b = i;
		libj2_j2i_to_j2u(&v, &u);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		u = (struct libj2_j2u){111, 222};
		v.high = a = (uintmax_t)INTMAX_MIN + i;
		v.low = b = i;
		libj2_j2i_to_j2u(&v, &u);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		u = (struct libj2_j2u){111, 222};
		v.high = a = (uintmax_t)INTMAX_MAX - i;
		v.low = b = i;
		libj2_j2i_to_j2u(&v, &u);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);

		u = (struct libj2_j2u){111, 222};
		v.high = a = (uintmax_t)INTMAX_MIN - i;
		v.low = b = i;
		libj2_j2i_to_j2u(&v, &u);
		EXPECT(v.high == a);
		EXPECT(v.low == b);
		EXPECT(u.high == a);
		EXPECT(u.low == b);
	}

	return 0;
}

#endif
