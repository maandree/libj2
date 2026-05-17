/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Check whether a signed double-max precision integer
 * is less than an unsigned double-max precision integer
 * 
 * `libj2_j2i_lt_j2u(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_lt_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 1;
	return libj2_j2u_lt_j2u(&u, b);
}


/**
 * Check whether a signed double-max precision integer is less
 * than or equal to an unsigned double-max precision integer
 * 
 * `libj2_j2i_le_j2u(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_le_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 1;
	return libj2_j2u_le_j2u(&u, b);
}


/**
 * Check whether a signed double-max precision integer
 * is greater than an unsigned double-max precision integer
 * 
 * `libj2_j2i_gt_j2u(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_gt_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 0;
	return libj2_j2u_gt_j2u(&u, b);
}


/**
 * Check whether a signed double-max precision integer is greater
 * than or equal to an unsigned double-max precision integer
 * 
 * `libj2_j2i_ge_j2u(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ge_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 0;
	return libj2_j2u_ge_j2u(&u, b);
}


/**
 * Check whether a signed double-max precision integer
 * is equal to an unsigned double-max precision integer
 * 
 * `libj2_j2i_eq_j2u(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_eq_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 0;
	return libj2_j2u_eq_j2u(&u, b);
}


/**
 * Check whether a signed double-max precision integer
 * is not equal to an unsigned double-max precision integer
 * 
 * `libj2_j2i_ne_j2u(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ne_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 1;
	return libj2_j2u_ne_j2u(&u, b);
}


/**
 * Compare a signed double-max precision integer
 * against an unsigned double-max precision integer
 * 
 * `libj2_j2i_cmp_j2u(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
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
libj2_j2i_cmp_j2u(const struct libj2_j2i *a, const struct libj2_j2u *b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return -1;
	return libj2_j2u_cmp_j2u(&u, b);
}


/**
 * Check whether an unsigned double-max precision integer
 * is less than a signed double-max precision integer
 * 
 * `libj2_j2u_lt_j2i(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_lt_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 0;
	return libj2_j2u_lt_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer is less
 * than or equal to a signed double-max precision integer
 * 
 * `libj2_j2u_le_j2i(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_le_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 0;
	return libj2_j2u_le_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is greater than a signed double-max precision integer
 * 
 * `libj2_j2u_gt_j2i(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_gt_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 1;
	return libj2_j2u_gt_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer is
 * greater than or equal to a signed double-max precision integer
 * 
 * `libj2_j2u_ge_j2i(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_ge_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 1;
	return libj2_j2u_ge_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is equal to a signed double-max precision integer
 * 
 * `libj2_j2u_eq_j2i(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_eq_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 0;
	return libj2_j2u_eq_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is not equal to a signed double-max precision integer
 * 
 * `libj2_j2u_ne_j2i(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_ne_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 1;
	return libj2_j2u_ne_j2u(a, &u);
}


/**
 * Compare an unsigned double-max precision integer
 * against a signed double-max precision integer
 * 
 * `libj2_j2u_cmp_j2i(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
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
libj2_j2u_cmp_j2i(const struct libj2_j2u *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return +1;
	return libj2_j2u_cmp_j2u(a, &u);
}


/**
 * Check whether a signed max precision integer
 * is less than an unsigned double-max precision integer
 * 
 * `libj2_ji_lt_j2u(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_lt_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? 1 : libj2_ju_lt_j2u((uintmax_t)a, b);
}


/**
 * Check whether a signed max precision integer is less
 * than or equal to an unsigned double-max precision integer
 * 
 * `libj2_ji_le_j2u(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_le_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? 1 : libj2_ju_le_j2u((uintmax_t)a, b);
}


/**
 * Check whether a signed max precision integer
 * is greater than an unsigned double-max precision integer
 * 
 * `libj2_ji_gt_j2u(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_gt_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? 0 : libj2_ju_gt_j2u((uintmax_t)a, b);
}


/**
 * Check whether a signed max precision integer is greater
 * than or equal to an unsigned double-max precision integer
 * 
 * `libj2_ji_ge_j2u(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_ge_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? 0 : libj2_ju_ge_j2u((uintmax_t)a, b);
}


/**
 * Check whether a signed max precision integer
 * is equal to an unsigned double-max precision integer
 * 
 * `libj2_ji_eq_j2u(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_eq_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? 0 : libj2_ju_eq_j2u((uintmax_t)a, b);
}


/**
 * Check whether a signed max precision integer
 * is not equal to an unsigned double-max precision integer
 * 
 * `libj2_ji_ne_j2u(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_ne_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? 1 : libj2_ju_ne_j2u((uintmax_t)a, b);
}


/**
 * Compare a signed max precision integer
 * against an unsigned double-max precision integer
 * 
 * `libj2_ji_cmp_j2u(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
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
libj2_ji_cmp_j2u(intmax_t a, const struct libj2_j2u *b)
{
	return a < 0 ? -1 : libj2_ju_cmp_j2u((uintmax_t)a, b);
}


/**
 * Check whether an unsigned double-max precision integer
 * is less than a signed max precision integer
 * 
 * `libj2_ju_lt_j2i(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ju_lt_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 0;
	return libj2_ju_lt_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is less than or equal to a signed max precision integer
 * 
 * `libj2_ju_le_j2i(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ju_le_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 0;
	return libj2_ju_le_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is greater than a signed max precision integer
 * 
 * `libj2_ju_gt_j2i(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ju_gt_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 1;
	return libj2_ju_gt_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer is
 * greater than or equal to a signed max precision integer
 * 
 * `libj2_ju_ge_j2i(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ju_ge_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 1;
	return libj2_ju_ge_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is equal to a signed max precision integer
 * 
 * `libj2_ju_eq_j2i(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ju_eq_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 0;
	return libj2_ju_eq_j2u(a, &u);
}


/**
 * Check whether an unsigned double-max precision integer
 * is not equal to a signed max precision integer
 * 
 * `libj2_ju_ne_j2i(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ju_ne_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return 1;
	return libj2_ju_ne_j2u(a, &u);
}


/**
 * Compare an unsigned double-max precision integer
 * against a signed max precision integer
 * 
 * `libj2_ju_cmp_j2i(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
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
libj2_ju_cmp_j2i(uintmax_t a, const struct libj2_j2i *b)
{
	struct libj2_j2u u = {.high = b->high, .low = b->low};
	if (libj2_j2i_is_negative(b))
		return +1;
	return libj2_ju_cmp_j2u(a, &u);
}


/**
 * Check whether a signed double-max precision integer
 * is less than an unsigned max precision integer
 * 
 * `libj2_j2i_lt_ju(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_lt_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 1;
	return libj2_j2u_lt_ju(&u, b);
}


/**
 * Check whether a signed double-max precision integer is less
 * than or equal to an unsigned max precision integer
 * 
 * `libj2_j2i_le_ju(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_le_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 1;
	return libj2_j2u_le_ju(&u, b);
}


/**
 * Check whether a signed double-max precision integer
 * is greater than an unsigned max precision integer
 * 
 * `libj2_j2i_gt_ju(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_gt_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 0;
	return libj2_j2u_gt_ju(&u, b);
}


/**
 * Check whether a signed double-max precision integer is greater
 * than or equal to an unsigned max precision integer
 * 
 * `libj2_j2i_ge_ju(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ge_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 0;
	return libj2_j2u_ge_ju(&u, b);
}


/**
 * Check whether a signed double-max precision integer
 * is equal to an unsigned max precision integer
 * 
 * `libj2_j2i_eq_ju(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_eq_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 0;
	return libj2_j2u_eq_ju(&u, b);
}


/**
 * Check whether a signed double-max precision integer
 * is not equal to an unsigned max precision integer
 * 
 * `libj2_j2i_ne_ju(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_ne_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return 1;
	return libj2_j2u_ne_ju(&u, b);
}


/**
 * Compare a signed double-max precision integer
 * against an unsigned max precision integer
 * 
 * `libj2_j2i_cmp_ju(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
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
libj2_j2i_cmp_ju(const struct libj2_j2i *a, uintmax_t b)
{
	struct libj2_j2u u = {.high = a->high, .low = a->low};
	if (libj2_j2i_is_negative(a))
		return -1;
	return libj2_j2u_cmp_ju(&u, b);
}


/**
 * Check whether an unsigned double-max precision integer
 * is less than a signed max precision integer
 * 
 * `libj2_j2u_lt_ji(a, b)` implements `*a < *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_lt_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? 0 : libj2_j2u_lt_ju(a, (uintmax_t)b);
}


/**
 * Check whether an unsigned double-max precision integer is
 * less than or equal to a signed max precision integer
 * 
 * `libj2_j2u_le_ji(a, b)` implements `*a <= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is less than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_le_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? 0 : libj2_j2u_le_ju(a, (uintmax_t)b);
}


/**
 * Check whether an unsigned double-max precision integer
 * is greater than a signed max precision integer
 * 
 * `libj2_j2u_gt_ji(a, b)` implements `*a > *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_gt_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? 1 : libj2_j2u_gt_ju(a, (uintmax_t)b);
}


/**
 * Check whether an unsigned double-max precision integer is
 * greater than or equal to a signed max precision integer
 * 
 * `libj2_j2u_ge_ji(a, b)` implements `*a >= *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is greater than or equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_ge_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? 1 : libj2_j2u_ge_ju(a, (uintmax_t)b);
}


/**
 * Check whether an unsigned double-max precision integer
 * is equal to a signed max precision integer
 * 
 * `libj2_j2u_eq_ji(a, b)` implements `*a == *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_eq_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? 0 : libj2_j2u_eq_ju(a, (uintmax_t)b);
}


/**
 * Check whether an unsigned double-max precision integer
 * is not equal to a signed max precision integer
 * 
 * `libj2_j2u_ne_ji(a, b)` implements `*a != *b`
 * 
 * @param   a  The left-hand value
 * @param   b  The right-hand value
 * @return     1 if `*a` is not equal to `*b`, 0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2u_ne_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? 1 : libj2_j2u_ne_ju(a, (uintmax_t)b);
}


/**
 * Compare an unsigned double-max precision integer
 * against a signed max precision integer
 * 
 * `libj2_j2u_cmp_ji(a, b)` implements `*a < *b ? -1 : *a > *b ? +1 : 0`,
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
libj2_j2u_cmp_ji(const struct libj2_j2u *a, intmax_t b)
{
	return b < 0 ? +1 : libj2_j2u_cmp_ju(a, (uintmax_t)b);
}
