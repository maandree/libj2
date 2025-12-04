/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_j2u_is_max(const struct libj2_j2u *a);
/* TODO Add man page */


#else

int
main(void)
{
	struct libj2_j2u value;
	uintmax_t a, b;
	int i, j;

	for (i = 0; i < CHAR_BIT * (int)sizeof(uintmax_t); i++) {
		for (j = 0; j < CHAR_BIT * (int)sizeof(uintmax_t); j++) {
			value.high = a = (uintmax_t)(i + 1);
			value.low = b = (uintmax_t)(j + 1);
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = (uintmax_t)1 << i;
			value.low = b = (uintmax_t)(j + 1);
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = (uintmax_t)(i + 1);
			value.low = b = (uintmax_t)1 << j;
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = (uintmax_t)1 << i;
			value.low = b = (uintmax_t)1 << j;
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)(i + 1));
			value.low = b = ~((uintmax_t)(j + 1));
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)1 << i);
			value.low = b = ~((uintmax_t)(j + 1));
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)(i + 1));
			value.low = b = ~((uintmax_t)1 << j);
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)1 << i);
			value.low = b = ~((uintmax_t)1 << j);
			EXPECT(!libj2_j2u_is_max(&value));
			EXPECT(value.high == a);
			EXPECT(value.low == b);
		}

		value.high = 0;
		value.low = a = (uintmax_t)(i + 1);
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)(i + 1);
		value.low = 0;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		value.high = 0;
		value.low = a = (uintmax_t)1 << i;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)1 << i;
		value.low = 0;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		value.high = 0;
		value.low = a = ~((uintmax_t)(i + 1));
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)(i + 1));
		value.low = 0;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		value.high = 0;
		value.low = a = ~((uintmax_t)1 << i);
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)1 << i);
		value.low = 0;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		b = ~(uintmax_t)0;

		value.high = b;
		value.low = a = (uintmax_t)(i + 1);
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)(i + 1);
		value.low = b;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == b);

		value.high = b;
		value.low = a = (uintmax_t)1 << i;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)1 << i;
		value.low = b;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == b);

		value.high = b;
		value.low = a = ~((uintmax_t)(i + 1));
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)(i + 1));
		value.low = b;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == b);

		value.high = b;
		value.low = a = ~((uintmax_t)1 << i);
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)1 << i);
		value.low = b;
		EXPECT(!libj2_j2u_is_max(&value));
		EXPECT(value.high == a);
		EXPECT(value.low == b);
	}

	value.high = 0;
	value.low = 0;
	EXPECT(!libj2_j2u_is_max(&value));
	EXPECT(value.high == 0);
	EXPECT(value.low == 0);

	a = ~(uintmax_t)0;

	value.high = 0;
	value.low = a;
	EXPECT(!libj2_j2u_is_max(&value));
	EXPECT(value.high == 0);
	EXPECT(value.low == a);

	value.high = a;
	value.low = 0;
	EXPECT(!libj2_j2u_is_max(&value));
	EXPECT(value.high == a);
	EXPECT(value.low == 0);

	value.high = a;
	value.low = a;
	EXPECT(libj2_j2u_is_max(&value) == 1);
	EXPECT(value.high == a);
	EXPECT(value.low == a);

	return 0;
}

#endif
