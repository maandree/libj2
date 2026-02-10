/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Shift the bits in an unsigned double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * If any set bit is shifted out of precision, it will
 * be regarded an arithmetic overflow, and the result
 * will be saturated to the maximum value that can be
 * represented
 * 
 * `libj2_j2u_sat_lsh` is a version `libj2_j2u_lsh`
 * that uses saturated arithmetics
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2, using satured multiplication
 * 
 * @param  a  The integer to shift, also used as the
 *            output parameter for the result
 * @param  b  The number of positions to shift each bit
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_lsh(struct libj2_j2u *a, unsigned b)
{
	if (libj2_j2u_lsh_overflow(a, b))
		libj2_j2u_max(a);
}


/**
 * Shift the bits in an unsigned double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * If any set bit is shifted out of precision, it will
 * be regarded an arithmetic overflow, and the result
 * will be saturated to the maximum value that can be
 * represented
 * 
 * `libj2_j2u_sat_lsh_to_j2u` is a version
 * `libj2_j2u_lsh_to_j2u` that uses saturated arithmetics
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2, using satured multiplication
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_lsh_to_j2u(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	if (libj2_j2u_lsh_to_j2u_overflow(a, b, res))
		libj2_j2u_max(res);
}


/**
 * Shift the bits in an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to more signficant positions (left-shift)
 * 
 * If any set bit is shifted out of precision, it will
 * be regarded an arithmetic overflow, and the result
 * will be saturated to the maximum value that can be
 * represented
 * 
 * `libj2_ju_sat_lsh_to_j2u` is a version
 * `libj2_ju_lsh_to_j2u` that uses saturated arithmetics
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2, using satured multiplication
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 * 
 * @since  1.1
 */
inline void
libj2_ju_sat_lsh_to_j2u(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	if (libj2_ju_lsh_to_j2u_overflow(a, b, res))
		libj2_j2u_max(res);
}


/**
 * Shift the bits in a signed double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * If any set bit is shifted out of precision, it will
 * be regarded an arithmetic overflow, and the result
 * will be saturated to the maximum value (if positive)
 * or minimum value (if negaitve) that can be
 * represented
 * 
 * `libj2_j2i_sat_lsh` is a version `libj2_j2i_lsh`
 * that uses saturated arithmetics
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2, using satured multiplication
 * 
 * @param  a  The integer to shift, also used as the
 *            output parameter for the result
 * @param  b  The number of positions to shift each bit
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_lsh(struct libj2_j2i *a, unsigned b)
{
	int r = libj2_j2i_lsh_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}


/**
 * Shift the bits in a signed double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * If any set bit is shifted out of precision, it will
 * be regarded an arithmetic overflow, and the result
 * will be saturated to the maximum value (if positive)
 * or minimum value (if negaitve) that can be
 * represented
 * 
 * `libj2_j2i_sat_lsh_to_j2i` is a version
 * `libj2_j2i_lsh_to_j2i` that uses saturated arithmetics
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2, using satured multiplication
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_lsh_to_j2i(const struct libj2_j2i *a, unsigned b, struct libj2_j2i *res)
{
	int r = libj2_j2i_lsh_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}


/**
 * Shift the bits in a signed double-max precision
 * integer, represented by a signed max precision
 * integer and whose high part, of the value bits,
 * is treated as having the value 0, to more
 * signficant positions (left-shift)
 * 
 * If any set bit is shifted out of precision, it will
 * be regarded an arithmetic overflow, and the result
 * will be saturated to the maximum value (if positive)
 * or minimum value (if negaitve) that can be
 * represented
 * 
 * `libj2_ji_sat_lsh_to_j2i` is a version
 * `libj2_ji_lsh_to_j2i` that uses saturated arithmetics
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2, using satured multiplication
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 * 
 * @since  1.1
 */
inline void
libj2_ji_sat_lsh_to_j2i(intmax_t a, unsigned b, struct libj2_j2i *res)
{
	int r = libj2_ji_lsh_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}





/**
 * Calculate the saturated sum of an unsigned double-max
 * precision integer and an unsigned max precision integer
 * 
 * `libj2_j2u_sat_add_ju` is a version
 * `libj2_j2u_add_ju` that uses saturated arithmetics,
 * meaning that if the result is too large to be
 * represented it is saturated into the maximum value
 * that can be represented
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_add_ju(struct libj2_j2u *a, uintmax_t b)
{
	if (libj2_j2u_add_ju_overflow(a, b))
		libj2_j2u_max(a);
}


/**
 * Calculate the saturated sum of an unsigned double-max
 * precision integer and an unsigned max precision integer
 * 
 * `libj2_j2u_sat_add_ju_to_j2u` is a version
 * `libj2_j2u_add_ju_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value that can be represented
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_add_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	if (libj2_j2u_add_ju_to_j2u_overflow(a, b, res))
		libj2_j2u_max(res);
}


/**
 * Calculate the saturated sum of an unsigned max precision
 * integer and an unsigned double-max precision integer
 * 
 * `libj2_ju_sat_add_j2u_to_j2u` is a version
 * `libj2_ju_add_j2u_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value that can be represented
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_ju_sat_add_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (libj2_ju_add_j2u_to_j2u_overflow(a, b, res))
		libj2_j2u_max(res);
}


/**
 * Calculate the saturated sum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_sat_add_j2u` is a version
 * `libj2_j2u_add_j2u` that uses saturated arithmetics,
 * meaning that if the result is too large to be
 * represented it is saturated into the maximum value
 * that can be represented
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_add_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (libj2_j2u_add_j2u_overflow(a, b))
		libj2_j2u_max(a);
}


/**
 * Calculate the saturated sum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_sat_add_j2u_to_j2u` is a version
 * `libj2_j2u_add_j2u_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value that can be represented
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_add_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (libj2_j2u_add_j2u_to_j2u_overflow(a, b, res))
		libj2_j2u_max(res);
}


/**
 * Calculate the saturated sum of a signed double-max
 * precision integer and a signed max precision integer
 * 
 * `libj2_j2i_sat_add_ji` is a version
 * `libj2_j2i_add_ji` that uses saturated arithmetics,
 * meaning that if the result is too large to be
 * represented it is saturated into the maximum value
 * (if positive) or minimum value (if negative) that
 * can be represented
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_add_ji(struct libj2_j2i *a, intmax_t b)
{
	int r = libj2_j2i_add_ji_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}


/**
 * Calculate the saturated sum of a signed double-max
 * precision integer and a signed max precision integer
 * 
 * `libj2_j2i_sat_add_ji_to_j2i` is a version
 * `libj2_j2i_add_ji_to_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_add_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	int r = libj2_j2i_add_ji_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}


/**
 * Calculate the saturated sum of a signed max precision
 * integer and a signed double-max precision integer
 * 
 * `libj2_ji_sat_add_j2i_to_j2i` is a version
 * `libj2_ji_add_j2i_to_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum
 * value (if negative) that can be represented
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_ji_sat_add_j2i_to_j2i(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	int r = libj2_ji_add_j2i_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}


/**
 * Calculate the saturated sum of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_sat_add_j2i` is a version
 * `libj2_j2i_add_j2i` that uses saturated arithmetics,
 * meaning that if the result is too large to be
 * represented it is saturated into the maximum value
 * (if positive) or minimum value (if negative) that
 * can be represented
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_add_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	int r = libj2_j2i_add_j2i_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}


/**
 * Calculate the saturated sum of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_sat_add_j2i_to_j2i` is a version
 * `libj2_j2i_add_j2i_to_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum
 * value (if negative) that can be represented
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_add_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	int r = libj2_j2i_add_j2i_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}





/**
 * Calculate the saturated difference between an
 * unsigned double-max precision integer (minuend)
 * and an unsigned max precision integer (subtrahend)
 * 
 * `libj2_j2u_sat_sub_ju` is a version
 * `libj2_j2u_sub_ju` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a  The minuend (left-hand), also used as the
 *            output parameter for the difference
 * @param  b  The subtrahend (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_sub_ju(struct libj2_j2u *a, uintmax_t b)
{
	if (libj2_j2u_sub_ju_overflow(a, b))
		libj2_j2u_min(a);
}


/**
 * Calculate the saturated difference between an
 * unsigned double-max precision integer (minuend)
 * and an unsigned max precision integer (subtrahend)
 * 
 * `libj2_j2u_sat_sub_ju_to_j2u` is a version
 * `libj2_j2u_sub_ju_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_sub_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	if (libj2_j2u_sub_ju_to_j2u_overflow(a, b, res))
		libj2_j2u_min(res);
}


/**
 * Calculate the saturated difference between two unsigned
 * max precision integers, as an unsigned double-max
 * precision integer
 * 
 * `libj2_ju_sat_sub_ju_to_j2u` is a version
 * `libj2_ju_sub_ju_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_ju_sat_sub_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res)
{
	if (libj2_ju_sub_ju_to_j2u_overflow(a, b, res))
		libj2_j2u_min(res);
}


/**
 * Calculate the saturated difference between two
 * unsigned double-max precision integers
 * 
 * `libj2_j2u_sat_sub_j2u` is a version
 * `libj2_j2u_sub_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a  The minuend (left-hand), also used
 *            as the output parameter for the difference
 * @param  b  The subtrahend (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_sub_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (libj2_j2u_sub_j2u_overflow(a, b))
		libj2_j2u_min(a);
}


/**
 * Calculate the saturated difference between two
 * unsigned double-max precision integers
 * 
 * `libj2_j2u_sat_sub_j2u_to_j2u` is a version
 * `libj2_j2u_sub_j2u_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_sub_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (libj2_j2u_sub_j2u_to_j2u_overflow(a, b, res))
		libj2_j2u_min(res);
}


/**
 * Calculate the saturated difference between an
 * unsigned max precision integer (minuend) and an
 * unsigned double-max precision integer (subtrahend)
 * 
 * `libj2_ju_sat_sub_j2u_to_j2u` is a version
 * `libj2_ju_sub_j2u_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_ju_sat_sub_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (libj2_ju_sub_j2u_to_j2u_overflow(a, b, res))
		libj2_j2u_min(res);
}


/**
 * Calculate the saturated difference between two
 * unsigned max precision integers; in this variant
 * of `libj2_j2u_sat_sub_j2u`, the minuend (left-hand)
 * is the second parameter and the subtrahend
 * (right-hand) is the first parameter
 * 
 * `libj2_j2u_sat_rsub_j2u` is a version
 * `libj2_j2u_rsub_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a    The subtrahend (right-hand), also used as
 *              the output parameter for the difference
 * @param  b    The minuend (left-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_rsub_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (libj2_j2u_rsub_j2u_overflow(a, b))
		libj2_j2u_min(a);
}


/**
 * Calculate the saturated difference between an
 * unsigned max precision integer (minuend) and an
 * unsigned double-max precision integer (subtrahend);
 * in this variant of `libj2_j2u_sat_sub_ju`, the
 * minuend (left-hand) is the second parameter
 * and the subtrahend (right-hand) is the first
 * parameter
 * 
 * `libj2_j2u_sat_rsub_ju` is a version
 * `libj2_j2u_rsub_ju` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the value zero
 * 
 * @param  a  The subtrahend (right-hand), also used as
 *            the output parameter for the difference
 * @param  b  The minuend (left-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_rsub_ju(struct libj2_j2u *a, uintmax_t b)
{
	if (libj2_j2u_rsub_ju_overflow(a, b))
		libj2_j2u_min(a);
}


/**
 * Calculate the saturated difference between n
 * signed double-max precision integer (minuend)
 * and a signed max precision integer (subtrahend)
 * 
 * `libj2_j2i_sat_sub_ji` is a version
 * `libj2_j2i_sub_ji` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a  The minuend (left-hand), also used as the
 *            output parameter for the difference
 * @param  b  The subtrahend (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_sub_ji(struct libj2_j2i *a, intmax_t b)
{
	int r = libj2_j2i_sub_ji_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}


/**
 * Calculate the saturated difference between a
 * signed double-max precision integer (minuend)
 * and a signed max precision integer (subtrahend)
 * 
 * `libj2_j2i_sat_sub_ji_to_j2i` is a version
 * `libj2_j2i_sub_ji_to_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_sub_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	int r = libj2_j2i_sub_ji_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}


/**
 * Calculate the saturated difference between two
 * signed double-max precision integers
 * 
 * `libj2_j2i_sat_sub_j2i` is a version
 * `libj2_j2i_sub_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a  The minuend (left-hand), also used
 *            as the output parameter for the difference
 * @param  b  The subtrahend (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_sub_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	int r = libj2_j2i_sub_j2i_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}


/**
 * Calculate the saturated difference between two
 * signed double-max precision integers
 * 
 * `libj2_j2i_sat_sub_j2i_to_j2i` is a version
 * `libj2_j2i_sub_j2i_to_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_sub_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	int r = libj2_j2i_sub_j2i_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}


/**
 * Calculate the saturated difference between a
 * signed max precision integer (minuend) and a
 * signed double-max precision integer (subtrahend)
 * 
 * `libj2_ji_sat_sub_j2i_to_j2i` is a version
 * `libj2_ji_sub_j2i_to_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.1
 */
inline void
libj2_ji_sat_sub_j2i_to_j2i(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	int r = libj2_ji_sub_j2i_to_j2i_overflow(a, b, res);
	if (r > 0)
		libj2_j2i_max(res);
	else if (r)
		libj2_j2i_min(res);
}


/**
 * Calculate the saturated difference between two
 * unsigned max precision integers; in this variant
 * of `libj2_j2i_sat_sub_j2i`, the minuend (left-hand)
 * is the second parameter and the subtrahend
 * (right-hand) is the first parameter
 * 
 * `libj2_j2i_sat_rsub_j2i` is a version
 * `libj2_j2i_rsub_j2i` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a    The subtrahend (right-hand), also used as
 *              the output parameter for the difference
 * @param  b    The minuend (left-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_rsub_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	int r = libj2_j2i_rsub_j2i_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}


/**
 * Calculate the saturated difference between an
 * unsigned max precision integer (minuend) and an
 * unsigned double-max precision integer (subtrahend);
 * in this variant of `libj2_j2i_sat_sub_ji`, the
 * minuend (left-hand) is the second parameter
 * and the subtrahend (right-hand) is the first
 * parameter
 * 
 * `libj2_j2i_sat_rsub_ji` is a version
 * `libj2_j2i_rsub_ji` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value (if positive) or minimum value
 * (if negative) that can be represented
 * 
 * @param  a  The subtrahend (right-hand), also used as
 *            the output parameter for the difference
 * @param  b  The minuend (left-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_sat_rsub_ji(struct libj2_j2i *a, intmax_t b)
{
	int r = libj2_j2i_rsub_ji_overflow(a, b);
	if (r > 0)
		libj2_j2i_max(a);
	else if (r)
		libj2_j2i_min(a);
}





/**
 * Calculate the saturated product of an unsigned
 * double-max precision integer (multiplier) and an
 * unsigned max precision integer (multiplicand)
 * 
 * `libj2_j2u_sat_mul_ju` is a version
 * `libj2_j2u_mul_ju` that uses saturated arithmetics,
 * meaning that if the result is too large to be
 * represented it is saturated into the maximum value
 * that can be represented
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_mul_ju(struct libj2_j2u *a, uintmax_t b)
{
	uintmax_t c;

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_mul_overflow(a->high, b, &c))
		goto overflow;
#else
	if (b && a->high > UINTMAX_MAX / b)
		goto overflow;
	c = a->high * b;
#endif

	libj2_ju_mul_ju_to_j2u(a->low, b, a);

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(a->high, c, &a->high))
		goto overflow;
#else
	if (a->high > UINTMAX_MAX - c)
		goto overflow;
	a->high += c;
#endif

	return;

overflow:
	libj2_j2u_max(a);
}


/**
 * Calculate the saturated product of an unsigned
 * double-max precision integer (multiplier) and an
 * unsigned max precision integer (multiplicand)
 * 
 * `libj2_j2u_sat_mul_ju_to_j2u` is a version
 * `libj2_j2u_mul_ju_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value that can be represented
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_mul_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_sat_mul_ju(res, b);
}


/**
 * Calculate the saturated product of an unsigned
 * max precision integer (multiplier) and an unsigned
 * double-max precision integer (multiplicand)
 * 
 * `libj2_ju_sat_mul_j2u_to_j2u` is a version
 * `libj2_ju_mul_j2u_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value that can be represented
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_ju_sat_mul_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	*res = *b;
	libj2_j2u_sat_mul_ju(res, a);
}


/**
 * Calculate the saturated product of two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sat_mul_j2u_destructive` is a version
 * `libj2_j2u_mul_j2u_destructive` that uses saturated
 * arithmetics, meaning that if the result is too large
 * to be represented it is saturated into the maximum
 * value that can be represented
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand; will be tainted
 * 
 * `a` and `b` must not be the same pointers
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_mul_j2u_destructive(struct libj2_j2u *restrict a /* result */, struct libj2_j2u *restrict b /* destructed */)
{
	if (a->high && b->high)
		goto overflow;

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_mul_overflow(a->high, b->low, &a->high))
		goto overflow;
	if (__builtin_mul_overflow(b->high, a->low, &b->high))
		goto overflow;
	if (__builtin_add_overflow(b->high, a->high, &b->high))
		goto overflow;
#else
	if (b->low && a->high > UINTMAX_MAX / b->low)
		goto overflow;
	a->high *= b->low;
	if (a->low && b->high > UINTMAX_MAX / a->low)
		goto overflow;
	b->high *= a->low;
	if (b->high > UINTMAX_MAX - a->high)
		goto overflow;
	b->high += a->high;
#endif

	libj2_ju_mul_ju_to_j2u(a->low, b->low, a);

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(a->high, b->high, &a->high))
		goto overflow;
#else
	if (a->high > UINTMAX_MAX - b->high)
		goto overflow;
	a->high += b->high;
#endif

	return;

overflow:
	libj2_j2u_max(a);
}


/**
 * Calculate the saturated product of two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sat_mul_j2u` is a version
 * `libj2_j2u_mul_j2u` that uses saturated arithmetics,
 * meaning that if the result is too large to be
 * represented it is saturated into the maximum value
 * that can be represented
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_mul_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *b;
	libj2_j2u_sat_mul_j2u_destructive(a, &c);
}


/**
 * Calculate the saturated product of two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sat_mul_j2u_to_j2u` is a version
 * `libj2_j2u_mul_j2u_to_j2u` that uses saturated
 * arithmetics, meaning that if the result is too
 * large to be represented it is saturated into
 * the maximum value that can be represented
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_j2u_sat_mul_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *b;
	*res = *a;
	libj2_j2u_sat_mul_j2u_destructive(res, &c);
}
