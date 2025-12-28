/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Compare a signed double-max precision integer
 * against another signed double-max precision integer
 * 
 * `libj2_j2i_cmp_j2i(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
 * or equivalently, the signum of `*a - *b` where the signum is 0 for 0
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     -1 if `*a` is less than `*b`,
 *             +1 if `*a` is greater than `*b`,
 *             0 if `*a` is equal to `*b`
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_cmp_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	int cmp = libj2_sgn_j2i(a) - libj2_sgn_j2i(b);
	if (cmp)
		return cmp < 0 ? -1 : +1;
	return libj2_j2u_cmp_j2u((const void *)a, (const void *)b);
}


/**
 * Check whether a signed double-max precision integer is
 * less than another signed double-max precision integer
 * 
 * `libj2_j2i_lt_j2i(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_lt_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	return libj2_j2i_cmp_j2i(a, b) < 0;
}


/**
 * Check whether a signed double-max precision integer is less
 * than or equal to another signed double-max precision integer
 * 
 * `libj2_j2i_le_j2i(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_le_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	return libj2_j2i_cmp_j2i(a, b) <= 0;
}


/**
 * Check whether a signed double-max precision integer is
 * greater than another signed double-max precision integer
 * 
 * `libj2_j2i_gt_j2i(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_gt_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	return libj2_j2i_cmp_j2i(a, b) > 0;
}


/**
 * Check whether a signed double-max precision integer is greater
 * than or equal to another signed double-max precision integer
 * 
 * `libj2_j2i_ge_j2i(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ge_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	return libj2_j2i_cmp_j2i(a, b) >= 0;
}


/**
 * Check whether a signed double-max precision integer is
 * equal to another signed double-max precision integer
 * 
 * `libj2_j2i_eq_j2i(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_eq_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	return libj2_j2u_eq_j2u((const void *)a, (const void *)b);
}


/**
 * Check whether a signed double-max precision integer is
 * not equal to another signed double-max precision integer
 * 
 * `libj2_j2i_ne_j2i(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ne_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	return libj2_j2u_ne_j2u((const void *)a, (const void *)b);
}


/**
 * Compare a signed double-max precision integer
 * against a signed max precision integer
 * 
 * `libj2_j2i_cmp_ji(a, b)` implements `*a < b ? -1 : *a > b ? +1 : 0`,
 * or equivalently, the signum of `*a - b` where the signum is 0 for 0
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     -1 if `*a` is less than `b`,
 *             +1 if `*a` is greater than `b`,
 *             0 if `*a` is equal to `b`
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_cmp_ji(const struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(b, &t);
	return libj2_j2i_cmp_j2i(a, &t);
}


/**
 * Check whether a signed double-max precision integer
 * is less than a signed max precision integer
 * 
 * `libj2_j2i_lt_ji(a, b)` implements `*a < b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_lt_ji(const struct libj2_j2i *a, intmax_t b)
{
	return libj2_j2i_cmp_ji(a, b) < 0;
}


/**
 * Check whether a signed double-max precision integer is
 * less than or equal to a signed max precision integer
 * 
 * `libj2_j2i_le_ji(a, b)` implements `*a <= b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_le_ji(const struct libj2_j2i *a, intmax_t b)
{
	return libj2_j2i_cmp_ji(a, b) <= 0;
}


/**
 * Check whether a signed double-max precision integer
 * is greater than a signed max precision integer
 * 
 * `libj2_j2i_gt_ji(a, b)` implements `*a > b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_gt_ji(const struct libj2_j2i *a, intmax_t b)
{
	return libj2_j2i_cmp_ji(a, b) > 0;
}


/**
 * Check whether a signed double-max precision integer is
 * greater than or equal to a signed max precision integer
 * 
 * `libj2_j2i_ge_ji(a, b)` implements `*a >= b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ge_ji(const struct libj2_j2i *a, intmax_t b)
{
	return libj2_j2i_cmp_ji(a, b) >= 0;
}


/**
 * Check whether a signed double-max precision integer
 * is equal to a signed max precision integer
 * 
 * `libj2_j2i_eq_ji(a, b)` implements `*a == b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_eq_ji(const struct libj2_j2i *a, intmax_t b)
{
	if (b >= 0)
		return !a->high && a->low == (uintmax_t)b;
	return a->high == UINTMAX_MAX && a->low == ~(uintmax_t)-(b + 1);
}


/**
 * Check whether a signed double-max precision integer
 * is not equal to a signed max precision integer
 * 
 * `libj2_j2i_ne_ji(a, b)` implements `*a != b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ne_ji(const struct libj2_j2i *a, intmax_t b)
{
	return !libj2_j2i_eq_ji(a, b);
}


/**
 * Compare a signed max precision integer
 * against a signed double-max precision integer
 * 
 * `libj2_ji_cmp_j2i(a, b)` implements `a < *b ? -1 : a > *b ? +1 : 0`,
 * or equivalently, the signum of `a - *b` where the signum is 0 for 0
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     -1 if `a` is less than `*b`,
 *             +1 if `a` is greater than `*b`,
 *             0 if `a` is equal to `*b`
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_cmp_j2i(intmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(a, &t);
	return libj2_j2i_cmp_j2i(&t, b);
}


/**
 * Check whether a signed max precision integer is
 * less than a signed double-max precision integer
 * 
 * `libj2_ji_lt_j2i(a, b)` implements `a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_lt_j2i(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_gt_ji(b, a);
}


/**
 * Check whether a signed max precision integer is less
 * than or equal to a signed double-max precision integer
 * 
 * `libj2_ji_le_j2i(a, b)` implements `a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_le_j2i(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_ge_ji(b, a);
}


/**
 * Check whether a signed max precision integer is
 * greater than a signed double-max precision integer
 * 
 * `libj2_ji_gt_j2i(a, b)` implements `a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_gt_j2i(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_lt_ji(b, a);
}


/**
 * Check whether a signed max precision integer is greater
 * than or equal to a signed double-max precision integer
 * 
 * `libj2_ji_ge_j2i(a, b)` implements `a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_ge_j2i(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_le_ji(b, a);
}


/**
 * Check whether a signed max precision integer is
 * equal to a signed double-max precision integer
 * 
 * `libj2_ji_eq_j2i(a, b)` implements `a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_eq_j2i(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_eq_ji(b, a);
}


/**
 * Check whether a signed max precision integer is
 * not equal to a signed double-max precision integer
 * 
 * `libj2_ji_ne_j2i(a, b)` implements `a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_ne_j2i(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_ne_ji(b, a);
}





/**
 * Get the maximum of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_max_j2i_to_ji2(a, b, res)` implements
 * `*res = *a > *b ? *a : *b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the maximum of `*a` and `*b`
 * 
 * @since  1.1
 */
inline void
libj2_j2i_max_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	*res = libj2_j2i_gt_j2i(a, b) ? *a : *b;
}


/**
 * Get the maximum of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_max_j2i(a, b)` implements
 * `*a = *a > *b ? *a : *b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the maximum of `*a` and `*b`
 * @param  b  The other value
 * 
 * @since  1.1
 */
inline void
libj2_j2i_max_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	if (libj2_j2i_gt_j2i(b, a))
		*a = *b;
}


/**
 * Get the maximum of a signed double-max
 * precision integer and a signed precision
 * integer
 * 
 * `libj2_j2i_max_ji(a, b)` implements
 * `*a = *a > b ? *a : b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the maximum of `*a` and `b`
 * @param  b  The other value
 * 
 * @since  1.1
 */
inline void
libj2_j2i_max_ji(struct libj2_j2i *a, intmax_t b)
{
	if (libj2_j2i_lt_ji(a, b))
		libj2_ji_to_j2i(b, a);
}


/**
 * Get the maximum of a signed double-max
 * precision integer and a signed precision
 * integer
 * 
 * `libj2_j2i_max_ji_to_j2i(a, b, res)` implements
 * `*res = *a > b ? *a : b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the maximum of `*a` and `b`
 * 
 * @since  1.1
 */
inline void
libj2_j2i_max_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	if (libj2_j2i_lt_ji(a, b))
		libj2_ji_to_j2i(b, res);
	else
		*res = *a;
}


/**
 * Get the minimum of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_min_j2i_to_ji2(a, b, res)` implements
 * `*res = *a < *b ? *a : *b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the minimum of `*a` and `*b`
 * 
 * @since  1.1
 */
inline void
libj2_j2i_min_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	*res = libj2_j2i_lt_j2i(a, b) ? *a : *b;
}


/**
 * Get the minimum of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_min_j2i(a, b)` implements
 * `*a = *a < *b ? *a : *b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the minimum of `*a` and `*b`
 * @param  b  The other value
 * 
 * @since  1.1
 */
inline void
libj2_j2i_min_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	if (libj2_j2i_lt_j2i(b, a))
		*a = *b;
}


/**
 * Get the minimum of a signed double-max
 * precision integer and a signed precision
 * integer
 * 
 * `libj2_j2i_min_ji(a, b)` implements
 * `*a = *a < b ? *a : b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the minimum of `*a` and `b`
 * @param  b  The other value
 * 
 * @since  1.1
 */
inline void
libj2_j2i_min_ji(struct libj2_j2i *a, intmax_t b)
{
	if (libj2_j2i_gt_ji(a, b))
		libj2_ji_to_j2i(b, a);
}


/**
 * Get the minimum of a signed double-max
 * precision integer and a signed precision
 * integer
 * 
 * `libj2_j2i_min_ji_to_j2i(a, b, res)` implements
 * `*res = *a < b ? *a : b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the minimum of `*a` and `b`
 * 
 * @since  1.1
 */
inline void
libj2_j2i_min_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	if (libj2_j2i_gt_ji(a, b))
		libj2_ji_to_j2i(b, res);
	else
		*res = *a;
}


/**
 * Get the maximum of a set of signed double-max
 * precision integers
 * 
 * @param  a     One of the values, and output parameter for
 *               the maximum of the values
 * @param  args  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2i *`
 * 
 * @since  1.1
 */
inline void
libj2_vmax_j2i(struct libj2_j2i *a, va_list args)
{
	const struct libj2_j2i *b;
	while ((b = va_arg(args, const struct libj2_j2i *)))
		libj2_j2i_max_j2i(a, b);
}


/**
 * Get the maximum of a set of signed double-max
 * precision integers
 * 
 * @param  a    One of the values, and output parameter for
 *              the maximum of the values
 * @param  ...  `NULL` terminated list of additional values; each
 *              argument shall have the type `const struct libj2_j2i *`
 * 
 * @since  1.1
 */
inline void
libj2_max_j2i(struct libj2_j2i *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	libj2_vmax_j2i(a, args);
	va_end(args);
}


/**
 * Get the maximum of a set of signed double-max
 * precision integers
 * 
 * @param   a     One of the values
 * @param   args  `NULL` terminated list of additional values; each
 *                argument shall have the type `const struct libj2_j2i *`
 * @return        One of the `const struct libj2_j2i *` that as the
 *                maximum of the values of each argument
 * 
 * @since  1.1
 */
inline const struct libj2_j2i *
libj2_vmax_j2i_return(const struct libj2_j2i *a, va_list args)
{
	const struct libj2_j2i *b;
	while ((b = va_arg(args, const struct libj2_j2i *)))
		if (libj2_j2i_gt_j2i(b, a))
			a = b;
	return a;
}


/**
 * Get the maximum of a set of signed double-max
 * precision integers
 * 
 * @param   a    One of the values
 * @param   ...  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2i *`
 * @return       One of the `const struct libj2_j2i *` that as the
 *               maximum of the values of each argument
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline const struct libj2_j2i *
libj2_max_j2i_return(const struct libj2_j2i *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	return libj2_vmax_j2i_return(a, args);
	va_end(args);
}


/**
 * Get the maximum of a set of signed double-max
 * precision integers
 * 
 * @param  a     One of the values
 * @param  args  `NULL` terminated list of additional values, each
 *               argument shall have the type `const struct libj2_j2i *`,
 *               followed by a `struct libj2_j2i *` is used as the
 *               output parameter for the maximum of the values
 * 
 * @since  1.1
 */
inline void
libj2_vmax_j2i_to_j2i(const struct libj2_j2i *a, va_list args)
{
	struct libj2_j2i *res;
	a = libj2_vmax_j2i_return(a, args);
	res = va_arg(args, struct libj2_j2i *);
	*res = *a;
}


/**
 * Get the maximum of a set of signed double-max
 * precision integers
 * 
 * @param  a    One of the values
 * @param  ...  `NULL` terminated list of additional values, each
 *              argument shall have the type `const struct libj2_j2i *`,
 *              followed by a `struct libj2_j2i *` is used as the
 *              output parameter for the maximum of the values
 * 
 * @since  1.1
 */
inline void
libj2_max_j2i_to_j2i(const struct libj2_j2i *a, ... /*, NULL, struct libj2_j2i *res */)
{
	va_list args;
	va_start(args, a);
	libj2_vmax_j2i_to_j2i(a, args);
	va_end(args);
}


/**
 * Get the minimum of a set of signed double-max
 * precision integers
 * 
 * @param  a     One of the values, and output parameter for
 *               the minimum of the values
 * @param  args  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2i *`
 * 
 * @since  1.1
 */
inline void
libj2_vmin_j2i(struct libj2_j2i *a, va_list args)
{
	const struct libj2_j2i *b;
	while ((b = va_arg(args, const struct libj2_j2i *)))
		libj2_j2i_min_j2i(a, b);
}


/**
 * Get the minimum of a set of signed double-max
 * precision integers
 * 
 * @param  a    One of the values, and output parameter for
 *              the minimum of the values
 * @param  ...  `NULL` terminated list of additional values; each
 *              argument shall have the type `const struct libj2_j2i *`
 * 
 * @since  1.1
 */
inline void
libj2_min_j2i(struct libj2_j2i *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	libj2_vmin_j2i(a, args);
	va_end(args);
}


/**
 * Get the minimum of a set of signed double-max
 * precision integers
 * 
 * @param   a     One of the values
 * @param   args  `NULL` terminated list of additional values; each
 *                argument shall have the type `const struct libj2_j2i *`
 * @return        One of the `const struct libj2_j2i *` that as the
 *                minimum of the values of each argument
 * 
 * @since  1.1
 */
inline const struct libj2_j2i *
libj2_vmin_j2i_return(const struct libj2_j2i *a, va_list args)
{
	const struct libj2_j2i *b;
	while ((b = va_arg(args, const struct libj2_j2i *)))
		if (libj2_j2i_lt_j2i(b, a))
			a = b;
	return a;
}


/**
 * Get the minimum of a set of signed double-max
 * precision integers
 * 
 * @param   a    One of the values
 * @param   ...  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2i *`
 * @return       One of the `const struct libj2_j2i *` that as the
 *               minimum of the values of each argument
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline const struct libj2_j2i *
libj2_min_j2i_return(const struct libj2_j2i *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	return libj2_vmin_j2i_return(a, args);
	va_end(args);
}


/**
 * Get the minimum of a set of signed double-max
 * precision integers
 * 
 * @param  a     One of the values
 * @param  args  `NULL` terminated list of additional values, each
 *               argument shall have the type `const struct libj2_j2i *`,
 *               followed by a `struct libj2_j2i *` is used as the
 *               output parameter for the minimum of the values
 * 
 * @since  1.1
 */
inline void
libj2_vmin_j2i_to_j2i(const struct libj2_j2i *a, va_list args)
{
	struct libj2_j2i *res;
	a = libj2_vmin_j2i_return(a, args);
	res = va_arg(args, struct libj2_j2i *);
	*res = *a;
}


/**
 * Get the minimum of a set of signed double-max
 * precision integers
 * 
 * @param  a    One of the values
 * @param  ...  `NULL` terminated list of additional values, each
 *              argument shall have the type `const struct libj2_j2i *`,
 *              followed by a `struct libj2_j2i *` is used as the
 *              output parameter for the minimum of the values
 * 
 * @since  1.1
 */
inline void
libj2_min_j2i_to_j2i(const struct libj2_j2i *a, ... /*, NULL, struct libj2_j2i *res */)
{
	va_list args;
	va_start(args, a);
	libj2_vmin_j2i_to_j2i(a, args);
	va_end(args);
}
