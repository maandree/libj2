/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Cast an unsigned max precision integer to an
 * unsigned double-max precision integer
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


/**
 * Cast an unsigned max precision integer to a signed
 * double-max precision integer
 * 
 * `libj2_ju_to_j2i(a, res)` implements `*res = a`
 * 
 * @param  a    The value to assign to `*res`
 * @param  res  The integer to assign the value `a` to
 * 
 * @since  1.1
 */
inline void
libj2_ju_to_j2i(uintmax_t a, struct libj2_j2i *res)
{
	res->high = 0;
	res->low = a;
}


/**
 * Cast a signed max precision integer to a signed
 * double-max precision integer
 * 
 * `libj2_ji_to_j2i(a, res)` implements `*res = a`
 * 
 * @param  a    The value to assign to `*res`
 * @param  res  The integer to assign the value `a` to
 * 
 * @since  1.1
 */
inline void
libj2_ji_to_j2i(intmax_t a, struct libj2_j2i *res)
{
	if (a >= 0) {
		res->high = 0;
		res->low = (uintmax_t)a;
	} else {
		res->high = UINTMAX_MAX;
		res->low = ~(uintmax_t)-(a + 1);
	}
}


/**
 * Cast an unsigned double-max precision integer
 * to a signed double-max precision integer
 * 
 * `libj2_j2i_to_j2u(a, res)` implements `*res = a`
 * 
 * Overflows if `libj2_j2u_test_bit(a, LIBJ2_J2U_BIT - 1U)`
 * 
 * @param  a    The value to assign to `*res`
 * @param  res  The integer to assign the value `a` to
 * 
 * @since  1.1
 */
inline void
libj2_j2u_to_j2i(const struct libj2_j2u *a, struct libj2_j2i *res)
{
	res->high = a->high;
	res->low = a->low;
}


/**
 * Cast a signed double-max precision integer to
 * an unsigned double-max precision integer
 * 
 * `libj2_j2i_to_j2u(a, res)` implements `*res = a`
 * 
 * Overflows if `libj2_j2i_is_negative(a)`
 * 
 * @param  a    The value to assign to `*res`
 * @param  res  The integer to assign the value `a` to
 * 
 * @since  1.1
 */
inline void
libj2_j2i_to_j2u(const struct libj2_j2i *a, struct libj2_j2u *res)
{
	res->high = a->high;
	res->low = a->low;
}


/* libj2_j2u_zero, libj2_j2u_max, libj2_j2u_min, libj2_j2i_zero,
 * libj2_j2i_max, and libj2_j2i_min are located in constants.h */
