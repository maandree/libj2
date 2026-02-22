/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
#define LIBJ2_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#if 1
# if defined(__GNUC__)
#  define LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_
#   if !defined(__clang__)
#    define LIBJ2_USE_GCC_PARITYG_
#   endif
# endif
#endif


#if defined(__GNUC__)
# define LIBJ2_PURE_ __attribute__((__pure__))
#else
# define LIBJ2_PURE_
#endif


/**
 * The number of bits in a `uintmax_t`
 * 
 * @since  1.0
 */
#define LIBJ2_JU_BIT ((unsigned)CHAR_BIT * (unsigned)sizeof(uintmax_t))

/**
 * The number of bits in a `struct libj2_j2u`
 * 
 * @since  1.0
 */
#define LIBJ2_J2U_BIT (2U * LIBJ2_JU_BIT)

/**
 * The number of bits in a `struct libj2_j2i`,
 * including the sign bit
 * 
 * @since  1.1
 */
#define LIBJ2_J2I_BIT LIBJ2_J2U_BIT

/**
 * The number of value bits in a `struct libj2_j2i`,
 * that is, the number of bits excluding the sign
 * bit
 * 
 * @since  1.1
 */
#define LIBJ2_J2I_VBIT (LIBJ2_J2I_BIT - 1U)


/**
 * Unsigned double-maximum precision integer
 * 
 * If `uintmax_t` is a 64-bit type, this `struct` is a 128-bit type
 * 
 * @since  1.0
 */
struct libj2_j2u {
	/**
	 * Most significant half
	 */
	uintmax_t high;

	/**
	 * Least significant half
	 */
	uintmax_t low;
};


/**
 * Signed double-maximum precision integer,
 * using two's complement
 * 
 * libj2 does not implement bitwise operations,
 * bit-scanning, or bit-rotation operations
 * for this type, but a `struct libj2_j2i *`
 * can safely be cast to `struct libj2_j2u *`
 * for such operators as well as the for
 * unsigned bit shifting operations
 * 
 * If `a` is the maximum representable value,
 * `-a - 1` is the minimum representable value;
 * there is only one zero value (has no sign)
 * 
 * @since  1.1
 */
struct libj2_j2i {
	/**
	 * Most significant half, of which the most
	 * significant bit is the sign bit
	 */
	uintmax_t high;

	/**
	 * Least significant half
	 */
	uintmax_t low;
};


/**
 * Arithmetic overflow prediction result
 * 
 * Used by some functions for which prediction
 * is costly in edge cases, and thus stopped
 * as soon as such an edge case is detected
 * 
 * @since  1.0  LIBJ2_NO_OVERFLOW, LIBJ2_OVERFLOW, LIBJ2_OVERFLOW_UNKNOWN
 * @since  1.1  LIBJ2_POSITIVE_OVERFLOW, LIBJ2_POSITIVE_OVERFLOW_UNKNOWN,
 *              LIBJ2_NEGATIVE_OVERFLOW, LIBJ2_NEGATIVE_OVERFLOW_UNKNOWN
 */
enum libj2_overflow {
	/**
	 * There will be no overflow
	 */
	LIBJ2_NO_OVERFLOW = 0,

	/**
	 * There will be a positive overflow
	 */
	LIBJ2_POSITIVE_OVERFLOW = 1,
#define LIBJ2_OVERFLOW LIBJ2_POSITIVE_OVERFLOW

	/**
	 * Overflow prediction stopped
	 * (due to high cost);
	 * result is positive
	 */
	LIBJ2_POSITIVE_OVERFLOW_UNKNOWN = 2,
#define LIBJ2_OVERFLOW_UNKNOWN LIBJ2_POSITIVE_OVERFLOW_UNKNOWN

	/**
	 * There will be a negative overflow
	 */
	LIBJ2_NEGATIVE_OVERFLOW = -1,

	/**
	 * Overflow prediction stopped
	 * (due to high cost);
	 * result is positive
	 */
	LIBJ2_NEGATIVE_OVERFLOW_UNKNOWN = -2
};


#include "libj2/constants.h"
#include "libj2/signum.h"
#include "libj2/constructors.h"
#include "libj2/unsigned-comparison.h"
#include "libj2/signed-comparison.h"
#include "libj2/mixed-comparison.h"
#include "libj2/bitwise-logic.h"
#include "libj2/sign-shifting.h"
#include "libj2/bit-shifting.h"
#include "libj2/bit-scanning.h"
#include "libj2/addition.h"
#include "libj2/subtraction.h"
#include "libj2/multiplication.h"
#include "libj2/division.h"
#include "libj2/saturated-math.h"
#include "libj2/strings.h"


#if !defined(LIBJ2_COMPILING_)
# if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
#  undef LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_
# endif
# if defined(LIBJ2_USE_GCC_PARITYG_)
#  undef LIBJ2_USE_GCC_PARITYG_
# endif
# undef LIBJ2_PURE_
#endif

#endif
