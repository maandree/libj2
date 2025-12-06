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
 * integer, of two unsigned double-max precision integers
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
 * Calculate the sum of two unsigned double-max precision
 * integers
 * 
 * `libj2_j2u_add_j2u_to_j2u(a, b, res)` implements `*res = *a + *b`
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
inline int
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
inline int
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
 * @since  1.0
 */
inline int
libj2_j2u_add_j2u_overflow_p(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (a == b)
		return (int)(a->high >> (LIBJ2_JU_BIT - 1U));
	else if (libj2_j2u_add_ju_overflow_p(a, b->low))
		return 1;
	else
		return a->high > UINTMAX_MAX - b->high;
}
