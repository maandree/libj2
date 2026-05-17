/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the unsigned double-max precision integer
 * product of two unsigned max precision integers
 * 
 * `libj2_ju_mul_ju_to_j2u(a, b, res)` implements
 * `*res = a * b`, where `a` and `b` are converted
 * into `struct libj2_j2u`'s
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.0
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
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
 * max precision integer (multiplicand)
 * 
 * `libj2_j2u_mul_ju_to_j2u(a, b)` implements `*a *= b`,
 * where `b` are converted into an `struct libj2_j2u`
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 * 
 * @since  1.0
 */
inline void
libj2_j2u_mul_ju(struct libj2_j2u *a, uintmax_t b)
{
	uintmax_t c = a->high * b;
	libj2_ju_mul_ju_to_j2u(a->low, b, a);
	a->high += c;
}


/**
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
 * max precision integer (multiplicand)
 * 
 * `libj2_j2u_mul_ju_to_j2u(a, b, res)` implements
 * `*res = *a * b`, where `b` are converted into
 * an `struct libj2_j2u`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.0
 */
inline void
libj2_j2u_mul_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_mul_ju(res, b);
}


/**
 * Calculate the product of a signed max
 * precision integer (multiplier) and a signed
 * double-max precision integer (multiplicand)
 * 
 * `libj2_ju_mul_j2u_to_j2u(a, b, res)` implements
 * `*res = a * *b`, where `a` are converted into
 * an `struct libj2_j2u`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.0
 */
inline void
libj2_ju_mul_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	*res = *b;
	libj2_j2u_mul_ju(res, a);
}


/**
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
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
 * 
 * @since  1.0
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
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
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
 * 
 * @since  1.0
 */
inline int
libj2_j2u_mul_ju_to_j2u_overflow(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	*res = *a;
	return libj2_j2u_mul_ju_overflow(res, b);
}


/**
 * Calculate the product of a signed max
 * precision integer (multiplier) and a signed
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
 * 
 * @since  1.0
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
 * 
 * @since  1.0
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
 * 
 * @since  1.0
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
 * 
 * @since  1.0
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
 * 
 * @since  1.0
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
 * 
 * @since  1.0
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
 * 
 * @since  1.0
 */
inline int
libj2_j2u_mul_j2u_to_j2u_overflow(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *b;
	*res = *a;
	return libj2_j2u_mul_j2u_overflow_destructive(res, &c);
}


/**
 * Variant of `libj2_j2u_mul_j2u_overflow_p` that
 * that stops the overflow-prediction is costly
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     `LIBJ2_OVERFLOW` (= 1) if the multiplication would overflow,
 *             `LIBJ2_NO_OVERFLOW` (= 0) if the multiplication would not overflow,
 *             or `LIBJ2_OVERFLOW_UNKNOWN` (= +2) if the prediction was not made
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline enum libj2_overflow
libj2_j2u_mul_j2u_overflow_p_quick(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	unsigned lz;

	if (!a->high == !b->high)
		return a->high > 0 ? LIBJ2_OVERFLOW : LIBJ2_NO_OVERFLOW;
	if (!a->high && a->low <= 1U)
		return LIBJ2_NO_OVERFLOW;
	if (!b->high && b->low <= 1U)
		return LIBJ2_NO_OVERFLOW;

	lz = libj2_clz_j2u(a) + libj2_clz_j2u(b);
	if (lz <= LIBJ2_J2U_BIT)
		return LIBJ2_OVERFLOW;
	if (lz > LIBJ2_J2U_BIT - 1U)
		return LIBJ2_NO_OVERFLOW;

	return LIBJ2_OVERFLOW_UNKNOWN;
}


/**
 * Variant of `libj2_j2u_mul_ju_overflow_p` that
 * that stops the overflow-prediction is costly
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     `LIBJ2_OVERFLOW` (= 1) if the multiplication would overflow,
 *             `LIBJ2_NO_OVERFLOW` (= 0) if the multiplication would not overflow,
 *             or `LIBJ2_OVERFLOW_UNKNOWN` (= +2) if the prediction was not made
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline enum libj2_overflow
libj2_j2u_mul_ju_overflow_p_quick(const struct libj2_j2u *a, uintmax_t b)
{
	return libj2_j2u_mul_j2u_overflow_p_quick(a, &(struct libj2_j2u){.high = 0, .low = b});
}


/**
 * Variant of `libj2_ju_mul_j2u_overflow_p` that
 * that stops the overflow-prediction is costly
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     `LIBJ2_OVERFLOW` (= 1) if the multiplication would overflow,
 *             `LIBJ2_NO_OVERFLOW` (= 0) if the multiplication would not overflow,
 *             or `LIBJ2_OVERFLOW_UNKNOWN` (= +2) if the prediction was not made
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline enum libj2_overflow
libj2_ju_mul_j2u_overflow_p_quick(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_mul_ju_overflow_p_quick(b, a);
}


/**
 * Predict whether `libj2_j2u_mul_j2u_overflow_destructive` 
 * `libj2_j2u_mul_j2u_overflow`, or `libj2_j2u_mul_j2u_to_j2u_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_j2u_mul_j2u_overflow_p(a, b)` implements
 * `libj2_j2u_mul_j2u_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner for most cases
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     1 if the multiplication would overflow, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_mul_j2u_overflow_p(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	enum libj2_overflow overflow;
	struct libj2_j2u j2u;
	uintmax_t ju, c;

	overflow = libj2_j2u_mul_j2u_overflow_p_quick(a, b);
	if (overflow != LIBJ2_OVERFLOW_UNKNOWN)
		return (int)overflow;

	if (a->high) {
		j2u = *a;
		ju = b->low;
	} else {
		j2u = *b;
		ju = a->low;
	}

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	if (__builtin_mul_overflow(j2u.high, ju, &c))
		return 1;
#else
	if (j2u.high > UINTMAX_MAX / ju)
		return 1;
	c = j2u.high * ju;
#endif

	libj2_ju_mul_ju_to_j2u(j2u.low, ju, &j2u);
	return j2u.high > UINTMAX_MAX - c;
}


/**
 * Predict whether `libj2_j2u_mul_ju_overflow`
 * or `libj2_j2u_mul_ju_to_j2u_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_j2u_mul_ju_overflow_p(a, b)` implements
 * `libj2_j2u_mul_ju_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner for most cases
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     1 if the multiplication would overflow, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_j2u_mul_ju_overflow_p(const struct libj2_j2u *a, uintmax_t b)
{
	return libj2_j2u_mul_j2u_overflow_p(a, &(struct libj2_j2u){.high = 0, .low = b});
}


/**
 * Predict whether `libj2_ju_mul_j2u_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_ju_mul_j2u_overflow_p(a, b)` implements
 * `libj2_ju_mul_j2u(&(struct libj2_j2u){.high = a->high, .low = a->low}, b)`
 * in an efficient manner for most cases
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     1 if the multiplication would overflow, 0 otherwise
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline int
libj2_ju_mul_j2u_overflow_p(uintmax_t a, const struct libj2_j2u *b)
{
	return libj2_j2u_mul_ju_overflow_p(b, a);
}


/**
 * Variant of `libj2_j2u_mul_j2u_overflow_p` that
 * that performs the multiplication if the
 * overflow-prediction is costly
 * 
 * @param   a        The multiplier
 * @param   b        The multiplicand
 * @param   res      Output parameter for the product
 * @param   res_set  Output parameter for whether `*res` is set,
 *                   if set to 1 when the function returns,
 *                   `*res` will be set to the product,
 *                   if set to 0 when the function returns,
 *                   `*res` will be unmodified;
 *                   will never be set to any other value
 * @return           1 if the multiplication would overflow
 *                   (did overflow), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_mul_j2u_to_j2u_overflow_p(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res, int *res_set)
{
	enum libj2_overflow overflow;

	overflow = libj2_j2u_mul_j2u_overflow_p_quick(a, b);
	if (overflow != LIBJ2_OVERFLOW_UNKNOWN) {
		*res_set = 0;
		return (int)overflow;
	}

	*res_set = 1;
	if (a->high)
		return libj2_j2u_mul_ju_to_j2u_overflow(a, b->low, res);
	else
		return libj2_j2u_mul_ju_to_j2u_overflow(b, a->low, res);
}


/**
 * Variant of `libj2_j2u_mul_ju_overflow_p` that
 * that performs the multiplication if the
 * overflow-prediction is costly
 * 
 * @param   a        The multiplier
 * @param   b        The multiplicand
 * @param   res      Output parameter for the product
 * @param   res_set  Output parameter for whether `*res` is set,
 *                   if set to 1 when the function returns,
 *                   `*res` will be set to the product,
 *                   if set to 0 when the function returns,
 *                   `*res` will be unmodified;
 *                   will never be set to any other value
 * @return           1 if the multiplication would overflow
 *                   (did overflow), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_mul_ju_to_j2u_overflow_p(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res, int *res_set)
{
	return libj2_j2u_mul_j2u_to_j2u_overflow_p(a, &(struct libj2_j2u){.high = 0, .low = b}, res, res_set);
}


/**
 * Variant of `libj2_ju_mul_j2u_overflow_p` that
 * that performs the multiplication if the
 * overflow-prediction is costly
 * 
 * @param   a        The multiplier
 * @param   b        The multiplicand
 * @param   res      Output parameter for the product
 * @param   res_set  Output parameter for whether `*res` is set,
 *                   if set to 1 when the function returns,
 *                   `*res` will be set to the product,
 *                   if set to 0 when the function returns,
 *                   `*res` will be unmodified;
 *                   will never be set to any other value
 * @return           1 if the multiplication would overflow
 *                   (did overflow), 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_ju_mul_j2u_to_j2u_overflow_p(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res, int *res_set)
{
	return libj2_j2u_mul_ju_to_j2u_overflow_p(b, a, res, res_set);
}





/**
 * Calculate the product of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_mul_j2i_overflow(a, b)` implements
 * `*a *= *b` with overflow-detection
 * 
 * @param   a  The multiplier, also used as the
 *             output parameter for the product
 * @param   b  The multiplicand
 * @return     +1 on positive overflow,
 *             -1 on negative overflow,
 *             0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_mul_j2i_overflow(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u, v;
	int overflow, neg = libj2_j2i_is_negative(a);
	if (neg)
		libj2_minus_j2i(a);
	libj2_j2i_to_j2u(a, &u);
	if (a == b) {
		neg = 0;
		overflow = libj2_j2u_mul_j2u_overflow(&u, &u);
	} else {
		if (libj2_j2i_is_negative(b)) {
			neg ^= 1;
			libj2_minus_j2i_to_j2u(b, &v);
		} else {
			libj2_j2i_to_j2u(b, &v);
		}
		overflow = libj2_j2u_mul_j2u_overflow(&u, &v);
	}
	libj2_j2u_to_j2i(&u, a);
	if (neg) {
		if (overflow)
			overflow = -overflow;
		else if (libj2_j2i_is_min(a))
			return 0;
		else if (libj2_j2i_is_negative(a))
			overflow = -1;
		libj2_minus_j2i(a);
	} else if (!overflow) {
		overflow = libj2_j2i_is_negative(a);
	}
	return overflow;
}


/**
 * Calculate the product of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_mul_j2i_to_j2i_overflow(a, b, res)`
 * implements `*res = *a * *b` with overflow-detection
 * 
 * @param   a    The multiplier
 * @param   b    The multiplicand
 * @param   res  Output parameter for the product
 * @return       +1 on positive overflow,
 *               -1 on negative overflow,
 *               0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_mul_j2i_to_j2i_overflow(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	if (a == res) {
		return libj2_j2i_mul_j2i_overflow(res, b);
	} else if (b == res) {
		return libj2_j2i_mul_j2i_overflow(res, a);
	} else {
		*res = *a;
		return libj2_j2i_mul_j2i_overflow(res, b);
	}
}


/**
 * Predict whether `libj2_j2i_mul_j2i_overflow_destructive` 
 * `libj2_j2i_mul_j2i_overflow`, or `libj2_j2i_mul_j2i_to_j2i_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_j2i_mul_j2i_overflow_p(a, b)` implements
 * `libj2_j2i_mul_j2i_to_j2i_overflow(a, b, &(struct libj2_j2i){})`
 * in an efficient manner for most cases
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     +1 if the multiplication would overflow positively,
 *             -1 if the multiplication would overflow negatively,
 *             0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_mul_j2i_overflow_p(const struct libj2_j2i *a, const struct libj2_j2i *b) /* TODO optimised impl */
{
	return libj2_j2i_mul_j2i_to_j2i_overflow(a, b, &(struct libj2_j2i){0, 0});
}


/**
 * Variant of `libj2_j2i_mul_j2i_overflow_p` that
 * that stops the overflow-prediction is costly
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     `LIBJ2_POSITIVE_OVERFLOW` (= +1) if the
 *             multiplication would overflow positively,
 *             `LIBJ2_NEGATIVE_OVERFLOW` (= -1) if the
 *             multiplication would overflow negatively,
 *             `LIBJ2_NO_OVERFLOW` (= 0) if the multiplication
 *             would not overflow,
 *             `LIBJ2_POSITIVE_OVERFLOW_UNKNOWN` (= +2)
 *             if the prediction was not made but the
 *             multiplication could overflow positively, or
 *             `LIBJ2_NEGATIVE_OVERFLOW_UNKNOWN` (= -2)
 *             if the prediction was not made but the
 *             multiplication could overflow negatively
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline enum libj2_overflow
libj2_j2i_mul_j2i_overflow_p_quick(const struct libj2_j2i *a, const struct libj2_j2i *b) /* TODO optimised impl */
{
	int ret = libj2_j2i_mul_j2i_to_j2i_overflow(a, b, &(struct libj2_j2i){0, 0});
	return (enum libj2_overflow)ret;
}


/**
 * Variant of `libj2_j2i_mul_j2i_overflow_p` that
 * that performs the multiplication if the
 * overflow-prediction is costly
 * 
 * @param   a        The multiplier
 * @param   b        The multiplicand
 * @param   res      Output parameter for the product
 * @param   res_set  Output parameter for whether `*res` is set,
 *                   if set to 1 when the function returns,
 *                   `*res` will be set to the product,
 *                   if set to 0 when the function returns,
 *                   `*res` will be unmodified;
 *                   will never be set to any other value
 * @return           +1 if the multiplication would or did overflow positively,
 *                   -1 if the multiplication would or did overflow negatively,
 *                   0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_mul_j2i_to_j2i_overflow_p(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res, int *res_set) /* TODO optimised impl */
{
	*res_set = 1;
	return libj2_j2i_mul_j2i_to_j2i_overflow(a, b, res);
}


/**
 * Calculate the signed double-max precision integer
 * product of two signed max precision integers
 * 
 * `libj2_ji_mul_ji_to_j2i(a, b, res)` implements
 * `*res = a * b`, where `a` and `b` are converted
 * into `struct libj2_j2i`'s
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_ji_mul_ji_to_j2i(intmax_t a, intmax_t b, struct libj2_j2i *res)
{
	int neg = (a < 0) ^ (b < 0);
	uintmax_t u = a < 0 ? (uintmax_t)-(a + 1) + 1U : (uintmax_t)a;
	uintmax_t v = b < 0 ? (uintmax_t)-(b + 1) + 1U : (uintmax_t)b;
	struct libj2_j2u r;
	libj2_ju_mul_ju_to_j2u(u, v, &r);
	libj2_j2u_to_j2i(&r, res);
	if (neg)
		libj2_minus_j2i(res);
}


/**
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
 * max precision integer (multiplicand)
 * 
 * `libj2_j2i_mul_ji_to_j2i(a, b)` implements `*a *= b`,
 * where `b` are converted into an `struct libj2_j2i`
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mul_ji(struct libj2_j2i *a, intmax_t b)
{
	int neg = libj2_j2i_is_negative(a);
	struct libj2_j2u u;
	uintmax_t v;
	if (neg)
		libj2_minus_j2i(a);
	if (b < 0) {
		neg ^= 1;
		v = (uintmax_t)-(b + 1) + 1U;
	} else {
		v = (uintmax_t)b;
	}
	libj2_j2i_to_j2u(a, &u);
	libj2_j2u_mul_ju(&u, v);
	libj2_j2u_to_j2i(&u, a);
	if (neg)
		libj2_minus_j2i(a);
}


/**
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
 * max precision integer (multiplicand)
 * 
 * `libj2_j2i_mul_ji_to_j2i(a, b, res)` implements
 * `*res = *a * b`, where `b` are converted into
 * an `struct libj2_j2i`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mul_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	*res = *a;
	libj2_j2i_mul_ji(res, b);
}


/**
 * Calculate the product of a signed max
 * precision integer (multiplier) and a signed
 * double-max precision integer (multiplicand)
 * 
 * `libj2_ji_mul_j2i_to_j2i(a, b, res)` implements
 * `*res = a * *b`, where `a` are converted into
 * an `struct libj2_j2i`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_ji_mul_j2i_to_j2i(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	libj2_j2i_mul_ji_to_j2i(b, a, res);
}


/**
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
 * max precision integer (multiplicand)
 * 
 * `libj2_j2i_mul_ji_to_overflow(a, b)` implements
 * `*a *= b`, where `b` are converted into an
 * `struct libj2_j2i`, with overflow-detection
 * 
 * @param   a  The multiplier, also used as the
 *             output parameter for the product
 * @param   b  The multiplicand
 * @return     +1 on positive overflow,
 *             -1 on negative overflow,
 *             0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_mul_ji_overflow(struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(b, &t);
	return libj2_j2i_mul_j2i_overflow(a, &t);
}


/**
 * Calculate the product of a signed double-max
 * precision integer (multiplier) and a signed
 * max precision integer (multiplicand)
 * 
 * `libj2_j2i_mul_ji_to_j2i_overflow(a, b, res)`
 * implements `*res = *a * b`, where `b` are
 * converted into an `struct libj2_j2i`, with
 * overflow-detection
 * 
 * @param   a    The multiplier
 * @param   b    The multiplicand
 * @param   res  Output parameter for the product
 * @return       +1 on positive overflow,
 *               -1 on negative overflow,
 *               0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_mul_ji_to_j2i_overflow(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(b, &t);
	return libj2_j2i_mul_j2i_to_j2i_overflow(a, &t, res);
}


/**
 * Calculate the product of a signed max
 * precision integer (multiplier) and a signed
 * double-max precision integer (multiplicand)
 * 
 * `libj2_ji_mul_j2i_to_j2i_overflow(a, b, res)`
 * implements `*res = a * *b`, where `a` are
 * converted into an `struct libj2_j2i`, with
 * overflow-detection
 * 
 * @param   a    The multiplier
 * @param   b    The multiplicand
 * @param   res  Output parameter for the product
 * @return       +1 on positive overflow,
 *               -1 on negative overflow,
 *               0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_ji_mul_j2i_to_j2i_overflow(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	return libj2_j2i_mul_ji_to_j2i_overflow(b, a, res);
}


/**
 * Calculate the product of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_mul_j2i(a, b)` implements `*a *= *b`
 * 
 * @param  a  The multiplier, also used as the
 *            output parameter for the product
 * @param  b  The multiplicand
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mul_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2u u, v;
	int neg = libj2_j2i_is_negative(a);
	if (neg)
		libj2_minus_j2i(a);
	libj2_j2i_to_j2u(a, &u);
	if (a == b) {
		neg = 0;
		libj2_j2u_mul_j2u(&u, &u);
	} else {
		if (libj2_j2i_is_negative(b)) {
			neg ^= 1;
			libj2_minus_j2i_to_j2u(b, &v);
		} else {
			libj2_j2i_to_j2u(b, &v);
		}
		libj2_j2u_mul_j2u(&u, &v);
	}
	libj2_j2u_to_j2i(&u, a);
	if (neg)
		libj2_minus_j2i(a);
}


/**
 * Calculate the product of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_mul_j2i_to_j2i(a, b, res)`
 * implements `*res = *a * *b`
 * 
 * @param  a    The multiplier
 * @param  b    The multiplicand
 * @param  res  Output parameter for the product
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mul_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	if (a == res) {
	common:
		libj2_j2i_mul_j2i(res, b);
	} else if (b == res) {
		b = a;
		goto common;
	} else if (a == b) {
		struct libj2_j2u u, r;
		if (libj2_j2i_is_negative(a)) {
			libj2_minus_j2i_to_j2u(a, &r);
			libj2_j2u_mul_j2u(&r, &r);
		} else {
			libj2_j2i_to_j2u(a, &u);
			libj2_j2u_mul_j2u_to_j2u(&u, &u, &r);
		}
		libj2_j2u_to_j2i(&r, res);
	} else {
		*res = *a;
		goto common;
	}
}


/**
 * Variant of `libj2_j2i_mul_ji_overflow_p` that
 * that stops the overflow-prediction is costly
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     `LIBJ2_OVERFLOW` (= 1) if the multiplication would overflow,
 *             `LIBJ2_NO_OVERFLOW` (= 0) if the multiplication would not overflow,
 *             or `LIBJ2_OVERFLOW_UNKNOWN` (= +2) if the prediction was not made
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline enum libj2_overflow
libj2_j2i_mul_ji_overflow_p_quick(const struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(b, &t);
	return libj2_j2i_mul_j2i_overflow_p_quick(a, &t);
}


/**
 * Variant of `libj2_ji_mul_j2i_overflow_p` that
 * that stops the overflow-prediction is costly
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     `LIBJ2_OVERFLOW` (= 1) if the multiplication would overflow,
 *             `LIBJ2_NO_OVERFLOW` (= 0) if the multiplication would not overflow,
 *             or `LIBJ2_OVERFLOW_UNKNOWN` (= +2) if the prediction was not made
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline enum libj2_overflow
libj2_ji_mul_j2i_overflow_p_quick(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_mul_ji_overflow_p_quick(b, a);
}


/**
 * Predict whether `libj2_j2i_mul_ji_overflow`
 * or `libj2_j2i_mul_ji_to_j2i_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_j2i_mul_ji_overflow_p(a, b)` implements
 * `libj2_j2i_mul_ji_to_j2i_overflow(a, b, &(struct libj2_j2i){})`
 * in an efficient manner for most cases
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     +1 if the multiplication would overflow positively,
 *             -1 if the multiplication would overflow negatively,
 *             0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_j2i_mul_ji_overflow_p(const struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(b, &t);
	return libj2_j2i_mul_j2i_overflow_p(a, &t);
}


/**
 * Predict whether `libj2_ji_mul_j2i_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_ji_mul_j2i_overflow_p(a, b)` implements
 * `libj2_ji_mul_j2i(&(struct libj2_j2i){.high = a->high, .low = a->low}, b)`
 * in an efficient manner for most cases
 * 
 * @param   a  The multiplier
 * @param   b  The multiplicand
 * @return     +1 if the multiplication would overflow positively,
 *             -1 if the multiplication would overflow negatively,
 *             0 otherwise
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline int
libj2_ji_mul_j2i_overflow_p(intmax_t a, const struct libj2_j2i *b)
{
	return libj2_j2i_mul_ji_overflow_p(b, a);
}


/**
 * Variant of `libj2_j2i_mul_ji_overflow_p` that
 * that performs the multiplication if the
 * overflow-prediction is costly
 * 
 * @param   a        The multiplier
 * @param   b        The multiplicand
 * @param   res      Output parameter for the product
 * @param   res_set  Output parameter for whether `*res` is set,
 *                   if set to 1 when the function returns,
 *                   `*res` will be set to the product,
 *                   if set to 0 when the function returns,
 *                   `*res` will be unmodified;
 *                   will never be set to any other value
 * @return           +1 if the multiplication would or did overflow positively,
 *                   -1 if the multiplication would or did overflow negatively,
 *                   0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_mul_ji_to_j2i_overflow_p(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res, int *res_set)
{
	struct libj2_j2i t;
	libj2_ji_to_j2i(b, &t);
	return libj2_j2i_mul_j2i_to_j2i_overflow_p(a, &t, res, res_set);
}


/**
 * Variant of `libj2_ji_mul_j2i_overflow_p` that
 * that performs the multiplication if the
 * overflow-prediction is costly
 * 
 * @param   a        The multiplier
 * @param   b        The multiplicand
 * @param   res      Output parameter for the product
 * @param   res_set  Output parameter for whether `*res` is set,
 *                   if set to 1 when the function returns,
 *                   `*res` will be set to the product,
 *                   if set to 0 when the function returns,
 *                   `*res` will be unmodified;
 *                   will never be set to any other value
 * @return           +1 if the multiplication would or did overflow positively,
 *                   -1 if the multiplication would or did overflow negatively,
 *                   0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_ji_mul_j2i_to_j2i_overflow_p(intmax_t a, const struct libj2_j2i *b, struct libj2_j2i *res, int *res_set)
{
	return libj2_j2i_mul_ji_to_j2i_overflow_p(b, a, res, res_set);
}
