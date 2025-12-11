/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the additive inverse of an unsigned
 * double-max precision integer
 * 
 * `libj2_minus_j2u_to_j2u(a, res)` implements
 * `*res = -*a`
 * 
 * @param  a    The integer to invert
 * @param  res  Output parameter for the inverse
 * 
 * @since  1.0
 */
inline void
libj2_minus_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	res->high = -a->high;
	if (a->low)
		res->high -= 1U;
	res->low = -a->low;
}


/**
 * Calculate the additive inverse of an unsigned
 * double-max precision integer
 * 
 * `libj2_minus_j2u(a)` implements `*a = -*a`
 * 
 * @param  a  The integer to invert, also used as
 *            the output parameter for the inverse
 * 
 * @since  1.0
 */
inline void
libj2_minus_j2u(struct libj2_j2u *a)
{
	libj2_minus_j2u_to_j2u(a, a);
}


/**
 * Calculate the additive inverse of a signed
 * double-max precision integer
 * 
 * `libj2_minus_j2i_to_j2i(a, res)` implements
 * `*res = -*a`
 * 
 * Overflows if `libj2_j2i_is_min(a)`
 * 
 * @param  a    The integer to invert
 * @param  res  Output parameter for the inverse
 * 
 * @since  1.1
 */
inline void
libj2_minus_j2i_to_j2i(const struct libj2_j2i *a, struct libj2_j2i *res)
{
	libj2_minus_j2u_to_j2u((const void *)a, (void *)res);
}


/**
 * Calculate the additive inverse of a signed
 * double-max precision integer
 * 
 * `libj2_minus_j2i(a)` implements `*a = -*a`
 * 
 * Overflows if `libj2_j2i_is_min(a)`
 * 
 * @param  a  The integer to invert, also used as
 *            the output parameter for the inverse
 * 
 * @since  1.1
 */
inline void
libj2_minus_j2i(struct libj2_j2i *a)
{
	libj2_minus_j2u_to_j2u((const void *)a, (void *)a);
}


/**
 * Calculate the additive inverse of a signed
 * double-max precision integer and stored it as
 * an unsigned double-max precision integer
 * 
 * `libj2_minus_j2i_to_j2u(a, res)` implements
 * `*res = -*a`
 * 
 * Overflows if `libj2_j2i_is_min(a) || libj2_j2i_is_positive(a)`
 * 
 * @param  a    The integer to invert
 * @param  res  Output parameter for the inverse
 * 
 * @since  1.1
 */
inline void
libj2_minus_j2i_to_j2u(const struct libj2_j2i *a, struct libj2_j2u *res)
{
	libj2_minus_j2u_to_j2u((const void *)a, (void *)res);
}


/**
 * Calculate the additive inverse of an unsigned
 * double-max precision integer and stored it as
 * a signed double-max precision integer
 * 
 * `libj2_minus_j2u_to_j2i(a, res)` implements
 * `*res = -*a`
 * 
 * Overflows if `libj2_co_j2u(a) > 1U &&
 * libj2_j2u_test_bit(a, LIBJ2_J2U_BIT - 1U)`
 * 
 * @param  a    The integer to invert
 * @param  res  Output parameter for the inverse
 * 
 * @since  1.1
 */
inline void
libj2_minus_j2u_to_j2i(const struct libj2_j2u *a, struct libj2_j2i *res)
{
	libj2_minus_j2u_to_j2u((const void *)a, (void *)res);
}





/**
 * Calculate the absolute value of a signed
 * double-max precision integer
 * 
 * Overflows if `libj2_j2i_is_min(a)`
 * 
 * @param  a    The integer
 * @param  res  Output parameter for the absolute value
 * 
 * @since  1.1
 */
inline void
libj2_abs_j2i_to_j2i(const struct libj2_j2i *a, struct libj2_j2i *res)
{
	if (libj2_j2i_is_negative(a))
		libj2_minus_j2i_to_j2i(a, res);
	else if (a != res)
		*res = *a;
}


/**
 * Calculate the absolute value of a signed
 * double-max precision integer
 * 
 * Overflows if `libj2_j2i_is_min(a)`
 * 
 * @param  a  The integer, also used as the
 *            output parameter for the absolute value
 * 
 * @since  1.1
 */
inline void
libj2_abs_j2i(struct libj2_j2i *a)
{
	if (libj2_j2i_is_negative(a))
		libj2_minus_j2i(a);
}


/**
 * Calculate the absolute value of a signed
 * double-max precision integer and stored it as
 * an unsigned double-max precision integer
 * 
 * @param  a    The integer
 * @param  res  Output parameter for the absolute value
 * 
 * @since  1.1
 */
inline void
libj2_abs_j2i_to_j2u(const struct libj2_j2i *a, struct libj2_j2u *res)
{
	libj2_abs_j2i_to_j2i(a, (void *)res);
}





/**
 * Calculate the additive inverse of the absolute
 * value of a signed double-max precision integer
 * 
 * @param  a    The integer
 * @param  res  Output parameter for the inverse
 *              of the absolute value
 * 
 * @since  1.1
 */
inline void
libj2_minus_abs_j2i_to_j2i(const struct libj2_j2i *a, struct libj2_j2i *res)
{
	if (libj2_j2i_is_positive(a))
		libj2_minus_j2i_to_j2i(a, res);
	else if (a != res)
		*res = *a;
}


/**
 * Calculate the additive inverse of the absolute
 * value of a signed double-max precision integer
 * 
 * @param  a  The integer, also used as the
 *            output parameter for the inverse
 *            of the absolute value
 * 
 * @since  1.1
 */
inline void
libj2_minus_abs_j2i(struct libj2_j2i *a)
{
	if (libj2_j2i_is_positive(a))
		libj2_minus_j2i(a);
}





/**
 * If the sign-bit is set in a signed double-max
 * precision integer, flip all bits
 * 
 * @param  a    The integer to conditionally invert
 * @param  res  Output parameter for the sign-xor
 * @param  res  Output parameter for the inverse
 * 
 * @since  1.1
 */
inline void
libj2_j2i_xor_sign_to_j2i(const struct libj2_j2i *a, struct libj2_j2i *res)
{
	if (libj2_j2i_is_negative(a))
		libj2_not_j2u_to_j2u((const void *)a, (void *)res);
	else
		*res = *a;
}


/**
 * If the sign-bit is set in a signed double-max
 * precision integer, flip all bits
 * 
 * @param  a    The integer to conditionally invert
 * @param  res  Output parameter for the sign-xor
 * 
 * @since  1.1
 */
inline void
libj2_j2i_xor_sign_to_j2u(const struct libj2_j2i *a, struct libj2_j2u *res)
{
	libj2_j2i_xor_sign_to_j2i(a, (void *)res);
}


/**
 * If the sign-bit is set in a signed double-max
 * precision integer, flip all bits
 * 
 * @param  a  The integer to conditionally invert,
 *            also used as the output parameter for
 *            the sign-xor
 * 
 * @since  1.1
 */
inline void
libj2_j2i_xor_sign(struct libj2_j2i *a)
{
	if (libj2_j2i_is_negative(a))
		libj2_not_j2u((void *)a);
}
