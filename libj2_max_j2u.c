/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

extern inline void libj2_max_j2u(struct libj2_j2u *a, ... /*, NULL */);
/* TODO Add man page */


#else

static struct libj2_j2u v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13;


static void
reset(void)
{
	const uintmax_t max = UINTMAX_MAX;
	v1 = (struct libj2_j2u){0, 0};
	v2 = (struct libj2_j2u){0, 1};
	v3 = (struct libj2_j2u){0, 2};
	v4 = (struct libj2_j2u){0, max - 1U};
	v5 = (struct libj2_j2u){1, 0};
	v6 = (struct libj2_j2u){1, 1};
	v7 = (struct libj2_j2u){max - 1U, 0};
	v8 = (struct libj2_j2u){max - 1U, 1};
	v9 = (struct libj2_j2u){max - 1U, max};
	v10 = (struct libj2_j2u){max, 0};
	v11 = (struct libj2_j2u){max, 1};
	v12 = (struct libj2_j2u){max, max - 1U};
	v13 = (struct libj2_j2u){max, max};
}


static void
expect_untouched(void)
{
	const uintmax_t max = UINTMAX_MAX;
	EXPECT(libj2_j2u_eq_j2u(&v1, &(struct libj2_j2u){0, 0}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v2, &(struct libj2_j2u){0, 1}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v3, &(struct libj2_j2u){0, 2}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v4, &(struct libj2_j2u){0, max - 1U}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v5, &(struct libj2_j2u){1, 0}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v6, &(struct libj2_j2u){1, 1}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v7, &(struct libj2_j2u){max - 1U, 0}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v8, &(struct libj2_j2u){max - 1U, 1}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v9, &(struct libj2_j2u){max - 1U, max}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v10, &(struct libj2_j2u){max, 0}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v11, &(struct libj2_j2u){max, 1}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v12, &(struct libj2_j2u){max, max - 1U}) == 1);
	EXPECT(libj2_j2u_eq_j2u(&v13, &(struct libj2_j2u){max, max}) == 1);
}


#define HEAD(X, ...) X
#define TAIL(X, ...) __VA_ARGS__

#define CHECK(MAX, ...)\
	do {\
		reset();\
		\
		r = *(HEAD(__VA_ARGS__));\
		libj2_max_j2u(&r, TAIL(__VA_ARGS__));\
		expect_untouched();\
		EXPECT(libj2_j2u_eq_j2u(&(MAX), &r));\
		\
		p = libj2_max_j2u_return(__VA_ARGS__);\
		expect_untouched();\
		EXPECT(p != NULL);\
		EXPECT(libj2_j2u_eq_j2u(&(MAX), p));\
		\
		r = (struct libj2_j2u){111, 222};\
		libj2_max_j2u_to_j2u(__VA_ARGS__, &r);\
		expect_untouched();\
		EXPECT(libj2_j2u_eq_j2u(&(MAX), &r));\
	} while (0)


int
main(void)
{
	struct libj2_j2u r;
	const struct libj2_j2u *p;

	CHECK(v1, &v1, NULL);
	CHECK(v2, &v2, NULL);
	CHECK(v3, &v3, NULL);

	CHECK(v2, &v1, &v2, NULL);
	CHECK(v2, &v2, &v1, NULL);
	CHECK(v3, &v2, &v3, NULL);
	CHECK(v3, &v3, &v2, NULL);
	CHECK(v4, &v3, &v4, NULL);
	CHECK(v4, &v4, &v3, NULL);
	CHECK(v5, &v4, &v5, NULL);
	CHECK(v5, &v5, &v4, NULL);
	CHECK(v6, &v5, &v6, NULL);
	CHECK(v6, &v6, &v5, NULL);
	CHECK(v7, &v6, &v7, NULL);
	CHECK(v7, &v7, &v6, NULL);
	CHECK(v8, &v7, &v8, NULL);
	CHECK(v8, &v8, &v7, NULL);
	CHECK(v9, &v8, &v9, NULL);
	CHECK(v9, &v9, &v8, NULL);
	CHECK(v10, &v9, &v10, NULL);
	CHECK(v10, &v10, &v9, NULL);
	CHECK(v11, &v10, &v11, NULL);
	CHECK(v11, &v11, &v10, NULL);
	CHECK(v12, &v11, &v12, NULL);
	CHECK(v12, &v12, &v11, NULL);
	CHECK(v13, &v12, &v13, NULL);
	CHECK(v13, &v13, &v12, NULL);

	CHECK(v6, &v1, &v2, &v3, &v4, &v5, &v6, NULL);
	CHECK(v6, &v1, &v2, &v3, &v4, &v6, &v5, NULL);
	CHECK(v6, &v1, &v2, &v3, &v6, &v4, &v5, NULL);
	CHECK(v6, &v1, &v2, &v6, &v3, &v4, &v5, NULL);
	CHECK(v6, &v1, &v6, &v2, &v3, &v4, &v5, NULL);
	CHECK(v6, &v6, &v1, &v2, &v3, &v4, &v5, NULL);

	CHECK(v6, &v6, &v5, &v4, &v3, &v2, &v1, NULL);
	CHECK(v6, &v5, &v6, &v4, &v3, &v2, &v1, NULL);
	CHECK(v6, &v5, &v4, &v6, &v3, &v2, &v1, NULL);
	CHECK(v6, &v5, &v4, &v3, &v6, &v2, &v1, NULL);
	CHECK(v6, &v5, &v4, &v3, &v2, &v6, &v1, NULL);
	CHECK(v6, &v5, &v4, &v3, &v2, &v1, &v6, NULL);

	CHECK(v13, &v1, &v6, &v9, &v11, &v12, &v4, &v8, &v2, &v3, &v10, &v7, &v5, &v13, NULL);
	CHECK(v13, &v12, &v2, &v11, &v13, &v7, &v4, &v9, &v10, &v1, &v6, &v3, &v8, &v5, NULL);
	CHECK(v13, &v5, &v13, &v6, &v12, &v8, &v10, &v3, &v9, &v7, &v2, &v11, &v1, &v4, NULL);
	CHECK(v13, &v4, &v13, &v10, &v11, &v5, &v12, &v9, &v3, &v7, &v6, &v1, &v8, &v2, NULL);
	CHECK(v13, &v5, &v7, &v6, &v3, &v2, &v1, &v11, &v12, &v8, &v4, &v9, &v13, &v10, NULL);
	CHECK(v13, &v3, &v8, &v7, &v10, &v1, &v11, &v13, &v12, &v5, &v4, &v2, &v6, &v9, NULL);
	CHECK(v13, &v11, &v2, &v8, &v3, &v5, &v12, &v4, &v13, &v1, &v10, &v7, &v6, &v9, NULL);
	CHECK(v13, &v8, &v6, &v2, &v10, &v9, &v13, &v12, &v4, &v7, &v1, &v11, &v5, &v3, NULL);
	CHECK(v13, &v4, &v8, &v7, &v12, &v13, &v1, &v6, &v11, &v2, &v3, &v10, &v9, &v5, NULL);
	CHECK(v13, &v13, &v11, &v1, &v4, &v8, &v10, &v12, &v5, &v3, &v2, &v9, &v7, &v6, NULL);
	CHECK(v13, &v13, &v3, &v12, &v8, &v10, &v11, &v7, &v2, &v4, &v1, &v9, &v6, &v5, NULL);
	CHECK(v13, &v9, &v8, &v13, &v7, &v1, &v5, &v6, &v11, &v12, &v4, &v3, &v2, &v10, NULL);
	CHECK(v13, &v9, &v8, &v10, &v6, &v3, &v1, &v12, &v2, &v5, &v11, &v4, &v7, &v13, NULL);
	CHECK(v13, &v5, &v4, &v12, &v13, &v8, &v7, &v9, &v1, &v6, &v10, &v3, &v2, &v11, NULL);
	CHECK(v13, &v5, &v4, &v11, &v9, &v8, &v7, &v10, &v6, &v2, &v3, &v1, &v13, &v12, NULL);
	CHECK(v13, &v12, &v1, &v13, &v10, &v7, &v6, &v5, &v2, &v11, &v4, &v3, &v8, &v9, NULL);
	CHECK(v13, &v2, &v1, &v8, &v7, &v13, &v5, &v9, &v10, &v6, &v3, &v11, &v12, &v4, NULL);
	CHECK(v13, &v3, &v7, &v13, &v9, &v6, &v8, &v5, &v12, &v4, &v11, &v2, &v10, &v1, NULL);
	CHECK(v13, &v12, &v3, &v6, &v5, &v2, &v9, &v4, &v11, &v8, &v10, &v13, &v1, &v7, NULL);
	CHECK(v13, &v1, &v13, &v7, &v4, &v3, &v12, &v2, &v9, &v5, &v10, &v11, &v6, &v8, NULL);
	CHECK(v13, &v7, &v3, &v8, &v1, &v2, &v4, &v13, &v5, &v6, &v10, &v9, &v11, &v12, NULL);
	CHECK(v13, &v2, &v3, &v13, &v8, &v12, &v5, &v11, &v1, &v9, &v10, &v4, &v7, &v6, NULL);
	CHECK(v13, &v10, &v6, &v7, &v5, &v11, &v9, &v1, &v3, &v13, &v4, &v2, &v8, &v12, NULL);
	CHECK(v13, &v6, &v9, &v12, &v7, &v2, &v1, &v10, &v4, &v13, &v11, &v3, &v5, &v8, NULL);
	CHECK(v13, &v5, &v1, &v9, &v6, &v4, &v8, &v7, &v11, &v13, &v3, &v2, &v12, &v10, NULL);
	CHECK(v13, &v1, &v10, &v11, &v2, &v9, &v12, &v7, &v5, &v3, &v8, &v13, &v6, &v4, NULL);
	CHECK(v13, &v3, &v10, &v2, &v4, &v8, &v9, &v11, &v7, &v5, &v1, &v13, &v6, &v12, NULL);
	CHECK(v13, &v8, &v10, &v11, &v6, &v5, &v2, &v9, &v4, &v3, &v13, &v7, &v12, &v1, NULL);
	CHECK(v13, &v4, &v12, &v11, &v7, &v3, &v13, &v10, &v2, &v5, &v9, &v1, &v6, &v8, NULL);
	CHECK(v13, &v7, &v13, &v12, &v3, &v4, &v8, &v11, &v9, &v1, &v10, &v6, &v2, &v5, NULL);
	CHECK(v13, &v5, &v4, &v2, &v1, &v8, &v7, &v13, &v10, &v11, &v3, &v9, &v6, &v12, NULL);
	CHECK(v13, &v7, &v8, &v10, &v2, &v4, &v1, &v11, &v9, &v12, &v6, &v13, &v5, &v3, NULL);
	CHECK(v13, &v3, &v7, &v2, &v13, &v5, &v10, &v12, &v6, &v8, &v1, &v11, &v9, &v4, NULL);
	CHECK(v13, &v12, &v13, &v6, &v9, &v4, &v11, &v8, &v3, &v2, &v1, &v7, &v10, &v5, NULL);
	CHECK(v13, &v2, &v9, &v10, &v13, &v1, &v3, &v5, &v8, &v7, &v6, &v11, &v4, &v12, NULL);
	CHECK(v13, &v7, &v5, &v10, &v11, &v3, &v12, &v4, &v9, &v6, &v13, &v1, &v2, &v8, NULL);
	CHECK(v13, &v1, &v3, &v4, &v8, &v2, &v13, &v11, &v7, &v10, &v5, &v6, &v12, &v9, NULL);
	CHECK(v13, &v7, &v2, &v1, &v13, &v5, &v10, &v3, &v9, &v6, &v4, &v11, &v8, &v12, NULL);
	CHECK(v13, &v6, &v5, &v3, &v11, &v8, &v9, &v1, &v12, &v7, &v13, &v4, &v10, &v2, NULL);
	CHECK(v13, &v13, &v6, &v5, &v4, &v3, &v8, &v1, &v2, &v7, &v9, &v10, &v11, &v12, NULL);
	CHECK(v13, &v13, &v12, &v4, &v3, &v11, &v6, &v1, &v7, &v10, &v2, &v5, &v9, &v8, NULL);
	CHECK(v13, &v13, &v6, &v7, &v2, &v8, &v4, &v1, &v5, &v12, &v11, &v3, &v10, &v9, NULL);
	CHECK(v13, &v13, &v5, &v12, &v11, &v10, &v9, &v2, &v6, &v4, &v8, &v3, &v1, &v7, NULL);
	CHECK(v13, &v1, &v8, &v7, &v6, &v13, &v9, &v3, &v11, &v10, &v4, &v2, &v12, &v5, NULL);
	CHECK(v13, &v8, &v9, &v3, &v7, &v1, &v11, &v2, &v13, &v4, &v6, &v12, &v10, &v5, NULL);
	CHECK(v13, &v4, &v5, &v13, &v2, &v7, &v8, &v9, &v10, &v11, &v1, &v3, &v6, &v12, NULL);
	CHECK(v13, &v7, &v4, &v11, &v9, &v6, &v12, &v3, &v5, &v10, &v8, &v1, &v2, &v13, NULL);
	CHECK(v13, &v8, &v9, &v6, &v2, &v11, &v5, &v13, &v1, &v3, &v7, &v10, &v12, &v4, NULL);
	CHECK(v13, &v10, &v4, &v5, &v6, &v3, &v7, &v13, &v8, &v12, &v2, &v9, &v1, &v11, NULL);
	CHECK(v13, &v9, &v1, &v3, &v8, &v12, &v5, &v6, &v2, &v10, &v11, &v4, &v7, &v13, NULL);

	return 0;
}

#endif
