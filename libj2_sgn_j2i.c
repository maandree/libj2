/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline int libj2_sgn_j2i(const struct libj2_j2i *a);


#else

#define JI_VBIT (LIBJ2_JU_BIT - 1U)


int
main(void)
{
	struct libj2_j2i value;
	uintmax_t a, b;
	unsigned i, j;

	for (i = 0; i < LIBJ2_JU_BIT; i++) {
		for (j = 0; j < LIBJ2_JU_BIT; j++) {
			value.high = a = (uintmax_t)(i + 1);
			value.low = b = j + 1U;
			EXPECT(libj2_sgn_j2i(&value) == +1);
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = (uintmax_t)1 << i;
			value.low = b = j + 1U;
			EXPECT(libj2_sgn_j2i(&value) == (i == JI_VBIT ? -1 : +1));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = (uintmax_t)(i + 1);
			value.low = b = (uintmax_t)1 << j;
			EXPECT(libj2_sgn_j2i(&value) == +1);
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = (uintmax_t)1 << i;
			value.low = b = (uintmax_t)1 << j;
			EXPECT(libj2_sgn_j2i(&value) == (i == JI_VBIT ? -1 : +1));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)(i + 1U));
			value.low = b = ~((uintmax_t)(j + 1U));
			EXPECT(libj2_sgn_j2i(&value) == -1);
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)1 << i);
			value.low = b = ~((uintmax_t)(j + 1U));
			EXPECT(libj2_sgn_j2i(&value) == (i == JI_VBIT ? +1 : -1));
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)(i + 1U));
			value.low = b = ~((uintmax_t)1 << j);
			EXPECT(libj2_sgn_j2i(&value) == -1);
			EXPECT(value.high == a);
			EXPECT(value.low == b);

			value.high = a = ~((uintmax_t)1 << i);
			value.low = b = ~((uintmax_t)1 << j);
			EXPECT(libj2_sgn_j2i(&value) == (i == JI_VBIT ? +1 : -1));
			EXPECT(value.high == a);
			EXPECT(value.low == b);
		}

		value.high = 0;
		value.low = a = (uintmax_t)(i + 1);
		EXPECT(libj2_sgn_j2i(&value) == +1);
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)(i + 1);
		value.low = 0;
		EXPECT(libj2_sgn_j2i(&value) == +1);
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		value.high = 0;
		value.low = a = (uintmax_t)1 << i;
		EXPECT(libj2_sgn_j2i(&value) == +1);
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)1 << i;
		value.low = 0;
		EXPECT(libj2_sgn_j2i(&value) == (i == JI_VBIT ? -1 : +1));
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		value.high = 0;
		value.low = a = ~((uintmax_t)(i + 1U));
		EXPECT(libj2_sgn_j2i(&value) == +1);
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)(i + 1U));
		value.low = 0;
		EXPECT(libj2_sgn_j2i(&value) == -1);
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		value.high = 0;
		value.low = a = ~((uintmax_t)1 << i);
		EXPECT(libj2_sgn_j2i(&value) == +1);
		EXPECT(value.high == 0);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)1 << i);
		value.low = 0;
		EXPECT(libj2_sgn_j2i(&value) == (i < JI_VBIT ? -1 : +1));
		EXPECT(value.high == a);
		EXPECT(value.low == 0);

		b = ~(uintmax_t)0;

		value.high = b;
		value.low = a = (uintmax_t)(i + 1);
		EXPECT(libj2_sgn_j2i(&value) == -1);
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)(i + 1);
		value.low = b;
		EXPECT(libj2_sgn_j2i(&value) == +1);
		EXPECT(value.high == a);
		EXPECT(value.low == b);

		value.high = b;
		value.low = a = (uintmax_t)1 << i;
		EXPECT(libj2_sgn_j2i(&value) == -1);
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = (uintmax_t)1 << i;
		value.low = b;
		EXPECT(libj2_sgn_j2i(&value) == (i == JI_VBIT ? -1 : +1));
		EXPECT(value.high == a);
		EXPECT(value.low == b);

		value.high = b;
		value.low = a = ~((uintmax_t)(i + 1U));
		EXPECT(libj2_sgn_j2i(&value) == -1);
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)(i + 1U));
		value.low = b;
		EXPECT(libj2_sgn_j2i(&value) == -1);
		EXPECT(value.high == a);
		EXPECT(value.low == b);

		value.high = b;
		value.low = a = ~((uintmax_t)1 << i);
		EXPECT(libj2_sgn_j2i(&value) == -1);
		EXPECT(value.high == b);
		EXPECT(value.low == a);

		value.high = a = ~((uintmax_t)1 << i);
		value.low = b;
		EXPECT(libj2_sgn_j2i(&value) == (i < JI_VBIT ? -1 : +1));
		EXPECT(value.high == a);
		EXPECT(value.low == b);
	}

	value.high = 0;
	value.low = 0;
	EXPECT(libj2_sgn_j2i(&value) == 0);
	EXPECT(value.high == 0);
	EXPECT(value.low == 0);

	a = ~(uintmax_t)0;

	value.high = 0;
	value.low = a;
	EXPECT(libj2_sgn_j2i(&value) == +1);
	EXPECT(value.high == 0);
	EXPECT(value.low == a);

	value.high = a;
	value.low = 0;
	EXPECT(libj2_sgn_j2i(&value) == -1);
	EXPECT(value.high == a);
	EXPECT(value.low == 0);

	value.high = a;
	value.low = a;
	EXPECT(libj2_sgn_j2i(&value) == -1);
	EXPECT(value.high == a);
	EXPECT(value.low == a);

	a >>= 1;

	value.high = a;
	value.low = 0;
	EXPECT(libj2_sgn_j2i(&value) == +1);
	EXPECT(value.high == a);
	EXPECT(value.low == 0);

	value.high = a;
	value.low = ~(uintmax_t)0;
	EXPECT(libj2_sgn_j2i(&value) == +1);
	EXPECT(value.high == a);
	EXPECT(value.low == ~(uintmax_t)0);

	a = UINTMAX_MAX ^ (UINTMAX_MAX >> 1);

	value.high = a;
	value.low = 0;
	EXPECT(libj2_sgn_j2i(&value) == -1);
	EXPECT(value.high == a);
	EXPECT(value.low == 0);

	value.high = a;
	value.low = ~(uintmax_t)0;
	EXPECT(libj2_sgn_j2i(&value) == -1);
	EXPECT(value.high == a);
	EXPECT(value.low == ~(uintmax_t)0);

	return 0;
}

#endif
