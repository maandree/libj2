/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif



/**
 * Check whether an unsigned double-max precision integer is
 * less than another unsigned double-max precision integer
 * 
 * `libj2_j2u_lt_j2u(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 */
inline int
libj2_j2u_lt_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high < b->high || (a->high == b->high && a->low < b->low);
}


/**
 * Check whether an unsigned double-max precision integer is less
 * than or equal to another unsigned double-max precision integer
 * 
 * `libj2_j2u_le_j2u(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 */
inline int
libj2_j2u_le_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high < b->high || (a->high == b->high && a->low <= b->low);
}


/**
 * Check whether an unsigned double-max precision integer is
 * greater than another unsigned double-max precision integer
 * 
 * `libj2_j2u_gt_j2u(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 */
inline int
libj2_j2u_gt_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high > b->high || (a->high == b->high && a->low > b->low);
}


/**
 * Check whether an unsigned double-max precision integer is greater
 * than or equal to another unsigned double-max precision integer
 * 
 * `libj2_j2u_ge_j2u(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 */
inline int
libj2_j2u_ge_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high > b->high || (a->high == b->high && a->low >= b->low);
}


/**
 * Check whether an unsigned double-max precision integer is
 * equal to another unsigned double-max precision integer
 * 
 * `libj2_j2u_eq_j2u(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 */
inline int
libj2_j2u_eq_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high == b->high && a->low == b->low;
}


/**
 * Check whether an unsigned double-max precision integer is
 * not equal to another unsigned double-max precision integer
 * 
 * `libj2_j2u_eq_j2u(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 */
inline int
libj2_j2u_ne_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high != b->high || a->low != b->low;
}


/**
 * Compare an unsigned double-max precision integer
 * to another unsigned double-max precision integer
 * 
 * `libj2_j2u_cmp_j2u(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
 * or equivalently, the signum of `*a - *b` where the signum is 0 for 0
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     -1 if `*a` is less than `*b`,
 *             +1 if `*a` is greater than `*b`,
 *             0 if `*a` is equal to `*b`
 */
inline int
libj2_j2u_cmp_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return a->high < b->high ? -1 : a->high > b->high ? +1 : a->low < b->low ? -1 : a->low > b->low;
}


/**
 * Check whether an unsigned double-max precision integer
 * is less than an unsigned max precision integer
 * 
 * `libj2_j2u_lt_ju(a, b)` implements `*a < b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `b`, 0 otherwise
 */
inline int
libj2_j2u_lt_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return !a->high && a->low < b;
}


/**
 * Check whether an unsigned double-max precision integer is
 * less than or equal to an unsigned max precision integer
 * 
 * `libj2_j2u_le_ju(a, b)` implements `*a <= b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `b`, 0 otherwise
 */
inline int
libj2_j2u_le_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return !a->high && a->low <= b;
}


/**
 * Check whether an unsigned double-max precision integer
 * is greater than an unsigned max precision integer
 * 
 * `libj2_j2u_gt_ju(a, b)` implements `*a > b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `b`, 0 otherwise
 */
inline int
libj2_j2u_gt_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return a->high || a->low > b;
}


/**
 * Check whether an unsigned double-max precision integer is
 * greater than or equal to an unsigned max precision integer
 * 
 * `libj2_j2u_ge_ju(a, b)` implements `*a >= b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `b`, 0 otherwise
 */
inline int
libj2_j2u_ge_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return a->high || a->low >= b;
}


/**
 * Check whether an unsigned double-max precision integer
 * is equal to an unsigned max precision integer
 * 
 * `libj2_j2u_eq_ju(a, b)` implements `*a == b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `b`, 0 otherwise
 */
inline int
libj2_j2u_eq_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return !a->high && a->low == b;
}


/**
 * Check whether an unsigned double-max precision integer
 * is not equal to an unsigned max precision integer
 * 
 * `libj2_j2u_ne_ju(a, b)` implements `*a != b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `b`, 0 otherwise
 */
inline int
libj2_j2u_ne_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return a->high || a->low != b;
}


/**
 * Compare an unsigned double-max precision integer
 * to an unsigned max precision integer
 * 
 * `libj2_j2u_cmp_ju(a, b)` implements `*a < b ? -1 : *a > b ? +1 : 0`,
 * or equivalently, the signum of `*a - b` where the signum is 0 for 0
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     -1 if `*a` is less than `b`,
 *             +1 if `*a` is greater than `b`,
 *             0 if `*a` is equal to `b`
 */
inline int
libj2_j2u_cmp_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return a->high ? +1 : a->low < b ? -1 : a->low > b;
}


/**
 * Check whether an unsigned max precision integer is
 * less than an unsigned double-max precision integer
 * 
 * `libj2_ju_lt_j2u(a, b)` implements `a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is less than `*b`, 0 otherwise
 */
inline int
libj2_ju_lt_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_gt_ju(b, a);
}


/**
 * Check whether an unsigned max precision integer is less
 * than or equal to an unsigned double-max precision integer
 * 
 * `libj2_ju_le_j2u(a, b)` implements `a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is less than or equal to `*b`, 0 otherwise
 */
inline int
libj2_ju_le_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_ge_ju(b, a);
}


/**
 * Check whether an unsigned max precision integer is
 * greater than an unsigned double-max precision integer
 * 
 * `libj2_ju_gt_j2u(a, b)` implements `a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is less than `*b`, 0 otherwise
 */
inline int
libj2_ju_gt_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_lt_ju(b, a);
}


/**
 * Check whether an unsigned max precision integer is greater
 * than or equal to an unsigned double-max precision integer
 * 
 * `libj2_ju_ge_j2u(a, b)` implements `a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is greater than or equal to `*b`, 0 otherwise
 */
inline int
libj2_ju_ge_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_le_ju(b, a);
}


/**
 * Check whether an unsigned max precision integer is
 * equal to an unsigned double-max precision integer
 * 
 * `libj2_ju_eq_j2u(a, b)` implements `a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is equal to `*b`, 0 otherwise
 */
inline int
libj2_ju_eq_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_eq_ju(b, a);
}


/**
 * Check whether an unsigned max precision integer is
 * not equal to an unsigned double-max precision integer
 * 
 * `libj2_ju_ne_j2u(a, b)` implements `a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `a` is not equal to `*b`, 0 otherwise
 */
inline int
libj2_ju_ne_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_ne_ju(b, a);
}


/**
 * Compare an unsigned max precision integer
 * to an unsigned double-max precision integer
 * 
 * `libj2_ju_cmp_j2u(a, b)` implements `a < *b ? -1 : a > *b ? +1 : 0`,
 * or equivalently, the signum of `a - *b` where the signum is 0 for 0
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     -1 if `a` is less than `*b`,
 *             +1 if `a` is greater than `*b`,
 *             0 if `a` is equal to `*b`
 */
inline int
libj2_ju_cmp_j2u(uintmax_t a, const struct libj2_j2u *b)
{
	return b->high ? -1 : a < b->low ? -1 : a > b->low;
}





/**
 * Get the maximum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_max_j2u_to_ju2(a, b, res)` implements
 * `*res = *a > *b ? *a : *b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the maximum of `*a` and `*b`
 */
inline void
libj2_j2u_max_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	*res = libj2_j2u_gt_j2u(a, b) ? *a : *b;
}


/**
 * Get the maximum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_max_j2u(a, b)` implements
 * `*a = *a > *b ? *a : *b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the maximum of `*a` and `*b`
 * @param  b  The other value
 */
inline void
libj2_j2u_max_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (libj2_j2u_gt_j2u(b, a))
		*a = *b;
}


/**
 * Get the maximum of an unsigned double-max
 * precision integer and an unsigned precision
 * integer
 * 
 * `libj2_j2u_max_ju(a, b)` implements
 * `*a = *a > b ? *a : b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the maximum of `*a` and `b`
 * @param  b  The other value
 */
inline void
libj2_j2u_max_ju(struct libj2_j2u *a, uintmax_t b)
{
	if (!a->high && a->low < b)
		a->low = b;
}


/**
 * Get the maximum of an unsigned double-max
 * precision integer and an unsigned precision
 * integer
 * 
 * `libj2_j2u_max_ju_to_j2u(a, b, res)` implements
 * `*res = *a > b ? *a : b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the maximum of `*a` and `b`
 */
inline void
libj2_j2u_max_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	if (!a->high && a->low < b) {
		res->high = 0;
		res->low = b;
	} else {
		*res = *a;
	}
}


/**
 * Get the minimum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_min_j2u_to_ju2(a, b, res)` implements
 * `*res = *a < *b ? *a : *b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the minimum of `*a` and `*b`
 */
inline void
libj2_j2u_min_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	*res = libj2_j2u_lt_j2u(a, b) ? *a : *b;
}


/**
 * Get the minimum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_min_j2u(a, b)` implements
 * `*a = *a < *b ? *a : *b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the minimum of `*a` and `*b`
 * @param  b  The other value
 */
inline void
libj2_j2u_min_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (libj2_j2u_lt_j2u(b, a))
		*a = *b;
}


/**
 * Get the minimum of an unsigned double-max
 * precision integer and an unsigned precision
 * integer
 * 
 * `libj2_j2u_min_ju(a, b)` implements
 * `*a = *a < b ? *a : b`
 * 
 * @param  a  One of the values, and output parameter
 *            for the minimum of `*a` and `b`
 * @param  b  The other value
 */
inline void
libj2_j2u_min_ju(struct libj2_j2u *a, uintmax_t b)
{
	if (a->high || a->low > b) {
		a->high = 0;
		a->low = b;
	}
}


/**
 * Get the minimum of an unsigned double-max
 * precision integer and an unsigned precision
 * integer
 * 
 * `libj2_j2u_min_ju_to_j2u(a, b, res)` implements
 * `*res = *a < b ? *a : b`
 * 
 * @param  a    One of the values
 * @param  b    The other value
 * @param  res  Output parameter for the minimum of `*a` and `b`
 */
inline void
libj2_j2u_min_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	if (a->high || a->low > b) {
		res->high = 0;
		res->low = b;
	} else {
		*res = *a;
	}
}


/**
 * Get the maximum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a     One of the values, and output parameter for
 *               the maximum of the values
 * @param  args  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2u *`
 */
inline void
libj2_vmax_j2u(struct libj2_j2u *a, va_list args)
{
	const struct libj2_j2u *b;
	while ((b = va_arg(args, const struct libj2_j2u *)))
		libj2_j2u_max_j2u(a, b);
}


/**
 * Get the maximum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a    One of the values, and output parameter for
 *              the maximum of the values
 * @param  ...  `NULL` terminated list of additional values; each
 *              argument shall have the type `const struct libj2_j2u *`
 */
inline void
libj2_max_j2u(struct libj2_j2u *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	libj2_vmax_j2u(a, args);
	va_end(args);
}


/**
 * Get the maximum of a set of unsigned double-max
 * precision integers
 * 
 * @param   a     One of the values
 * @param   args  `NULL` terminated list of additional values; each
 *                argument shall have the type `const struct libj2_j2u *`
 * @return        One of the `const struct libj2_j2u *` that as the
 *                maximum of the values of each argument
 */
inline const struct libj2_j2u *
libj2_vmax_j2u_return(const struct libj2_j2u *a, va_list args)
{
	const struct libj2_j2u *b;
	while ((b = va_arg(args, const struct libj2_j2u *)))
		if (libj2_j2u_gt_j2u(b, a))
			a = b;
	return a;
}


/**
 * Get the maximum of a set of unsigned double-max
 * precision integers
 * 
 * @param   a    One of the values
 * @param   ...  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2u *`
 * @return       One of the `const struct libj2_j2u *` that as the
 *               maximum of the values of each argument
 */
inline const struct libj2_j2u *
libj2_max_j2u_return(const struct libj2_j2u *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	return libj2_vmax_j2u_return(a, args);
	va_end(args);
}


/**
 * Get the maximum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a     One of the values
 * @param  args  `NULL` terminated list of additional values, each
 *               argument shall have the type `const struct libj2_j2u *`,
 *               followed by a `struct libj2_j2u *` is used as the
 *               output parameter for the maximum of the values
 */
inline void
libj2_vmax_j2u_to_j2u(const struct libj2_j2u *a, va_list args)
{
	struct libj2_j2u *res;
	a = libj2_vmax_j2u_return(a, args);
	res = va_arg(args, struct libj2_j2u *);
	*res = *a;
}


/**
 * Get the maximum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a    One of the values
 * @param  ...  `NULL` terminated list of additional values, each
 *              argument shall have the type `const struct libj2_j2u *`,
 *              followed by a `struct libj2_j2u *` is used as the
 *              output parameter for the maximum of the values
 */
inline void
libj2_max_j2u_to_j2u(const struct libj2_j2u *a, ... /*, NULL, struct libj2_j2u *res */)
{
	va_list args;
	va_start(args, a);
	libj2_vmax_j2u_to_j2u(a, args);
	va_end(args);
}


/**
 * Get the minimum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a     One of the values, and output parameter for
 *               the minimum of the values
 * @param  args  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2u *`
 */
inline void
libj2_vmin_j2u(struct libj2_j2u *a, va_list args)
{
	const struct libj2_j2u *b;
	while ((b = va_arg(args, const struct libj2_j2u *)))
		libj2_j2u_min_j2u(a, b);
}


/**
 * Get the minimum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a    One of the values, and output parameter for
 *              the minimum of the values
 * @param  ...  `NULL` terminated list of additional values; each
 *              argument shall have the type `const struct libj2_j2u *`
 */
inline void
libj2_min_j2u(struct libj2_j2u *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	libj2_vmin_j2u(a, args);
	va_end(args);
}


/**
 * Get the minimum of a set of unsigned double-max
 * precision integers
 * 
 * @param   a     One of the values
 * @param   args  `NULL` terminated list of additional values; each
 *                argument shall have the type `const struct libj2_j2u *`
 * @return        One of the `const struct libj2_j2u *` that as the
 *                minimum of the values of each argument
 */
inline const struct libj2_j2u *
libj2_vmin_j2u_return(const struct libj2_j2u *a, va_list args)
{
	const struct libj2_j2u *b;
	while ((b = va_arg(args, const struct libj2_j2u *)))
		if (libj2_j2u_lt_j2u(b, a))
			a = b;
	return a;
}


/**
 * Get the minimum of a set of unsigned double-max
 * precision integers
 * 
 * @param   a    One of the values
 * @param   ...  `NULL` terminated list of additional values; each
 *               argument shall have the type `const struct libj2_j2u *`
 * @return       One of the `const struct libj2_j2u *` that as the
 *               minimum of the values of each argument
 */
inline const struct libj2_j2u *
libj2_min_j2u_return(const struct libj2_j2u *a, ... /*, NULL */)
{
	va_list args;
	va_start(args, a);
	return libj2_vmin_j2u_return(a, args);
	va_end(args);
}


/**
 * Get the minimum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a     One of the values
 * @param  args  `NULL` terminated list of additional values, each
 *               argument shall have the type `const struct libj2_j2u *`,
 *               followed by a `struct libj2_j2u *` is used as the
 *               output parameter for the minimum of the values
 */
inline void
libj2_vmin_j2u_to_j2u(const struct libj2_j2u *a, va_list args)
{
	struct libj2_j2u *res;
	a = libj2_vmin_j2u_return(a, args);
	res = va_arg(args, struct libj2_j2u *);
	*res = *a;
}


/**
 * Get the minimum of a set of unsigned double-max
 * precision integers
 * 
 * @param  a    One of the values
 * @param  ...  `NULL` terminated list of additional values, each
 *              argument shall have the type `const struct libj2_j2u *`,
 *              followed by a `struct libj2_j2u *` is used as the
 *              output parameter for the minimum of the values
 */
inline void
libj2_min_j2u_to_j2u(const struct libj2_j2u *a, ... /*, NULL, struct libj2_j2u *res */)
{
	va_list args;
	va_start(args, a);
	libj2_vmin_j2u_to_j2u(a, args);
	va_end(args);
}
