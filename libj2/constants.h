/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Check whether an unsigned double-max precision integer has
 * the value 0 (or equivalently, a non-positive value)
 * 
 * `libj2_j2u_is_zero(a)` implements `*a == 0`
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has the value 0, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_is_zero(const struct libj2_j2u *a)
{
	return !a->high && !a->low;
}


/**
 * Assign the value 0 to an unsigned double-max
 * precision integer
 * 
 * `libj2_j2u_zero(res)` implements `(void)(*res = 0)`
 * 
 * @param  res  The integer to assign the value 0 to
 * 
 * @since  1.0
 */
inline void
libj2_j2u_zero(struct libj2_j2u *res)
{
	res->high = res->low = 0;
}


/**
 * Check whether an unsigned double-max precision
 * integer has the highest representable value
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has highest representable value, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_is_max(const struct libj2_j2u *a)
{
	return a->high == UINTMAX_MAX && a->low == UINTMAX_MAX;
}


/**
 * Assign the highest representable value to an
 * unsigned double-max precision integer
 * 
 * @param  res  The integer to assign the value to
 * 
 * @since  1.0
 */
inline void
libj2_j2u_max(struct libj2_j2u *res)
{
	res->high = res->low = UINTMAX_MAX;
}


/**
 * Check whether an unsigned double-max precision
 * integer has the lowest representable value
 * 
 * Since the integer type is unsigned, this function
 * does the same thing as `libj2_j2u_is_zero(a)`
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has lowest representable value, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_is_min(const struct libj2_j2u *a)
{
	return libj2_j2u_is_zero(a);
}


/**
 * Assign the lowest representable value to an
 * unsigned double-max precision integer
 * 
 * Since the integer type is unsigned, this function
 * does the same thing as `libj2_j2u_zero(res)`
 * 
 * @param  res  The integer to assign the value to
 * 
 * @since  1.0
 */
inline void
libj2_j2u_min(struct libj2_j2u *res)
{
	libj2_j2u_zero(res);
}





/**
 * Check whether a signed double-max precision integer has
 * the value 0 (or equivalently, a non-positive value)
 * 
 * `libj2_j2i_is_zero(a)` implements `*a == 0`
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has the value 0, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_is_zero(const struct libj2_j2i *a)
{
	return !a->high && !a->low;
}


/**
 * Assign the value 0 to a signed double-max
 * precision integer
 * 
 * `libj2_j2i_zero(res)` implements `(void)(*res = 0)`
 * 
 * @param  res  The integer to assign the value 0 to
 * 
 * @since  1.1
 */
inline void
libj2_j2i_zero(struct libj2_j2i *res)
{
	res->high = res->low = 0;
}


/**
 * Check whether a signed double-max precision
 * integer has the highest representable value
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has highest representable value, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_is_max(const struct libj2_j2i *a)
{
	return a->high == UINTMAX_MAX >> 1 && a->low == UINTMAX_MAX;
}


/**
 * Assign the highest representable value to a signed
 * double-max precision integer
 * 
 * @param  res  The integer to assign the value to
 * 
 * @since  1.1
 */
inline void
libj2_j2i_max(struct libj2_j2i *res)
{
	res->high = UINTMAX_MAX >> 1;
	res->low = UINTMAX_MAX;
}


/**
 * Check whether a signed double-max precision
 * integer has the lowest representable value
 * 
 * @param   a  The integer to inspect
 * @return     1 if `a` has lowest representable value, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_is_min(const struct libj2_j2i *a)
{
	return a->high == ~(UINTMAX_MAX >> 1) && !a->low;
}


/**
 * Assign the lowest representable value to an nsigned
 * double-max precision integer
 * 
 * @param  res  The integer to assign the value to
 * 
 * @since  1.1
 */
inline void
libj2_j2i_min(struct libj2_j2i *res)
{
	res->high = ~(UINTMAX_MAX >> 1);
	res->low = 0;
}
