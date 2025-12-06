/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Check whether an unsigned double-max precision integer has a
 * positive value (or equivalently, a non-zero value)
 * 
 * `libj2_j2u_is_positive(a)` implements `*a > 0`
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has a positive value, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_is_positive(const struct libj2_j2u *a)
{
	return a->high || a->low;
}


/**
 * Get the sign (signum function) of an unsigned double-max
 * precision integer
 * 
 * `libj2_sgn_j2u(a)` implements `*a < 0 ? -1 : *a > 0 ? +1 : 0`,
 * or equaivalently, since `a` is unsigned, `*a > 0 ? +1 : 0`
 * 
 * Since the integer type is unsigned, this function
 * does the same thing as `libj2_j2u_is_positive(res)`
 * 
 * @param   a  The integer to inspect
 * @return     -1 if `a` is negative (impossible),
 *             +1 if `a` is positive, and
 *             0 if `a` is 0
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_sgn_j2u(const struct libj2_j2u *a)
{
	return libj2_j2u_is_positive(a);
}


/* libj2_j2u_is_zero is located in constants.h */
