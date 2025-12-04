/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the unsigned double-max precision integer
 * product of two unsigned double-max precision integers
 * 
 * `libj2_ju_mul_ju_to_j2u(a, b, res)` implements
 * `*res = a * b`, where `a` and `b` are converted
 * into `struct libj2_j2u`'s
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 */
inline void
libj2_ju_mul_ju_to_j2u(uintmax_t a, uintmax_t b, struct libj2_j2u *res)
{
	const int n = (int)LIBJ2_JU_BIT / 2;
	uintmax_t a1, a2, b1, b2, c, c1, c2;

	a1 = a >> n;
	b1 = b >> n;
	a2 = a ^ (a1 << n);
	b2 = b ^ (b1 << n);

	res->high = a1 * b1;
	res->low  = a2 * b2;

	c = a1 * b2;
	c1 = c >> n;
	c2 = c ^ (c1 << n);
	c2 <<= n;
	res->high += c1;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(res->low, c2, &res->low))
		res->high += 1U;
#else
	if (res->low > UINTMAX_MAX - c2)
		res->high += 1U;
	res->low += c2;
#endif

	c = a2 * b1;
	c1 = c >> n;
	c2 = c ^ (c1 << n);
	c2 <<= n;
	res->high += c1;
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_add_overflow(res->low, c2, &res->low))
		res->high += 1U;
#else
	if (res->low > UINTMAX_MAX - c2)
		res->high += 1U;
	res->low += c2;
#endif
}


/**
 * Calculate the product of an unsigned double-max
 * precision integer (multiplier) and an unsigned
 * max precision integer (multiplicand)
 * 
 * `libj2_j2u_mul_ju_to_j2u(a, b)` implements `*a *= b`,
 * where `b` are converted into an `struct libj2_j2u`
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 */
inline void
libj2_j2u_mul_ju(struct libj2_j2u *a, uintmax_t b)
{
	uintmax_t c = a->high * b;
	libj2_ju_mul_ju_to_j2u(a->low, b, a);
	a->high += c;
}


/**
 * Calculate the product of an unsigned double-max
 * precision integer (multiplier) and an unsigned
 * max precision integer (multiplicand)
 * 
 * `libj2_j2u_mul_ju_to_j2u(a, b, res)` implements
 * `*res = *a * b`, where `b` are converted into
 * an `struct libj2_j2u`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 */
inline void
libj2_j2u_mul_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_mul_ju(res, b);
}


/**
 * Calculate the product of an unsigned max
 * precision integer (multiplier) and an unsigned
 * double-max precision integer (multiplicand)
 * 
 * `libj2_ju_mul_j2u_to_j2u(a, b, res)` implements
 * `*res = a * *b`, where `a` are converted into
 * an `struct libj2_j2u`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 */
inline void
libj2_ju_mul_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	*res = *b;
	libj2_j2u_mul_ju(res, a);
}


/**
 * Calculate the product of an unsigned double-max
 * precision integer (multiplier) and an unsigned
 * max precision integer (multiplicand)
 * 
 * `libj2_j2u_mul_ju_to_overflow(a, b)` implements
 * `*a *= b`, where `b` are converted into an
 * `struct libj2_j2u`, with overflow-detection
 * 
 * @param   a  The multiplier, also used as the
 *             output parameter for the product
 * @param   b  The multiplicand
 * @return     1 if the result overflowed, 0 otherwise
 */
inline int
libj2_j2u_mul_ju_overflow(struct libj2_j2u *a, uintmax_t b)
{
	int overflow = 0;
	uintmax_t c;

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	overflow |= __builtin_mul_overflow(a->high, b, &c);
#else
	if (b && a->high > UINTMAX_MAX / b)
		overflow = 1;
	c = a->high * b;
#endif

	libj2_ju_mul_ju_to_j2u(a->low, b, a);

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	overflow |= __builtin_add_overflow(a->high, c, &a->high);
#else
	if (a->high > UINTMAX_MAX - c)
		overflow = 1;
	a->high += c;
#endif

	return overflow;
}


/**
 * Calculate the product of an unsigned double-max
 * precision integer (multiplier) and an unsigned
 * max precision integer (multiplicand)
 * 
 * `libj2_j2u_mul_ju_to_j2u_overflow(a, b, res)`
 * implements `*res = *a * b`, where `b` are
 * converted into an `struct libj2_j2u`, with
 * overflow-detection
 * 
 * @param   a    The multiplier
 * @param   b    The multiplicand
 * @param   res  Output parameter for the product
 * @return       1 if the result overflowed, 0 otherwise
 */
inline int
libj2_j2u_mul_ju_to_j2u_overflow(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	*res = *a;
	return libj2_j2u_mul_ju_overflow(res, b);
}


/**
 * Calculate the product of an unsigned max
 * precision integer (multiplier) and an unsigned
 * double-max precision integer (multiplicand)
 * 
 * `libj2_ju_mul_j2u_to_j2u_overflow(a, b, res)`
 * implements `*res = a * *b`, where `a` are
 * converted into an `struct libj2_j2u`, with
 * overflow-detection
 * 
 * @param   a    The multiplier
 * @param   b    The multiplicand
 * @param   res  Output parameter for the product
 * @return       1 if the result overflowed, 0 otherwise
 */
inline int
libj2_ju_mul_j2u_to_j2u_overflow(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	*res = *b;
	return libj2_j2u_mul_ju_overflow(res, a);
}


/**
 * Calculate the product of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_mul_j2u_destructive(a, b)`
 * implements `*a *= *b`, except that `*b`
 * will be arbitrarily modified
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand; will be tainted
 * 
 * `a` and `b` must not be the same pointers
 */
inline void
libj2_j2u_mul_j2u_destructive(struct libj2_j2u *restrict a /* result */, struct libj2_j2u *restrict b /* destructed */)
{
	a->high *= b->low;
	b->high *= a->low;
	b->high += a->high;

	libj2_ju_mul_ju_to_j2u(a->low, b->low, a);
	a->high += b->high;
}


/**
 * Calculate the product of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_mul_j2u(a, b)` implements `*a *= *b`
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 */
inline void
libj2_j2u_mul_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *b;
	libj2_j2u_mul_j2u_destructive(a, &c);
}


/**
 * Calculate the product of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_mul_j2u_overflow_destructive(a, b)`
 * implements `*a *= *b`, except that `*b`
 * will be arbitrarily modified, with
 * overflow-detection
 * 
 * @param   a  The multiplier, also used as the
 *             output parameter for the product
 * @param   b  The multiplicand; will be tainted
 * @return     1 if the result overflowed, 0 otherwise
 * 
 * `a` and `b` must not be the same pointers
 */
inline int
libj2_j2u_mul_j2u_overflow_destructive(struct libj2_j2u *restrict a /* result */, struct libj2_j2u *restrict b /* destructed */)
{
	int overflow = a->high && b->high;

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	overflow |= __builtin_mul_overflow(a->high, b->low, &a->high);
	overflow |= __builtin_mul_overflow(b->high, a->low, &b->high);
	overflow |= __builtin_add_overflow(b->high, a->high, &b->high);
#else
	if (b->low && a->high > UINTMAX_MAX / b->low)
		overflow = 1;
	a->high *= b->low;
	if (a->low && b->high > UINTMAX_MAX / a->low)
		overflow = 1;
	b->high *= a->low;
	if (b->high > UINTMAX_MAX - a->high)
		overflow = 1;
	b->high += a->high;
#endif

	libj2_ju_mul_ju_to_j2u(a->low, b->low, a);

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	overflow |= __builtin_add_overflow(a->high, b->high, &a->high);
#else
	if (a->high > UINTMAX_MAX - b->high)
		overflow = 1;
	a->high += b->high;
#endif

	return overflow;
}


/**
 * Calculate the product of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_mul_j2u_overflow(a, b)` implements
 * `*a *= *b` with overflow-detection
 * 
 * @param   a  The multiplier, also used as the
 *             output parameter for the product
 * @param   b  The multiplicand
 * @return     1 if the result overflowed, 0 otherwise
 */
inline int
libj2_j2u_mul_j2u_overflow(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *b;
	return libj2_j2u_mul_j2u_overflow_destructive(a, &c);
}


/**
 * Calculate the product of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_mul_j2u_to_j2u(a, b, res)`
 * implements `*res = *a * *b`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 */
inline void
libj2_j2u_mul_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *b;
	*res = *a;
	libj2_j2u_mul_j2u_destructive(res, &c);
}

/**
 * Calculate the product of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_mul_j2u_to_j2u_overflow(a, b, res)`
 * implements `*res = *a * *b` with overflow-detection
 * 
 * @param   a    The multiplier
 * @param   b    The multiplicand
 * @param   res  Output parameter for the product
 * @return       1 if the result overflowed, 0 otherwise
 */
inline int
libj2_j2u_mul_j2u_to_j2u_overflow(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *b;
	*res = *a;
	return libj2_j2u_mul_j2u_overflow_destructive(res, &c);
}
