/* See LICENSE file for copyright and license details. */
#define LIBJ2_COMPILING_
#include "libj2.h"

#define PURE LIBJ2_PURE_

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunsafe-buffer-usage" /* broken warning, spams false positives */
# pragma clang diagnostic ignored "-Wimplicit-void-ptr-cast" /* C++-incompatiblity warning, bad idea, specially in non-header files */
#endif

#ifdef TEST
# if defined(__GNUC__)
#  define CONST __attribute__((__const__))
# else
#  define CONST
# endif
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# define EXPECT(EXPR)\
	do {\
		if (EXPR)\
			break;\
		fprintf(stderr, "Assertion failed at %s:%i: %s\n", __FILE__, __LINE__, #EXPR);\
		exit(1);\
	} while (0)
#endif
