/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the sum of an unsigned double-max precision
 * integer and an unsigned max precision integer
 * 
 * `libj2_j2u_add_ju(a, b)` implements `*a += b`
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.0
 */
inline void
libj2_j2u_add_ju(struct libj2_j2u *a, uintmax_t b)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(a->low, b, &a->low))
		a->high += 1U;
#else
	if (a->low > UINTMAX_MAX - b)
		a->high += 1U;
	a->low += b;
#endif
}


/**
 * Calculate the sum of an unsigned double-max precision
 * integer and an unsigned max precision integer
 * 
 * `libj2_j2u_add_ju_overflow(a, b)` implements `*a += b`
 * with overflow-detection
 * 
 * @param   a  The augend, and output parameter for the sum
 * @param   b  The addend
 * @return     1 on overflow (the highest set bit in the sum
 *             cannot be stored in the result), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_add_ju_overflow(struct libj2_j2u *a, uintmax_t b)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(a->low, b, &a->low))
		return __builtin_add_overflow(a->high, 1U, &a->high);
	return 0;
#else
	int overflow = 0;
	if (a->low > UINTMAX_MAX - b) {
		if (a->high == UINTMAX_MAX)
			overflow = 1;
		a->high += 1U;
	}
	a->low += b;
	return overflow;
#endif
}


/**
 * Calculate the sum of an unsigned double-max precision
 * integer and an unsigned max precision integer
 * 
 * `libj2_j2u_add_ju_to_j2u(a, b, res)` implements
 * `*res = *a + b`
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.0
 */
inline void
libj2_j2u_add_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	res->high = a->high;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(a->low, b, &res->low))
		res->high += 1U;
#else
	if (a->low > UINTMAX_MAX - b)
		res->high += 1U;
	res->low = a->low + b;
#endif
}


/**
 * Calculate the sum of an unsigned max precision
 * integer and an unsigned double-max precision integer
 * 
 * `libj2_ju_add_j2u_to_j2u(a, b, res)` implements
 * `*res = a + *b`
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.0
 */
inline void
libj2_ju_add_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_add_ju_to_j2u(b, a, res);
}


/**
 * Calculate the sum of an unsigned double-max precision
 * integer and an unsigned max precision integer
 * 
 * `libj2_j2u_add_ju_to_j2u_overflow(a, b, res)` implements
 * `*res = *a + b` with overflow-detection
 * 
 * @param   a    The augend
 * @param   b    The addend
 * @param   res  Output parameter for the sum
 * @return       1 on overflow (the highest set bit in the sum
 *               cannot be stored in the result), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_add_ju_to_j2u_overflow(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(a->low, b, &res->low))
		return __builtin_add_overflow(a->high, 1U, &res->high);
	res->high = a->high;
	return 0;
#else
	int overflow = 0;
	res->high = a->high;
	if (a->low > UINTMAX_MAX - b) {
		if (a->high == UINTMAX_MAX)
			overflow = 1;
		res->high += 1U;
	}
	res->low = a->low + b;
	return overflow;
#endif
}


/**
 * Calculate the sum of an unsigned max precision
 * integer and an unsigned double-max precision integer
 * 
 * `libj2_ju_add_j2u_to_j2u_overflow(a, b, res)` implements
 * `*res = a + *b` with overflow-detection
 * 
 * @param   a    The augend
 * @param   b    The addend
 * @param   res  Output parameter for the sum
 * @return       1 on overflow (the highest set bit in the sum
 *               cannot be stored in the result), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_ju_add_j2u_to_j2u_overflow(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	return libj2_j2u_add_ju_to_j2u_overflow(b, a, res);
}


/**
 * Calculate the sum, as an unsigned double-max precision
 * integer, of two unsigned max precision integers
 * 
 * `libj2_ju_add_ju_to_j2u(a, b, res)` implements
 * `*res = a + b`, where `a` and `b` are converted to
 * `struct libj2_j2u`'s
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.0
 */
inline void
libj2_ju_add_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	res->high = __builtin_add_overflow(a, b, &res->low) ? 1U : 0U;
#else
	res->high = (a > UINTMAX_MAX - b);
	res->low = a + b;
#endif
}


/**
 * Calculate the sum of two unsigned double-max precision
 * integers
 * 
 * `libj2_j2u_add_j2u(a, b)` implements `*a += *b`
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.0
 */
inline void
libj2_j2u_add_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (a == b) {
		a->high <<= 1;
		a->high |= a->low >> (LIBJ2_JU_BIT - 1U);
		a->low <<= 1;
	} else {
		libj2_j2u_add_ju(a, b->low);
		a->high += b->high;
	}
}


/**
 * Calculate the sum of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_add_j2u_to_j2u(a, b, res)` implements
 * `*res = *a + *b`
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.0
 */
inline void
libj2_j2u_add_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (a == b) {
		res->high = a->high << 1;
		res->high |= a->low >> (LIBJ2_JU_BIT - 1U);
		res->low = a->low << 1;
	} else if (b == res) {
		libj2_j2u_add_ju_to_j2u(b, a->low, res);
		res->high += a->high;
	} else {
		libj2_j2u_add_ju_to_j2u(a, b->low, res);
		res->high += b->high;
	}
}


/**
 * Calculate the sum of two unsigned double-max precision
 * integers
 * 
 * `libj2_j2u_add_j2u_overflow(a, b)` implements `*a += *b`
 * with overflow-detection
 * 
 * @param   a  The augend, and output parameter for the sum
 * @param   b  The addend
 * @return     1 on overflow (the highest set bit in the sum
 *             cannot be stored in the result), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_add_j2u_overflow(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (a == b) {
		int overflow = (int)(a->high >> (LIBJ2_JU_BIT - 1U));
		a->high <<= 1;
		a->high |= a->low >> (LIBJ2_JU_BIT - 1U);
		a->low <<= 1;
		return overflow;
	} else {
		int overflow = libj2_j2u_add_ju_overflow(a, b->low);
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
		return __builtin_add_overflow(a->high, b->high, &a->high) || overflow;
#else
		if (a->high > UINTMAX_MAX - b->high)
			overflow = 1;
		a->high += b->high;
		return overflow;
#endif
	}
}


/**
 * Calculate the sum of two unsigned double-max precision
 * integers
 * 
 * `libj2_j2u_add_j2u_to_j2u_overflow(a, b, res)` implements
 * `*res = *a + *b` with overflow-detection
 * 
 * @param   a    The augend
 * @param   b    The addend
 * @param   res  Output parameter for the sum
 * @return       1 on overflow (the highest set bit in the sum
 *               cannot be stored in the result), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_add_j2u_to_j2u_overflow(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (a == b) {
		int overflow = (int)(a->high >> (LIBJ2_JU_BIT - 1U));
		res->high = a->high << 1;
		res->high |= a->low >> (LIBJ2_JU_BIT - 1U);
		res->low = a->low << 1;
		return overflow;
	} else if (b == res) {
		int overflow = libj2_j2u_add_ju_to_j2u_overflow(b, a->low, res);
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
		return __builtin_add_overflow(res->high, a->high, &res->high) || overflow;
#else
		if (res->high > UINTMAX_MAX - a->high)
			overflow = 1;
		res->high += a->high;
		return overflow;
#endif
	} else {
		int overflow = libj2_j2u_add_ju_to_j2u_overflow(a, b->low, res);
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
		return __builtin_add_overflow(res->high, b->high, &res->high) || overflow;
#else
		if (res->high > UINTMAX_MAX - b->high)
			overflow = 1;
		res->high += b->high;
		return overflow;
#endif
	}
}


/**
 * Predict whether `libj2_j2u_add_ju_to_j2u_overflow` 
 * or `libj2_j2u_add_ju_overflow` will return a
 * result-overflow signal
 * 
 * `libj2_j2u_add_ju_overflow_p(a, b)` implements
 * `libj2_j2u_add_ju_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The augend
 * @param   b  The addend
 * @return     1 if the addition would overflow, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_add_ju_overflow_p(const struct libj2_j2u *a, uintmax_t b)
{
	return a->low > UINTMAX_MAX - b && a->high == UINTMAX_MAX;
}


/**
 * Predict whether `libj2_ju_add_j2u_to_j2u_overflow` 
 * will return a result-overflow signal
 * 
 * `libj2_ju_add_j2u_overflow_p(a, b)` implements
 * `libj2_ju_add_j2u_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The augend
 * @param   b  The addend
 * @return     1 if the addition would overflow, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_ju_add_j2u_overflow_p(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_add_ju_overflow_p(b, a);
}


/**
 * Predict whether `libj2_j2u_add_j2u_to_j2u_overflow` 
 * or `libj2_j2u_add_j2u_overflow` will return a
 * result-overflow signal
 * 
 * `libj2_j2u_add_j2u_overflow_p(a, b)` implements
 * `libj2_j2u_add_j2u_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The augend
 * @param   b  The addend
 * @return     1 if the addition would overflow, 0 otherwise
 * 
 * @since  1.0 (broken)
 * @since  1.1 (fixed)
 */
LIBJ2_PURE_ inline int
libj2_j2u_add_j2u_overflow_p(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (a == b)
		return (int)(a->high >> (LIBJ2_JU_BIT - 1U));
	else if (libj2_j2u_add_ju_overflow_p(a, b->low))
		return 1;
	else if (a->low > UINTMAX_MAX - b->low)
		return a->high + 1U > UINTMAX_MAX - b->high;
	else
		return a->high > UINTMAX_MAX - b->high;
}





/**
 * Calculate the sum of a signed double-max precision
 * integer and a signed max precision integer
 * 
 * `libj2_j2i_add_ji(a, b)` implements `*a += b`
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.1
 */
inline void
libj2_j2i_add_ji(struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2u u, v;
	if (b < 0) {
		v.high = UINTMAX_MAX;
		v.low = ~(uintmax_t)-(b + 1);
	} else {
		v.high = 0;
		v.low = (uintmax_t)b;
	}
	libj2_j2i_to_j2u(a, &u);
	libj2_j2u_add_j2u(&u, &v);
	libj2_j2u_to_j2i(&u, a);
}


/**
 * Calculate the sum of two signed double-max precision
 * integers
 * 
 * `libj2_j2i_add_j2i(a, b)` implements `*a += *b`
 * 
 * @param  a  The augend, and output parameter for the sum
 * @param  b  The addend
 * 
 * @since  1.1
 */
inline void
libj2_j2i_add_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u, v;
	libj2_j2i_to_j2u(a, &u);
	libj2_j2i_to_j2u(b, &v);
	libj2_j2u_add_j2u(&u, &v);
	libj2_j2u_to_j2i(&u, a);
}


/**
 * Calculate the sum of a signed double-max precision
 * integer and a signed max precision integer
 * 
 * `libj2_j2i_add_ji_to_j2i(a, b, res)` implements
 * `*res = *a + b`
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_j2i_add_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	struct libj2_j2u u, v, r;
	if (b < 0) {
		v.high = UINTMAX_MAX;
		v.low = ~(uintmax_t)-(b + 1);
	} else {
		v.high = 0;
		v.low = (uintmax_t)b;
	}
	libj2_j2i_to_j2u(a, &u);
	libj2_j2u_add_j2u_to_j2u(&u, &v, &r);
	libj2_j2u_to_j2i(&r, res);
}


/**
 * Calculate the sum of two signed double-max precision
 * integers
 * 
 * `libj2_j2i_add_j2i_to_j2i(a, b, res)` implements `*res = *a + *b`
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_j2i_add_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	struct libj2_j2u u, v, r;
	libj2_j2i_to_j2u(a, &u);
	libj2_j2i_to_j2u(b, &v);
	libj2_j2u_add_j2u_to_j2u(&u, &v, &r);
	libj2_j2u_to_j2i(&r, res);
}


/**
 * Calculate the sum, as a signed double-max precision
 * integer, of two signed max precision integers
 * 
 * `libj2_ji_add_ji_to_j2i(a, b, res)` implements
 * `*res = a + b`, where `a` and `b` are converted to
 * `struct libj2_j2i`'s
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_ji_add_ji_to_j2i(intmax_t a, intmax_t b, struct libj2_j2i *res)
{
	struct libj2_j2u u, v, r;
	if (a < 0) {
		u.high = UINTMAX_MAX;
		u.low = ~(uintmax_t)-(a + 1);
	} else {
		u.high = 0;
		u.low = (uintmax_t)a;
	}
	if (b < 0) {
		v.high = UINTMAX_MAX;
		v.low = ~(uintmax_t)-(b + 1);
	} else {
		v.high = 0;
		v.low = (uintmax_t)b;
	}
	libj2_j2u_add_j2u_to_j2u(&u, &v, &r);
	libj2_j2u_to_j2i(&r, res);
}


/**
 * Calculate the sum of a signed max precision
 * integer and a signed double-max precision integer
 * 
 * `libj2_ji_add_j2i_to_j2i(a, b, res)` implements
 * `*res = a + *b`
 * 
 * @param  a    The augend
 * @param  b    The addend
 * @param  res  Output parameter for the sum
 * 
 * @since  1.1
 */
inline void
libj2_ji_add_j2i_to_j2i(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	libj2_j2i_add_ji_to_j2i(b, a, res);
}


/**
 * Predict the result-overflow signal
 * `libj2_j2i_add_j2i_to_j2i_overflow` or
 * `libj2_j2i_add_j2i_overflow` will return
 * 
 * `libj2_j2i_add_j2i_overflow_p(a, b)` implements
 * `libj2_j2i_add_j2i_to_j2i_overflow(a, b, &(struct libj2_j2i){})`
 * in an efficient manner
 * 
 * @param   a  The augend
 * @param   b  The addend
 * @return     +1 if the addition would overflow positively,
 *             -1 if the addition would overflow negatively,
 *             0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_add_j2i_overflow_p(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	if (libj2_j2i_is_positive(a) && libj2_j2i_is_positive(b)) {
		if (a == b)
			return (int)(a->high >> (LIBJ2_JU_BIT - 2U));
		if (a->low > UINTMAX_MAX - b->low)
			return a->high >= (uintmax_t)INTMAX_MAX - b->high;
		else
			return a->high > (uintmax_t)INTMAX_MAX - b->high;
	} else if (libj2_j2i_is_negative(a) && libj2_j2i_is_negative(b)) {
		if (a == b)
			return ~a->high >> (LIBJ2_JU_BIT - 2U) ? -1 : 0;
		if (a->low > UINTMAX_MAX - b->low)
			return a->high + b->high + 1U < ~(uintmax_t)INTMAX_MAX ? -1 : 0;
		else
			return a->high + b->high < ~(uintmax_t)INTMAX_MAX ? -1 : 0;
	} else {
		return 0;
	}
}


/**
 * Predict the result-overflow signal
 * `libj2_j2i_add_ji_to_j2i_overflow` or
 * `libj2_j2i_add_ji_overflow` will return
 * 
 * `libj2_j2i_add_ji_overflow_p(a, b)` implements
 * `libj2_j2i_add_ji_to_j2i_overflow(a, b, &(struct libj2_j2i){})`
 * in an efficient manner
 * 
 * @param   a  The augend
 * @param   b  The addend
 * @return     +1 if the addition would overflow positively,
 *             -1 if the addition would overflow negatively,
 *             0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_add_ji_overflow_p(const struct libj2_j2i *a, intmax_t b)
{
	if (b > 0 && libj2_j2i_is_positive(a)) {
		if (a->low > UINTMAX_MAX - (uintmax_t)b)
			return a->high >= (uintmax_t)INTMAX_MAX;
		else
			return a->high > (uintmax_t)INTMAX_MAX;
	} else if (b < 0 && libj2_j2i_is_negative(a)) {
		if (a->low > UINTMAX_MAX - ~(uintmax_t)-(b + 1))
			return a->high < ~(uintmax_t)INTMAX_MAX ? -1 : 0;
		else
			return a->high <= ~(uintmax_t)INTMAX_MAX ? -1 : 0;
	} else {
		return 0;
	}
}


/**
 * Predict the result-overflow signal
 * `libj2_ji_add_j2i_to_j2i_overflow` will return
 * 
 * `libj2_ji_add_j2i_overflow_p(a, b)` implements
 * `libj2_ji_add_j2i_to_j2i_overflow(a, b, &(struct libj2_j2i){})`
 * in an efficient manner
 * 
 * @param   a  The augend
 * @param   b  The addend
 * @return     +1 if the addition would overflow positively,
 *             -1 if the addition would overflow negatively,
 *             0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_add_j2i_overflow_p(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_add_ji_overflow_p(b, a);
}


/**
 * Calculate the sum of a signed double-max precision
 * integer and a signed max precision integer
 * 
 * `libj2_j2i_add_ji_overflow(a, b)` implements `*a += b`
 * with overflow-detection
 * 
 * @param   a  The augend, and output parameter for the sum
 * @param   b  The addend
 * @return     +1 on positive overflow,
 *             -1 on negative overflow,
 *             0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_add_ji_overflow(struct libj2_j2i *a, intmax_t b)
{
	int overflow = libj2_j2i_add_ji_overflow_p(a, b);
	libj2_j2i_add_ji(a, b);
	return overflow;
}


/**
 * Calculate the sum of two signed double-max precision
 * integers
 * 
 * `libj2_j2i_add_j2i_overflow(a, b)` implements `*a += *b`
 * with overflow-detection
 * 
 * @param   a  The augend, and output parameter for the sum
 * @param   b  The addend
 * @return     +1 on positive overflow,
 *             -1 on negative overflow,
 *             0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_add_j2i_overflow(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	int overflow = libj2_j2i_add_j2i_overflow_p(a, b);
	libj2_j2i_add_j2i(a, b);
	return overflow;
}


/**
 * Calculate the sum of a signed double-max precision
 * integer and a signed max precision integer
 * 
 * `libj2_j2i_add_ji_to_j2i_overflow(a, b, res)` implements
 * `*res = *a + b` with overflow-detection
 * 
 * @param   a    The augend
 * @param   b    The addend
 * @param   res  Output parameter for the sum
 * @return       +1 on positive overflow,
 *               -1 on negative overflow,
 *               0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_add_ji_to_j2i_overflow(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	int overflow = libj2_j2i_add_ji_overflow_p(a, b);
	libj2_j2i_add_ji_to_j2i(a, b, res);
	return overflow;
}


/**
 * Calculate the sum of two signed double-max precision
 * integers
 * 
 * `libj2_j2i_add_j2i_to_j2i_overflow(a, b, res)` implements
 * `*res = *a + *b` with overflow-detection
 * 
 * @param   a    The augend
 * @param   b    The addend
 * @param   res  Output parameter for the sum
 * @return       +1 on positive overflow,
 *               -1 on negative overflow,
 *                0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_add_j2i_to_j2i_overflow(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	int overflow = libj2_j2i_add_j2i_overflow_p(a, b);
	libj2_j2i_add_j2i_to_j2i(a, b, res);
	return overflow;
}


/**
 * Calculate the sum of a signed max precision
 * integer and a signed double-max precision integer
 * 
 * `libj2_ji_add_j2i_to_j2i_overflow(a, b, res)` implements
 * `*res = a + *b` with overflow-detection
 * 
 * @param   a    The augend
 * @param   b    The addend
 * @param   res  Output parameter for the sum
 * @return       +1 on positive overflow,
 *               -1 on negative overflow,
 *                0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_ji_add_j2i_to_j2i_overflow(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	return libj2_j2i_add_ji_to_j2i_overflow(b, a, res);
}





/**
 * Calculate the sum of two unsigned double-max
 * precision integers and a carry flag, and
 * update the carry flag
 *
 * `libj2_j2u_add_j2u_to_j2u_carry(a, b, res, &c)`
 * imeplements `*res = *a + *b + *c` with
 * overflow-detection
 * 
 * @param  a      The augend
 * @param  b      The addend
 * @param  res    Output parameter for the sum
 * @param  carry  Shall point to the value 1 or 0:
 *                the result will be incremented
 *                with the value. When the function
 *                returns, it will be updated to 1
 *                on overflow, and 0 otherwise
 * 
 * @since  1.2
 */
inline void
libj2_j2u_add_j2u_to_j2u_carry(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res, int *carry)
{
	int overflow = libj2_j2u_add_j2u_to_j2u_overflow(a, b, res);
	if (*carry)
		overflow |= libj2_j2u_add_ju_overflow(res, 1u);
	*carry = overflow;
}


/**
 * Calculate the sum of two unsigned double-max
 * precision integers and a carry flag, and
 * update the carry flag
 *
 * `libj2_j2u_add_j2u_carry(a, b, &c)`
 * imeplements `*a = *a + *b + *c` with
 * overflow-detection
 * 
 * @param  a      The augend, and output parameter for the sum
 * @param  b      The addend
 * @param  carry  Shall point to the value 1 or 0:
 *                the result will be incremented
 *                with the value. When the function
 *                returns, it will be updated to 1
 *                on overflow, and 0 otherwise
 * 
 * @since  1.2
 */
inline void
libj2_j2u_add_j2u_carry(struct libj2_j2u *a, const struct libj2_j2u *b, int *carry)
{
	libj2_j2u_add_j2u_to_j2u_carry(a, b, a, carry);
}





/**
 * Calculate the sum of two signed double-max
 * precision integers and a carry flag, and
 * update the carry flag
 *
 * `libj2_j2i_add_j2i_to_j2i_carry(a, b, res, &c)`
 * imeplements `*res = *a + *b + *c` with
 * overflow-detection
 * 
 * @param  a      The augend
 * @param  b      The addend
 * @param  res    Output parameter for the sum
 * @param  carry  Shall point to the value +1, -1, or 0:
 *                the result will be incremented
 *                with the value. When the function
 *                returns, it will be updated to +1
 *                on positive overflow, -1 on negative
 *                overflow, and 0 otherwise
 * 
 * @since  1.2
 */
inline void
libj2_j2i_add_j2i_to_j2i_carry(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res, int *carry)
{
	int overflow = libj2_j2i_add_j2i_to_j2i_overflow(a, b, res);
	if (*carry)
		overflow |= libj2_j2i_add_ji_overflow(res, *carry > 0 ? +1 : -1);
	*carry = overflow;
}


/**
 * Calculate the sum of two signed double-max
 * precision integers and a carry flag, and
 * update the carry flag
 *
 * `libj2_j2i_add_j2i_carry(a, b, &c)`
 * imeplements `*a = *a + *b + *c` with
 * overflow-detection
 * 
 * @param  a      The augend, and output parameter for the sum
 * @param  b      The addend
 * @param  carry  Shall point to the value +1, -1, or 0:
 *                the result will be incremented
 *                with the value. When the function
 *                returns, it will be updated to +1
 *                on positive overflow, -1 on negative
 *                overflow, and 0 otherwise
 * 
 * @since  1.2
 */
inline void
libj2_j2i_add_j2i_carry(struct libj2_j2i *a, const struct libj2_j2i *b, int *carry)
{
	libj2_j2i_add_j2i_to_j2i_carry(a, b, a, carry);
}
