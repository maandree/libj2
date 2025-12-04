/* See LICENSE file for copyright and license details. */
#include "libj2.h"

#if defined(__GNUC__)
# define CONST __attribute__((__const__))
# define PURE __attribute__((__pure__))
#else
# define CONST
# define PURE
#endif

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunsafe-buffer-usage" /* broken warning, spams false positives */
# pragma clang diagnostic ignored "-Wimplicit-void-ptr-cast" /* C++-incompatiblity warning, bad idea, specially in non-header files */
#endif

#ifdef TEST
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
