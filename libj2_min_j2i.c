/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_min_j2i(struct libj2_j2i *a, ... /*, NULL */);
/* TODO Add man pages
   libj2_min_j2i
   libj2_min_j2i_to_j2i
   libj2_min_j2i_return
   libj2_vmin_j2i
   libj2_vmin_j2i_to_j2i
   libj2_vmin_j2i_return
   libj2_min_j2u
   libj2_min_j2u_to_j2u
   libj2_min_j2u_return
   libj2_vmin_j2u
   libj2_vmin_j2u_to_j2u
   libj2_vmin_j2u_return
 */


#else

static struct libj2_j2i v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;


static void
reset(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;
	v1 = (struct libj2_j2i){0, 0};
	v2 = (struct libj2_j2i){0, 1};
	v3 = (struct libj2_j2i){0, 2};
	v4 = (struct libj2_j2i){0, umax - 1U};
	v5 = (struct libj2_j2i){1, 0};
	v6 = (struct libj2_j2i){1, 1};
	v7 = (struct libj2_j2i){max - 1U, 0};
	v8 = (struct libj2_j2i){max - 1U, 1};
	v9 = (struct libj2_j2i){max - 1U, umax};
	v10 = (struct libj2_j2i){max, 0};
	v11 = (struct libj2_j2i){max, 1};
	v12 = (struct libj2_j2i){max, umax - 1U};
	v13 = (struct libj2_j2i){max, umax};
}


static void
expect_untouched(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;
	EXPECT(libj2_j2i_eq_j2i(&v1, &(struct libj2_j2i){0, 0}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v2, &(struct libj2_j2i){0, 1}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v3, &(struct libj2_j2i){0, 2}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v4, &(struct libj2_j2i){0, umax - 1U}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v5, &(struct libj2_j2i){1, 0}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v6, &(struct libj2_j2i){1, 1}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v7, &(struct libj2_j2i){max - 1U, 0}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v8, &(struct libj2_j2i){max - 1U, 1}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v9, &(struct libj2_j2i){max - 1U, umax}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v10, &(struct libj2_j2i){max, 0}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v11, &(struct libj2_j2i){max, 1}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v12, &(struct libj2_j2i){max, umax - 1U}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v13, &(struct libj2_j2i){max, umax}) == 1);
}


static void
neg_reset(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;
	const uintmax_t zero = 0U;
	const uintmax_t one = 1U;
	const uintmax_t two = 2U;
	v1 = (struct libj2_j2i){~zero, ~zero};
	v2 = (struct libj2_j2i){~zero, ~one};
	v3 = (struct libj2_j2i){~zero, ~two};
	v4 = (struct libj2_j2i){~zero, ~(umax - 1U)};
	v5 = (struct libj2_j2i){~one, ~zero};
	v6 = (struct libj2_j2i){~one, ~one};
	v7 = (struct libj2_j2i){~(max - 1U), ~zero};
	v8 = (struct libj2_j2i){~(max - 1U), ~one};
	v9 = (struct libj2_j2i){~(max - 1U), ~umax};
	v10 = (struct libj2_j2i){~max, ~zero};
	v11 = (struct libj2_j2i){~max, ~one};
	v12 = (struct libj2_j2i){~max, ~(umax - 1U)};
	v13 = (struct libj2_j2i){~max, ~umax};
}


static void
neg_expect_untouched(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;
	const uintmax_t zero = 0U;
	const uintmax_t one = 1U;
	const uintmax_t two = 2U;
	EXPECT(libj2_j2i_eq_j2i(&v1, &(struct libj2_j2i){~zero, ~zero}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v2, &(struct libj2_j2i){~zero, ~one}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v3, &(struct libj2_j2i){~zero, ~two}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v4, &(struct libj2_j2i){~zero, ~(umax - 1U)}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v5, &(struct libj2_j2i){~one, ~zero}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v6, &(struct libj2_j2i){~one, ~one}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v7, &(struct libj2_j2i){~(max - 1U), ~zero}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v8, &(struct libj2_j2i){~(max - 1U), ~one}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v9, &(struct libj2_j2i){~(max - 1U), ~umax}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v10, &(struct libj2_j2i){~max, ~zero}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v11, &(struct libj2_j2i){~max, ~one}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v12, &(struct libj2_j2i){~max, ~(umax - 1U)}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v13, &(struct libj2_j2i){~max, ~umax}) == 1);
}


static void
mix_reset(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;
	v1 = (struct libj2_j2i){~max, 0};
	v2 = (struct libj2_j2i){umax, umax};
	v3 = (struct libj2_j2i){0, 0};
	v4 = (struct libj2_j2i){0, 1};
	v5 = (struct libj2_j2i){max, umax};
}


static void
mix_expect_untouched(void)
{
	const uintmax_t umax = UINTMAX_MAX;
	const uintmax_t max = UINTMAX_MAX >> 1;
	EXPECT(libj2_j2i_eq_j2i(&v1, &(struct libj2_j2i){~max, 0}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v2, &(struct libj2_j2i){umax, umax}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v3, &(struct libj2_j2i){0, 0}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v4, &(struct libj2_j2i){0, 1}) == 1);
	EXPECT(libj2_j2i_eq_j2i(&v5, &(struct libj2_j2i){max, umax}) == 1);
}


#define HEAD(X, ...) X
#define TAIL(X, ...) __VA_ARGS__

#define CHECK(MIN, ...)\
	do {\
		reset();\
		\
		r = *(HEAD(__VA_ARGS__));\
		libj2_min_j2i(&r, TAIL(__VA_ARGS__));\
		expect_untouched();\
		EXPECT(libj2_j2i_eq_j2i(&(MIN), &r));\
		\
		p = libj2_min_j2i_return(__VA_ARGS__);\
		expect_untouched();\
		EXPECT(p != NULL);\
		EXPECT(libj2_j2i_eq_j2i(&(MIN), p));\
		\
		r = (struct libj2_j2i){111, 222};\
		libj2_min_j2i_to_j2i(__VA_ARGS__, &r);\
		expect_untouched();\
		EXPECT(libj2_j2i_eq_j2i(&(MIN), &r));\
	} while (0)

#define NEG_CHECK(MIN, ...)\
	do {\
		neg_reset();\
		\
		r = *(HEAD(__VA_ARGS__));\
		libj2_min_j2i(&r, TAIL(__VA_ARGS__));\
		neg_expect_untouched();\
		EXPECT(libj2_j2i_eq_j2i(&(MIN), &r));\
		\
		p = libj2_min_j2i_return(__VA_ARGS__);\
		neg_expect_untouched();\
		EXPECT(p != NULL);\
		EXPECT(libj2_j2i_eq_j2i(&(MIN), p));\
		\
		r = (struct libj2_j2i){111, 222};\
		libj2_min_j2i_to_j2i(__VA_ARGS__, &r);\
		neg_expect_untouched();\
		EXPECT(libj2_j2i_eq_j2i(&(MIN), &r));\
	} while (0)

#define MIX_CHECK(MIN, ...)\
	do {\
		mix_reset();\
		\
		r = *(HEAD(__VA_ARGS__));\
		libj2_min_j2i(&r, TAIL(__VA_ARGS__));\
		mix_expect_untouched();\
		EXPECT(libj2_j2i_eq_j2i((MIN), &r));\
		\
		p = libj2_min_j2i_return(__VA_ARGS__);\
		mix_expect_untouched();\
		EXPECT(p != NULL);\
		EXPECT(libj2_j2i_eq_j2i((MIN), p));\
		\
		r = (struct libj2_j2i){111, 222};\
		libj2_min_j2i_to_j2i(__VA_ARGS__, &r);\
		mix_expect_untouched();\
		EXPECT(libj2_j2i_eq_j2i((MIN), &r));\
	} while (0)


static void
check_mixed(const struct libj2_j2i *i1, const struct libj2_j2i *i2, const struct libj2_j2i *i3,
            const struct libj2_j2i *i4, const struct libj2_j2i *i5)
{
	struct libj2_j2i r;
	const struct libj2_j2i *p;
	const struct libj2_j2i *is[5];
	size_t n = 0;
	size_t i, ii, iii, iv;

	if (i1)
		is[n++] = i1;
	if (i2)
		is[n++] = i2;
	if (i3)
		is[n++] = i3;
	if (i4)
		is[n++] = i4;
	if (i5)
		is[n++] = i5;

	switch (n) {
	case 2:
		MIX_CHECK(is[0], is[0], is[1], NULL);
		MIX_CHECK(is[0], is[1], is[0], NULL);
		break;

	case 3:
		MIX_CHECK(is[0], is[0], is[1], is[2], NULL);
		MIX_CHECK(is[0], is[0], is[2], is[1], NULL);
		MIX_CHECK(is[0], is[1], is[0], is[2], NULL);
		MIX_CHECK(is[0], is[2], is[0], is[1], NULL);
		MIX_CHECK(is[0], is[1], is[2], is[0], NULL);
		MIX_CHECK(is[0], is[2], is[1], is[0], NULL);
		break;

	case 4:
		for (i = 0; i < 4; i++)
			for (ii = 0; ii < 4; ii++)
				for (iii = 0; iii < 4; iii++)
					for (iv = 0; iv < 4; iv++)
						if (i != ii && i != iii && i != iv && ii != iii && ii != iv && iii != iv)
							MIX_CHECK(is[0], is[i], is[ii], is[iii], is[iv], NULL);
		break;

	default:
		return;
	}
}


int
main(void)
{
	struct libj2_j2i r;
	const struct libj2_j2i *p;
	unsigned i;

	CHECK(v1, &v1, NULL);
	CHECK(v2, &v2, NULL);
	CHECK(v3, &v3, NULL);

	CHECK(v1, &v1, &v2, NULL);
	CHECK(v1, &v2, &v1, NULL);
	CHECK(v2, &v2, &v3, NULL);
	CHECK(v2, &v3, &v2, NULL);
	CHECK(v3, &v3, &v4, NULL);
	CHECK(v3, &v4, &v3, NULL);
	CHECK(v4, &v4, &v5, NULL);
	CHECK(v4, &v5, &v4, NULL);
	CHECK(v5, &v5, &v6, NULL);
	CHECK(v5, &v6, &v5, NULL);
	CHECK(v6, &v6, &v7, NULL);
	CHECK(v6, &v7, &v6, NULL);
	CHECK(v7, &v7, &v8, NULL);
	CHECK(v7, &v8, &v7, NULL);
	CHECK(v8, &v8, &v9, NULL);
	CHECK(v8, &v9, &v8, NULL);
	CHECK(v9, &v9, &v10, NULL);
	CHECK(v9, &v10, &v9, NULL);
	CHECK(v10, &v10, &v11, NULL);
	CHECK(v10, &v11, &v10, NULL);
	CHECK(v11, &v11, &v12, NULL);
	CHECK(v11, &v12, &v11, NULL);
	CHECK(v12, &v12, &v13, NULL);
	CHECK(v12, &v13, &v12, NULL);

	CHECK(v1, &v1, &v2, &v3, &v4, &v5, &v6, NULL);
	CHECK(v1, &v2, &v1, &v3, &v4, &v5, &v6, NULL);
	CHECK(v1, &v2, &v3, &v1, &v4, &v5, &v6, NULL);
	CHECK(v1, &v2, &v3, &v4, &v1, &v5, &v6, NULL);
	CHECK(v1, &v2, &v3, &v4, &v5, &v1, &v6, NULL);
	CHECK(v1, &v2, &v3, &v4, &v5, &v6, &v1, NULL);

	CHECK(v1, &v6, &v5, &v4, &v3, &v2, &v1, NULL);
	CHECK(v1, &v6, &v5, &v4, &v3, &v1, &v2, NULL);
	CHECK(v1, &v6, &v5, &v4, &v1, &v3, &v2, NULL);
	CHECK(v1, &v6, &v5, &v1, &v4, &v3, &v2, NULL);
	CHECK(v1, &v6, &v1, &v5, &v4, &v3, &v2, NULL);
	CHECK(v1, &v1, &v6, &v5, &v4, &v3, &v2, NULL);

	CHECK(v2, &v2, &v3, &v4, &v5, &v6, NULL);
	CHECK(v2, &v3, &v2, &v4, &v5, &v6, NULL);
	CHECK(v2, &v3, &v4, &v2, &v5, &v6, NULL);
	CHECK(v2, &v3, &v4, &v5, &v2, &v6, NULL);
	CHECK(v2, &v3, &v4, &v5, &v6, &v2, NULL);

	CHECK(v2, &v6, &v5, &v4, &v3, &v2, NULL);
	CHECK(v2, &v6, &v5, &v4, &v2, &v3, NULL);
	CHECK(v2, &v6, &v5, &v2, &v4, &v3, NULL);
	CHECK(v2, &v6, &v2, &v5, &v4, &v3, NULL);
	CHECK(v2, &v2, &v6, &v5, &v4, &v3, NULL);

	CHECK(v2, &v6, &v9, &v11, &v12, &v4, &v8, &v2, &v3, &v10, &v7, &v5, &v13, NULL);
	CHECK(v2, &v12, &v2, &v11, &v13, &v7, &v4, &v9, &v10, &v6, &v3, &v8, &v5, NULL);
	CHECK(v2, &v5, &v13, &v6, &v12, &v8, &v10, &v3, &v9, &v7, &v2, &v11, &v4, NULL);
	CHECK(v2, &v4, &v13, &v10, &v11, &v5, &v12, &v9, &v3, &v7, &v6, &v8, &v2, NULL);
	CHECK(v2, &v5, &v7, &v6, &v3, &v2, &v11, &v12, &v8, &v4, &v9, &v13, &v10, NULL);
	CHECK(v2, &v3, &v8, &v7, &v10, &v11, &v13, &v12, &v5, &v4, &v2, &v6, &v9, NULL);
	CHECK(v2, &v11, &v2, &v8, &v3, &v5, &v12, &v4, &v13, &v10, &v7, &v6, &v9, NULL);
	CHECK(v2, &v8, &v6, &v2, &v10, &v9, &v13, &v12, &v4, &v7, &v11, &v5, &v3, NULL);
	CHECK(v2, &v4, &v8, &v7, &v12, &v13, &v6, &v11, &v2, &v3, &v10, &v9, &v5, NULL);
	CHECK(v2, &v13, &v11, &v4, &v8, &v10, &v12, &v5, &v3, &v2, &v9, &v7, &v6, NULL);
	CHECK(v2, &v13, &v3, &v12, &v8, &v10, &v11, &v7, &v2, &v4, &v9, &v6, &v5, NULL);
	CHECK(v2, &v9, &v8, &v13, &v7, &v5, &v6, &v11, &v12, &v4, &v3, &v2, &v10, NULL);
	CHECK(v2, &v9, &v8, &v10, &v6, &v3, &v12, &v2, &v5, &v11, &v4, &v7, &v13, NULL);
	CHECK(v2, &v5, &v4, &v12, &v13, &v8, &v7, &v9, &v6, &v10, &v3, &v2, &v11, NULL);
	CHECK(v2, &v5, &v4, &v11, &v9, &v8, &v7, &v10, &v6, &v2, &v3, &v13, &v12, NULL);
	CHECK(v2, &v12, &v13, &v10, &v7, &v6, &v5, &v2, &v11, &v4, &v3, &v8, &v9, NULL);
	CHECK(v2, &v2, &v8, &v7, &v13, &v5, &v9, &v10, &v6, &v3, &v11, &v12, &v4, NULL);
	CHECK(v2, &v3, &v7, &v13, &v9, &v6, &v8, &v5, &v12, &v4, &v11, &v2, &v10, NULL);
	CHECK(v2, &v12, &v3, &v6, &v5, &v2, &v9, &v4, &v11, &v8, &v10, &v13, &v7, NULL);
	CHECK(v2, &v13, &v7, &v4, &v3, &v12, &v2, &v9, &v5, &v10, &v11, &v6, &v8, NULL);
	CHECK(v2, &v7, &v3, &v8, &v2, &v4, &v13, &v5, &v6, &v10, &v9, &v11, &v12, NULL);
	CHECK(v2, &v2, &v3, &v13, &v8, &v12, &v5, &v11, &v9, &v10, &v4, &v7, &v6, NULL);
	CHECK(v2, &v10, &v6, &v7, &v5, &v11, &v9, &v3, &v13, &v4, &v2, &v8, &v12, NULL);
	CHECK(v2, &v6, &v9, &v12, &v7, &v2, &v10, &v4, &v13, &v11, &v3, &v5, &v8, NULL);
	CHECK(v2, &v5, &v9, &v6, &v4, &v8, &v7, &v11, &v13, &v3, &v2, &v12, &v10, NULL);
	CHECK(v2, &v10, &v11, &v2, &v9, &v12, &v7, &v5, &v3, &v8, &v13, &v6, &v4, NULL);
	CHECK(v2, &v3, &v10, &v2, &v4, &v8, &v9, &v11, &v7, &v5, &v13, &v6, &v12, NULL);
	CHECK(v2, &v8, &v10, &v11, &v6, &v5, &v2, &v9, &v4, &v3, &v13, &v7, &v12, NULL);
	CHECK(v2, &v4, &v12, &v11, &v7, &v3, &v13, &v10, &v2, &v5, &v9, &v6, &v8, NULL);
	CHECK(v2, &v7, &v13, &v12, &v3, &v4, &v8, &v11, &v9, &v10, &v6, &v2, &v5, NULL);
	CHECK(v2, &v5, &v4, &v2, &v8, &v7, &v13, &v10, &v11, &v3, &v9, &v6, &v12, NULL);
	CHECK(v2, &v7, &v8, &v10, &v2, &v4, &v11, &v9, &v12, &v6, &v13, &v5, &v3, NULL);
	CHECK(v2, &v3, &v7, &v2, &v13, &v5, &v10, &v12, &v6, &v8, &v11, &v9, &v4, NULL);
	CHECK(v2, &v12, &v13, &v6, &v9, &v4, &v11, &v8, &v3, &v2, &v7, &v10, &v5, NULL);
	CHECK(v2, &v2, &v9, &v10, &v13, &v3, &v5, &v8, &v7, &v6, &v11, &v4, &v12, NULL);
	CHECK(v2, &v7, &v5, &v10, &v11, &v3, &v12, &v4, &v9, &v6, &v13, &v2, &v8, NULL);
	CHECK(v2, &v3, &v4, &v8, &v2, &v13, &v11, &v7, &v10, &v5, &v6, &v12, &v9, NULL);
	CHECK(v2, &v7, &v2, &v13, &v5, &v10, &v3, &v9, &v6, &v4, &v11, &v8, &v12, NULL);
	CHECK(v2, &v6, &v5, &v3, &v11, &v8, &v9, &v12, &v7, &v13, &v4, &v10, &v2, NULL);
	CHECK(v2, &v13, &v6, &v5, &v4, &v3, &v8, &v2, &v7, &v9, &v10, &v11, &v12, NULL);
	CHECK(v2, &v13, &v12, &v4, &v3, &v11, &v6, &v7, &v10, &v2, &v5, &v9, &v8, NULL);
	CHECK(v2, &v13, &v6, &v7, &v2, &v8, &v4, &v5, &v12, &v11, &v3, &v10, &v9, NULL);
	CHECK(v2, &v13, &v5, &v12, &v11, &v10, &v9, &v2, &v6, &v4, &v8, &v3, &v7, NULL);
	CHECK(v2, &v8, &v7, &v6, &v13, &v9, &v3, &v11, &v10, &v4, &v2, &v12, &v5, NULL);
	CHECK(v2, &v8, &v9, &v3, &v7, &v11, &v2, &v13, &v4, &v6, &v12, &v10, &v5, NULL);
	CHECK(v2, &v4, &v5, &v13, &v2, &v7, &v8, &v9, &v10, &v11, &v3, &v6, &v12, NULL);
	CHECK(v2, &v7, &v4, &v11, &v9, &v6, &v12, &v3, &v5, &v10, &v8, &v2, &v13, NULL);
	CHECK(v2, &v8, &v9, &v6, &v2, &v11, &v5, &v13, &v3, &v7, &v10, &v12, &v4, NULL);
	CHECK(v2, &v10, &v4, &v5, &v6, &v3, &v7, &v13, &v8, &v12, &v2, &v9, &v11, NULL);
	CHECK(v2, &v9, &v3, &v8, &v12, &v5, &v6, &v2, &v10, &v11, &v4, &v7, &v13, NULL);

	NEG_CHECK(v1, &v1, NULL);
	NEG_CHECK(v2, &v2, NULL);
	NEG_CHECK(v3, &v3, NULL);

	NEG_CHECK(v2, &v1, &v2, NULL);
	NEG_CHECK(v2, &v2, &v1, NULL);
	NEG_CHECK(v3, &v2, &v3, NULL);
	NEG_CHECK(v3, &v3, &v2, NULL);
	NEG_CHECK(v4, &v3, &v4, NULL);
	NEG_CHECK(v4, &v4, &v3, NULL);
	NEG_CHECK(v5, &v4, &v5, NULL);
	NEG_CHECK(v5, &v5, &v4, NULL);
	NEG_CHECK(v6, &v5, &v6, NULL);
	NEG_CHECK(v6, &v6, &v5, NULL);
	NEG_CHECK(v7, &v6, &v7, NULL);
	NEG_CHECK(v7, &v7, &v6, NULL);
	NEG_CHECK(v8, &v7, &v8, NULL);
	NEG_CHECK(v8, &v8, &v7, NULL);
	NEG_CHECK(v9, &v8, &v9, NULL);
	NEG_CHECK(v9, &v9, &v8, NULL);
	NEG_CHECK(v10, &v9, &v10, NULL);
	NEG_CHECK(v10, &v10, &v9, NULL);
	NEG_CHECK(v11, &v10, &v11, NULL);
	NEG_CHECK(v11, &v11, &v10, NULL);
	NEG_CHECK(v12, &v11, &v12, NULL);
	NEG_CHECK(v12, &v12, &v11, NULL);
	NEG_CHECK(v13, &v12, &v13, NULL);
	NEG_CHECK(v13, &v13, &v12, NULL);

	NEG_CHECK(v6, &v1, &v2, &v3, &v4, &v5, &v6, NULL);
	NEG_CHECK(v6, &v1, &v2, &v3, &v4, &v6, &v5, NULL);
	NEG_CHECK(v6, &v1, &v2, &v3, &v6, &v4, &v5, NULL);
	NEG_CHECK(v6, &v1, &v2, &v6, &v3, &v4, &v5, NULL);
	NEG_CHECK(v6, &v1, &v6, &v2, &v3, &v4, &v5, NULL);
	NEG_CHECK(v6, &v6, &v1, &v2, &v3, &v4, &v5, NULL);

	NEG_CHECK(v6, &v6, &v5, &v4, &v3, &v2, &v1, NULL);
	NEG_CHECK(v6, &v5, &v6, &v4, &v3, &v2, &v1, NULL);
	NEG_CHECK(v6, &v5, &v4, &v6, &v3, &v2, &v1, NULL);
	NEG_CHECK(v6, &v5, &v4, &v3, &v6, &v2, &v1, NULL);
	NEG_CHECK(v6, &v5, &v4, &v3, &v2, &v6, &v1, NULL);
	NEG_CHECK(v6, &v5, &v4, &v3, &v2, &v1, &v6, NULL);

	NEG_CHECK(v13, &v1, &v6, &v9, &v11, &v12, &v4, &v8, &v2, &v3, &v10, &v7, &v5, &v13, NULL);
	NEG_CHECK(v13, &v12, &v2, &v11, &v13, &v7, &v4, &v9, &v10, &v1, &v6, &v3, &v8, &v5, NULL);
	NEG_CHECK(v13, &v5, &v13, &v6, &v12, &v8, &v10, &v3, &v9, &v7, &v2, &v11, &v1, &v4, NULL);
	NEG_CHECK(v13, &v4, &v13, &v10, &v11, &v5, &v12, &v9, &v3, &v7, &v6, &v1, &v8, &v2, NULL);
	NEG_CHECK(v13, &v5, &v7, &v6, &v3, &v2, &v1, &v11, &v12, &v8, &v4, &v9, &v13, &v10, NULL);
	NEG_CHECK(v13, &v3, &v8, &v7, &v10, &v1, &v11, &v13, &v12, &v5, &v4, &v2, &v6, &v9, NULL);
	NEG_CHECK(v13, &v11, &v2, &v8, &v3, &v5, &v12, &v4, &v13, &v1, &v10, &v7, &v6, &v9, NULL);
	NEG_CHECK(v13, &v8, &v6, &v2, &v10, &v9, &v13, &v12, &v4, &v7, &v1, &v11, &v5, &v3, NULL);
	NEG_CHECK(v13, &v4, &v8, &v7, &v12, &v13, &v1, &v6, &v11, &v2, &v3, &v10, &v9, &v5, NULL);
	NEG_CHECK(v13, &v13, &v11, &v1, &v4, &v8, &v10, &v12, &v5, &v3, &v2, &v9, &v7, &v6, NULL);
	NEG_CHECK(v13, &v13, &v3, &v12, &v8, &v10, &v11, &v7, &v2, &v4, &v1, &v9, &v6, &v5, NULL);
	NEG_CHECK(v13, &v9, &v8, &v13, &v7, &v1, &v5, &v6, &v11, &v12, &v4, &v3, &v2, &v10, NULL);
	NEG_CHECK(v13, &v9, &v8, &v10, &v6, &v3, &v1, &v12, &v2, &v5, &v11, &v4, &v7, &v13, NULL);
	NEG_CHECK(v13, &v5, &v4, &v12, &v13, &v8, &v7, &v9, &v1, &v6, &v10, &v3, &v2, &v11, NULL);
	NEG_CHECK(v13, &v5, &v4, &v11, &v9, &v8, &v7, &v10, &v6, &v2, &v3, &v1, &v13, &v12, NULL);
	NEG_CHECK(v13, &v12, &v1, &v13, &v10, &v7, &v6, &v5, &v2, &v11, &v4, &v3, &v8, &v9, NULL);
	NEG_CHECK(v13, &v2, &v1, &v8, &v7, &v13, &v5, &v9, &v10, &v6, &v3, &v11, &v12, &v4, NULL);
	NEG_CHECK(v13, &v3, &v7, &v13, &v9, &v6, &v8, &v5, &v12, &v4, &v11, &v2, &v10, &v1, NULL);
	NEG_CHECK(v13, &v12, &v3, &v6, &v5, &v2, &v9, &v4, &v11, &v8, &v10, &v13, &v1, &v7, NULL);
	NEG_CHECK(v13, &v1, &v13, &v7, &v4, &v3, &v12, &v2, &v9, &v5, &v10, &v11, &v6, &v8, NULL);
	NEG_CHECK(v13, &v7, &v3, &v8, &v1, &v2, &v4, &v13, &v5, &v6, &v10, &v9, &v11, &v12, NULL);
	NEG_CHECK(v13, &v2, &v3, &v13, &v8, &v12, &v5, &v11, &v1, &v9, &v10, &v4, &v7, &v6, NULL);
	NEG_CHECK(v13, &v10, &v6, &v7, &v5, &v11, &v9, &v1, &v3, &v13, &v4, &v2, &v8, &v12, NULL);
	NEG_CHECK(v13, &v6, &v9, &v12, &v7, &v2, &v1, &v10, &v4, &v13, &v11, &v3, &v5, &v8, NULL);
	NEG_CHECK(v13, &v5, &v1, &v9, &v6, &v4, &v8, &v7, &v11, &v13, &v3, &v2, &v12, &v10, NULL);
	NEG_CHECK(v13, &v1, &v10, &v11, &v2, &v9, &v12, &v7, &v5, &v3, &v8, &v13, &v6, &v4, NULL);
	NEG_CHECK(v13, &v3, &v10, &v2, &v4, &v8, &v9, &v11, &v7, &v5, &v1, &v13, &v6, &v12, NULL);
	NEG_CHECK(v13, &v8, &v10, &v11, &v6, &v5, &v2, &v9, &v4, &v3, &v13, &v7, &v12, &v1, NULL);
	NEG_CHECK(v13, &v4, &v12, &v11, &v7, &v3, &v13, &v10, &v2, &v5, &v9, &v1, &v6, &v8, NULL);
	NEG_CHECK(v13, &v7, &v13, &v12, &v3, &v4, &v8, &v11, &v9, &v1, &v10, &v6, &v2, &v5, NULL);
	NEG_CHECK(v13, &v5, &v4, &v2, &v1, &v8, &v7, &v13, &v10, &v11, &v3, &v9, &v6, &v12, NULL);
	NEG_CHECK(v13, &v7, &v8, &v10, &v2, &v4, &v1, &v11, &v9, &v12, &v6, &v13, &v5, &v3, NULL);
	NEG_CHECK(v13, &v3, &v7, &v2, &v13, &v5, &v10, &v12, &v6, &v8, &v1, &v11, &v9, &v4, NULL);
	NEG_CHECK(v13, &v12, &v13, &v6, &v9, &v4, &v11, &v8, &v3, &v2, &v1, &v7, &v10, &v5, NULL);
	NEG_CHECK(v13, &v2, &v9, &v10, &v13, &v1, &v3, &v5, &v8, &v7, &v6, &v11, &v4, &v12, NULL);
	NEG_CHECK(v13, &v7, &v5, &v10, &v11, &v3, &v12, &v4, &v9, &v6, &v13, &v1, &v2, &v8, NULL);
	NEG_CHECK(v13, &v1, &v3, &v4, &v8, &v2, &v13, &v11, &v7, &v10, &v5, &v6, &v12, &v9, NULL);
	NEG_CHECK(v13, &v7, &v2, &v1, &v13, &v5, &v10, &v3, &v9, &v6, &v4, &v11, &v8, &v12, NULL);
	NEG_CHECK(v13, &v6, &v5, &v3, &v11, &v8, &v9, &v1, &v12, &v7, &v13, &v4, &v10, &v2, NULL);
	NEG_CHECK(v13, &v13, &v6, &v5, &v4, &v3, &v8, &v1, &v2, &v7, &v9, &v10, &v11, &v12, NULL);
	NEG_CHECK(v13, &v13, &v12, &v4, &v3, &v11, &v6, &v1, &v7, &v10, &v2, &v5, &v9, &v8, NULL);
	NEG_CHECK(v13, &v13, &v6, &v7, &v2, &v8, &v4, &v1, &v5, &v12, &v11, &v3, &v10, &v9, NULL);
	NEG_CHECK(v13, &v13, &v5, &v12, &v11, &v10, &v9, &v2, &v6, &v4, &v8, &v3, &v1, &v7, NULL);
	NEG_CHECK(v13, &v1, &v8, &v7, &v6, &v13, &v9, &v3, &v11, &v10, &v4, &v2, &v12, &v5, NULL);
	NEG_CHECK(v13, &v8, &v9, &v3, &v7, &v1, &v11, &v2, &v13, &v4, &v6, &v12, &v10, &v5, NULL);
	NEG_CHECK(v13, &v4, &v5, &v13, &v2, &v7, &v8, &v9, &v10, &v11, &v1, &v3, &v6, &v12, NULL);
	NEG_CHECK(v13, &v7, &v4, &v11, &v9, &v6, &v12, &v3, &v5, &v10, &v8, &v1, &v2, &v13, NULL);
	NEG_CHECK(v13, &v8, &v9, &v6, &v2, &v11, &v5, &v13, &v1, &v3, &v7, &v10, &v12, &v4, NULL);
	NEG_CHECK(v13, &v10, &v4, &v5, &v6, &v3, &v7, &v13, &v8, &v12, &v2, &v9, &v1, &v11, NULL);
	NEG_CHECK(v13, &v9, &v1, &v3, &v8, &v12, &v5, &v6, &v2, &v10, &v11, &v4, &v7, &v13, NULL);

	for (i = 1U; i < (1U << 5); i++)
		check_mixed((i & 1U) ? &v1 : NULL,
		            (i & 2U) ? &v2 : NULL,
		            (i & 4U) ? &v3 : NULL,
		            (i & 8U) ? &v4 : NULL,
		            (i & 16U) ? &v5 : NULL);

	return 0;
}

#endif
