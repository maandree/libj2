/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
#define LIBJ2_H

#include <limits.h>
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
 * The number of bits in an `uintmax_t`
 */
#define LIBJ2_JU_BIT ((unsigned)CHAR_BIT * (unsigned)sizeof(uintmax_t))

/**
 * The number of bits in an `struct libj2_j2u`
 */
#define LIBJ2_J2U_BIT (2U * LIBJ2_JU_BIT)


/**
 * Unsigned double-maximum precision integer
 * 
 * If `uintmax_t` is a 64-bit type, this `struct` is a 128-bit type
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


#include "libj2/constants.h"
#include "libj2/signum.h"
#include "libj2/constructors.h"
#include "libj2/unsigned-comparsion.h"
#include "libj2/bitwise-logic.h"
#include "libj2/bit-shifting.h"
#include "libj2/bit-scanning.h"
#include "libj2/sign-shifting.h"
#include "libj2/addition.h"
#include "libj2/subtraction.h"
#include "libj2/multiplication.h"
#include "libj2/division.h"


#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
# undef LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_
#endif
#undef LIBJ2_PURE_

#endif
