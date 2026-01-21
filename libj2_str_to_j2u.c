/* See LICENSE file for copyright and license details. */
#include "common.h"
#include <errno.h>
#ifndef TEST

extern inline int libj2_str_to_j2u(const char *str, size_t slen, char **end, const char *digits1,
                                   const char *digits2, struct libj2_j2u *a);


#else

int
main(void)
{
	/* Primarily tested in libj2_j2u_to_str.c */

	char buf[sizeof(uintmax_t) * 8U];
	struct libj2_j2u a;
	char *end;

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", SIZE_MAX, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 6, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 5, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 4, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1000));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("10000", 4, &end, NULL, "0123456789", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(!strcmp(end, "10000"));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("-10000", 5, &end, NULL, NULL, &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(!strcmp(end, "-10000"));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 3, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 100));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 2, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 1, NULL, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1));

	a = (struct libj2_j2u){111, 222};
	EXPECT(libj2_str_to_j2u("10000", 0, NULL, NULL, NULL, &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" \r\n\v+\t\f + 10000", SIZE_MAX, &end, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" \r\n\v+\t\f + 10000 0", SIZE_MAX, &end, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));
	EXPECT(end);
	EXPECT(!strcmp(end, " 0"));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" \r\n\v+\t\f + 10000x0", SIZE_MAX, &end, NULL, NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 10000));
	EXPECT(end);
	EXPECT(!strcmp(end, "x0"));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" +-- ", SIZE_MAX, &end, "-+", NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 4));
	EXPECT(end);
	EXPECT(!strcmp(end, " "));

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(" +-- ", SIZE_MAX, &end, "- +", NULL, &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 136));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "Ab", "Ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 1));
	EXPECT(end);
	EXPECT(*end == 'a');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "Ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "AB", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "AB", "AB", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'b');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "AB", "ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "ab", "AB", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "AB", "AB", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "AB", "ab", &a) == 0);
	EXPECT(libj2_j2u_eq_ju(&a, 2));
	EXPECT(end);
	EXPECT(!*end);

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "ABB", "abb", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'B');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "AB", "abc", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'B');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("BA", SIZE_MAX, &end, "ABC", "ab", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'B');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "ba", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'b');

	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u("ba", SIZE_MAX, &end, "ab", "bc", &a) == EINVAL);
	EXPECT(libj2_j2u_is_zero(&a));
	EXPECT(end);
	EXPECT(*end == 'b');

	sprintf(buf, "%jx%jx", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdef", NULL, &a) == 0);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	sprintf(buf, "%jx%jx", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdefg", NULL, &a) == ERANGE);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	sprintf(buf, "%jx%jx0", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdef", NULL, &a) == ERANGE);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	sprintf(buf, "1%jx%jx", UINTMAX_MAX, UINTMAX_MAX);
	a = (struct libj2_j2u){111, 222};
	end = NULL;
	EXPECT(libj2_str_to_j2u(buf, SIZE_MAX, &end, "0123456789abcdef", NULL, &a) == ERANGE);
	EXPECT(libj2_j2u_is_max(&a));
	EXPECT(end);
	EXPECT(!*end);

	return 0;
}

#endif
