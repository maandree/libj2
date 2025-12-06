/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the difference between an unsigned
 * double-max precision integer (minuend) and an
 * unsigned max precision integer (subtrahend)
 * 
 * `libj2_j2u_sub_ju(a, b)` implements `*a -= b`
 * 
 * @param  a  The minuend (left-hand), also used as the
 *            output parameter for the difference
 * @param  b  The subtrahend (right-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_sub_ju(struct libj2_j2u *a, uintmax_t b)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_sub_overflow(a->low, b, &a->low))
		a->high -= 1U;
#else
	if (a->low < b)
		a->high -= 1U;
	a->low -= b;
#endif
}


/**
 * Calculate the difference between an unsigned
 * double-max precision integer (minuend) and an
 * unsigned max precision integer (subtrahend)
 * 
 * `libj2_j2u_sub_ju_overflow(a, b)` implements `*a -= b`
 * with overflow-detection
 * 
 * @param   a  The minuend (left-hand), also used as the
 *             output parameter for the difference
 * @param   b  The subtrahend (right-hand)
 * @return     1 if the result overflowed (`b` is greater than `*a`),
 *             so the result wrapped around (actual difference is
 *             negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_sub_ju_overflow(struct libj2_j2u *a, uintmax_t b)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_sub_overflow(a->low, b, &a->low))
		return __builtin_sub_overflow(a->high, 1U, &a->high);
	return 0;
#else
	int overflow = 0;
	if (a->low < b) {
		if (!a->high)
			overflow = 1;
		a->high -= 1U;
	}
	a->low -= b;
	return overflow;
#endif
}


/**
 * Calculate the difference between an unsigned
 * double-max precision integer (minuend) and an
 * unsigned max precision integer (subtrahend)
 * 
 * `libj2_j2u_sub_ju_to_j2u(a, b, res)`
 * implements `*res = *a - b`
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.0
 */
inline void
libj2_j2u_sub_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	res->high = a->high;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_sub_overflow(a->low, b, &res->low))
		res->high -= 1U;
#else
	if (a->low < b)
		res->high -= 1U;
	res->low = a->low - b;
#endif
}


/**
 * Calculate the difference between an unsigned
 * double-max precision integer (minuend) and an
 * unsigned max precision integer (subtrahend)
 * 
 * `libj2_j2u_sub_ju_to_j2u_overflow(a, b, res)`
 * implements `*res = *a - b` with overflow-detection
 * 
 * @param   a    The minuend (left-hand)
 * @param   b    The subtrahend (right-hand)
 * @param   res  Output parameter for the difference
 * @return       1 if the result overflowed (`b` is greater than `*a`),
 *               so the result wrapped around (actual difference is
 *               negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_sub_ju_to_j2u_overflow(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_sub_overflow(a->low, b, &res->low))
		return __builtin_sub_overflow(a->high, 1U, &res->high);
	res->high = a->high;
	return 0;
#else
	int overflow = 0;
	res->high = a->high;
	if (a->low < b) {
		if (!a->high)
			overflow = 1;
		res->high -= 1U;
	}
	res->low = a->low - b;
	return overflow;
#endif
}


/**
 * Calculate the difference between two unsigned
 * max precision integers, as an unsigned double-max
 * precision integer
 * 
 * `libj2_ju_sub_ju_to_j2u_overflow(a, b, res)`
 * implements `*res = a - b`, where `a` and `b`
 * are converted into `struct libj2_j2u`'s
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.0
 */
inline void
libj2_ju_sub_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	res->high = -(uintmax_t)(__builtin_sub_overflow(a, b, &res->low) ? 1U : 0U);
#else
	res->high = -(uintmax_t)(a < b);
	res->low = a - b;
#endif
}


/**
 * Calculate the difference between two unsigned
 * max precision integers, as an unsigned double-max
 * precision integer
 * 
 * `libj2_ju_sub_ju_to_j2u_overflow(a, b, res)`
 * implements `*res = a - b` with overflow-detection,
 * and where `a` and `b` are converted into
 * `struct libj2_j2u`'s
 * 
 * @param   a    The minuend (left-hand)
 * @param   b    The subtrahend (right-hand)
 * @param   res  Output parameter for the difference
 * @return       1 if the result overflowed (`b` is greater than `*a`),
 *               so the result wrapped around (actual difference is
 *               negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_ju_sub_ju_to_j2u_overflow(uintmax_t a, uintmax_t b, struct libj2_j2u *res)
{
	int overflow;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	overflow = __builtin_sub_overflow(a, b, &res->low) ? 1 : 0;
#else
	overflow = a < b;
	res->low = a - b;
#endif
	res->high = -(uintmax_t)overflow;
	return overflow;
}


/**
 * Calculate the difference between two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sub_j2u(a, b)` implements `*a -= *b`
 * 
 * @param  a  The minuend (left-hand), also used
 *            as the output parameter for the difference
 * @param  b  The subtrahend (right-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_sub_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	libj2_j2u_sub_ju(a, b->low);
	a->high -= b->high;
}


/**
 * Calculate the difference between two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sub_j2u_to_j2u(a, b, res)` implements
 * `*res = *a - *b`
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.0
 */
inline void
libj2_j2u_sub_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (a == b) {
		libj2_j2u_zero(res);
	} else if (res == b) {
		libj2_minus_j2u(res);
		libj2_j2u_add_j2u(res, a);
	} else {
		libj2_j2u_sub_ju_to_j2u(a, b->low, res);
		res->high -= b->high;
	}
}


/**
 * Calculate the difference between two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sub_j2u_overflow(a, b)`
 * implements `*a -= *b` with overflow-detection
 * 
 * @param   a  The minuend (left-hand), also used
 *             as the output parameter for the difference
 * @param   b  The subtrahend (right-hand)
 * @return     1 if the result overflowed (`b` is greater than `*a`),
 *             so the result wrapped around (actual difference is
 *             negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_sub_j2u_overflow(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	int overflow = libj2_j2u_sub_ju_overflow(a, b->low);
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	return __builtin_sub_overflow(a->high, b->high, &a->high) || overflow;
#else
	if (a->high < b->high)
		overflow = 1;
	a->high -= b->high;
	return overflow;
#endif
}


/**
 * Calculate the difference between two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_sub_j2u_to_j2u_overflow(a, b, res)`
 * implements `*res = *a - *b` with overflow-detection
 * 
 * @param   a    The minuend (left-hand)
 * @param   b    The subtrahend (right-hand)
 * @param   res  Output parameter for the difference
 * @return       1 if the result overflowed (`b` is greater than `*a`),
 *               so the result wrapped around (actual difference is
 *               negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_sub_j2u_to_j2u_overflow(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (a == b) {
		libj2_j2u_zero(res);
		return 0;
	} else if (res == b) {
		int overflow = libj2_j2u_lt_j2u(a, res);
		libj2_minus_j2u(res);
		libj2_j2u_add_j2u(res, a);
		return overflow;
	} else {
		int overflow = libj2_j2u_sub_ju_to_j2u_overflow(a, b->low, res);
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
		return __builtin_sub_overflow(res->high, b->high, &res->high) || overflow;
#else
		if (res->high < b->high)
			overflow = 1;
		res->high -= b->high;
		return overflow;
#endif
	}
}


/**
 * Calculate the difference between an unsigned
 * max precision integer (minuend) and an unsigned
 * double-max precision integer (subtrahend)
 * 
 * `libj2_ju_sub_j2u_to_j2u(a, b, res)`
 * implements `*res = a - *b`
 * 
 * @param  a    The minuend (left-hand)
 * @param  b    The subtrahend (right-hand)
 * @param  res  Output parameter for the difference
 * 
 * @since  1.0
 */
inline void
libj2_ju_sub_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (res == b) {
		libj2_minus_j2u(res);
		libj2_j2u_add_ju(res, a);
	} else {
		res->high = 0;
		res->low = a;
		libj2_j2u_sub_j2u(res, b);
	}
}


/**
 * Calculate the difference between an unsigned
 * max precision integer (minuend) and an unsigned
 * double-max precision integer (subtrahend)
 * 
 * `libj2_ju_sub_j2u_to_j2u_overflow(a, b, res)`
 * implements `*res = a - *b` with overflow-detection
 * 
 * @param   a    The minuend (left-hand)
 * @param   b    The subtrahend (right-hand)
 * @param   res  Output parameter for the difference
 * @return       1 if the result overflowed (`*b` is greater than `a`),
 *               so the result wrapped around (actual difference is
 *               negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_ju_sub_j2u_to_j2u_overflow(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (res == b) {
		int overflow = b->high || b->low > a;
		libj2_minus_j2u(res);
		libj2_j2u_add_ju(res, a);
		return overflow;
	} else {
		res->high = 0;
		res->low = a;
		return libj2_j2u_sub_j2u_overflow(res, b);
	}
}


/**
 * Calculate the difference between two unsigned
 * max precision integers; in this variant of
 * `libj2_j2u_sub_j2u`, the minuend (left-hand)
 * is the second parameter and the subtrahend
 * (right-hand) is the first parameter
 * 
 * `libj2_j2u_rsub_j2u(a, b, res)` implements
 * `*a = *b - *a`
 * 
 * @param   a    The subtrahend (right-hand), also used as
 *               the output parameter for the difference
 * @param   b    The minuend (left-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_rsub_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	a->high = b->high - a->high;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
        if (__builtin_sub_overflow(b->low, a->low, &a->low))
                a->high -= 1U;
#else
        if (a->low > b->low)
                a->high -= 1U;
        a->low = b->low - a->low;
#endif
}


/**
 * Calculate the difference between two unsigned
 * max precision integers; in this variant of
 * `libj2_j2u_sub_j2u`, the minuend (left-hand)
 * is the second parameter and the subtrahend
 * (right-hand) is the first parameter
 * 
 * `libj2_j2u_rsub_j2u_overflow(a, b, res)`
 * implements `*a = *b - *a` with overflow-detection
 * 
 * @param   a    The subtrahend (right-hand), also used as
 *               the output parameter for the difference
 * @param   b    The minuend (left-hand)
 * @return       1 if the result overflowed (`*a` is greater than `*b`),
 *               so the result wrapped around (actual difference is
 *               negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_rsub_j2u_overflow(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	int overflow;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	overflow = __builtin_sub_overflow(b->high, a->high, &a->high);
	if (__builtin_sub_overflow(b->low, a->low, &a->low))
		overflow |= __builtin_sub_overflow(a->high, 1U, &a->high);
#else
	overflow = b->high < a->high;
	a->high = b->high - a->high;
	if (b->low < a->low) {
		if (!a->high)
			overflow = 1;
		a->high -= 1U;
	}
	a->low = b->low - a->low;
#endif
	return overflow;
}


/**
 * Calculate the difference between an unsigned
 * max precision integer (minuend) and an unsigned
 * double-max precision integer (subtrahend);
 * in this variant of `libj2_j2u_sub_ju`, the
 * minuend (left-hand) is the second parameter
 * and the subtrahend (right-hand) is the first
 * parameter
 * 
 * `libj2_j2u_rsub_ju(a, b, res)` implements `*a = b - *a`
 * 
 * @param  a  The subtrahend (right-hand), also used as
 *            the output parameter for the difference
 * @param  b  The minuend (left-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_rsub_ju(struct libj2_j2u *a, uintmax_t b)
{
	a->high = -a->high;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
        if (__builtin_sub_overflow(b, a->low, &a->low))
                a->high -= 1U;
#else
        if (a->low > b)
                a->high -= 1U;
        a->low = b - a->low;
#endif
}


/**
 * Calculate the difference between an unsigned
 * max precision integer (minuend) and an unsigned
 * double-max precision integer (subtrahend);
 * in this variant of `libj2_j2u_sub_ju`, the
 * minuend (left-hand) is the second parameter
 * and the subtrahend (right-hand) is the first
 * parameter
 * 
 * `libj2_j2u_rsub_ju_overflow(a, b, res)`
 * implements `*a = b - *a` with overflow-detection
 * 
 * @param   a    The subtrahend (right-hand), also used as
 *               the output parameter for the difference
 * @param   b    The minuend (left-hand)
 * @return       1 if the result overflowed (`*a` is greater than `b`),
 *               so the result wrapped around (actual difference is
 *               negative), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_rsub_ju_overflow(struct libj2_j2u *a, uintmax_t b)
{
	int overflow = !!a->high;
	a->high = -a->high;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_sub_overflow(b, a->low, &a->low))
		overflow |= __builtin_sub_overflow(a->high, 1U, &a->high);
#else
	if (a->low > b) {
		if (!a->high)
			overflow = 1;
		a->high -= 1U;
	}
	if (b < a->low)
		overflow = 1;
	a->low = b - a->low;
#endif
	return overflow;
}


/**
 * Predict whether `libj2_j2u_sub_ju_to_j2u_overflow` 
 * or `libj2_j2u_sub_ju_overflow` will return a
 * result-overflow signal
 * 
 * `libj2_j2u_sub_ju_overflow_p(a, b)` implements
 * `libj2_j2u_sub_ju_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The minuend (left-hand)
 * @param   b  The subtrahend (right-hand)
 * @return     1 if the subtraction would overflow, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_sub_ju_overflow_p(const struct libj2_j2u *a, uintmax_t b)
{
	return a->low < b && !a->high;
}


/**
 * Predict whether `libj2_ju_sub_j2u_to_j2u_overflow` 
 * will return a result-overflow signal
 * 
 * `libj2_ju_sub_j2u_overflow_p(a, b)` implements
 * `libj2_ju_sub_j2u_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The minuend (left-hand)
 * @param   b  The subtrahend (right-hand)
 * @return     1 if the subtraction would overflow, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_ju_sub_j2u_overflow_p(uintmax_t a, const struct libj2_j2u *b)
{
	return b->high || b->low > a;
}


/**
 * Predict whether `libj2_ju_sub_ju_to_j2u_overflow` 
 * will return a result-overflow signal
 * 
 * `libj2_ju_sub_ju_overflow_p(a, b)` implements
 * `libj2_ju_sub_ju_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The minuend (left-hand)
 * @param   b  The subtrahend (right-hand)
 * @return     1 if the subtraction would overflow, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_ju_sub_ju_overflow_p(uintmax_t a, uintmax_t b)
{
	return a < b;
}


/**
 * Predict whether `libj2_j2u_sub_j2u_to_j2u_overflow` 
 * or `libj2_j2u_sub_j2u_overflow` will return a
 * result-overflow signal
 * 
 * `libj2_j2u_sub_j2u_overflow_p(a, b)` implements
 * `libj2_j2u_sub_j2u_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The minuend (left-hand)
 * @param   b  The subtrahend (right-hand)
 * @return     1 if the subtraction would overflow, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_sub_j2u_overflow_p(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return libj2_j2u_sub_ju_overflow_p(a, b->low) || a->high < b->high;
}


/**
 * Predict whether `libj2_j2u_rsub_j2u_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_j2u_rsub_j2u_overflow_p(a, b)` implements
 * `libj2_j2u_rsub_j2u_overflow(&(struct libj2_j2u){.high = a->high, .low = a->low}, b)`
 * in an efficient manner
 * 
 * @param   a  The subtrahend (right-hand)
 * @param   b  The minuend (left-hand)
 * @return     1 if the subtraction would overflow, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_rsub_j2u_overflow_p(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return libj2_j2u_sub_j2u_overflow_p(b, a);
}


/**
 * Predict whether `libj2_j2u_rsub_ju_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_j2u_rsub_ju_overflow_p(a, b)` implements
 * `libj2_j2u_rsub_ju_overflow(&(struct libj2_j2u){.high = a->high, .low = a->low}, b)`
 * in an efficient manner
 * 
 * @param   a  The subtrahend (right-hand)
 * @param   b  The minuend (left-hand)
 * @return     1 if the subtraction would overflow, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_rsub_ju_overflow_p(const struct libj2_j2u *a, uintmax_t b)
{
	return libj2_ju_sub_j2u_overflow_p(b, a);
}
