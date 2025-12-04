/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the additive inverse of an unsigned
 * double-max precision integer
 * 
 * `libj2_minus_j2u(a)` implements `*a = -*a`
 * 
 * @param  a  The integer to invert, also used as the
 *            output parameter for the inverse
 */
inline void
libj2_minus_j2u(struct libj2_j2u *a)
{
	a->high = -a->high;
	if (a->low) {
		a->high -= 1U;
		a->low = -a->low;
	}
}


/**
 * Calculate the additive inverse of an unsigned
 * double-max precision integer
 * 
 * `libj2_minus_j2u_j2u(a, res)` implements `*res = -*a`
 * 
 * @param  a    The integer to invert
 * @param  res  Output parameter for the inverse
 */
inline void
libj2_minus_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	res->high = -a->high;
	if (a->low)
		res->high -= 1U;
	res->low = -a->low;
}
