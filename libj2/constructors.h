/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Cast an unsigned max precision integer to an unsigned
 * double-max precision integer
 * 
 * `libj2_ju_to_j2u(a, res)` implements `*res = a`
 * 
 * @param  a    The value to assign to `*res`
 * @param  res  The integer to assign the value `a` to
 * 
 * @since  1.0
 */
inline void
libj2_ju_to_j2u(uintmax_t a, struct libj2_j2u *res)
{
	res->high = 0;
	res->low = a;
}


/* libj2_j2u_zero, libj2_j2u_max, libj2_j2u_min are located in constants.h */
