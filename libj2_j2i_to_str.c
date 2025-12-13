/* See LICENSE file for copyright and license details. */
#include "common.h"
#ifndef TEST

/* TODO Add man page */
extern inline size_t libj2_j2i_to_str(const struct libj2_j2i *a, char *buf, size_t bufsize, const char *digits);


#else

int main(void)
{
	/* Primarily tested in libj2_j2u_to_str.c */

	struct libj2_j2i a;

	libj2_j2i_zero(&a);
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "") == 0);
	EXPECT(libj2_j2i_is_zero(&a));
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "0") == 0);
	EXPECT(libj2_j2i_is_zero(&a));
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "01") == 1);
	EXPECT(libj2_j2i_is_zero(&a));
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "01234") == 1);
	EXPECT(libj2_j2i_is_zero(&a));
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "01234567") == 1);
	EXPECT(libj2_j2i_is_zero(&a));
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "0123456789") == 1);
	EXPECT(libj2_j2i_is_zero(&a));
	EXPECT(libj2_j2i_to_str(&a, NULL, SIZE_MAX, "00") == 0);
	EXPECT(libj2_j2i_is_zero(&a));

	return 0;
}

#endif
