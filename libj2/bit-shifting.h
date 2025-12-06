/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Shift the bits an unsigned double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_lsh(a, b)` implements `*a <<= b`
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2
 * 
 * @param  a  The integer to shift, also used as the
 *            output parameter for the result
 * @param  b  The number of positions to shift each bit
 */
inline void
libj2_j2u_lsh(struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_JU_BIT) {
		if (b >= LIBJ2_J2U_BIT)
			a->high = 0;
		else
			a->high = a->low << (b - LIBJ2_JU_BIT);
		a->low = 0U;
	} else if (b) {
		a->high <<= b;
		a->high |= a->low >> (LIBJ2_JU_BIT - b);
		a->low <<= b;
	}
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_lsh_to_j2u(a, b, res)` implements `*res = *a << b`
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_lsh_to_j2u(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_lsh(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to more signficant positions (left-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_ju_lsh_to_j2u(a, b, res)` implements `*res = a << b`,
 * where `a` is converted to a `struct libj2_j2u`
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2
 * 
 * You can rely on `libj2_ju_lsh_to_j2u(1, LIBJ2_J2U_BIT, res)`
 * overflowing and assigning 0 to `*res`, and thus, subtracting
 * 1 from `*res` afterwards will set all bits; and so,
 * `libj2_ju_lsh_to_j2u(1, n, a), libj2_j2u_sub_j2(a, 1)` will
 * always set the `n` least significant bits in `a` and clear
 * all other bits
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_lsh_to_j2u(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	libj2_ju_to_j2u(a, res);
	libj2_j2u_lsh(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_lsh_overflow(a, b)` implements
 * `(*a << b) >> b == *a ? (*a <<= b, 0) : (*a <<= b, 1)`
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2
 * 
 * @param   a  The integer to shift, also used as the
 *             output parameter for the result
 * @param   b  The number of positions to shift each bit
 * @return     1 if any set bit was discarded because
 *             it was shifted out, 0 otherwise
 */
inline int
libj2_j2u_lsh_overflow(struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_J2U_BIT) {
		int overflow = a->high || a->low;
		a->high = 0;
		a->low = 0;
		return overflow;
	} else if (b > LIBJ2_JU_BIT) {
		int overflow = a->high || a->low >> (LIBJ2_J2U_BIT - b);
		a->high = a->low << (b - LIBJ2_JU_BIT);
		a->low = 0U;
		return overflow;
	} else if (b == LIBJ2_JU_BIT) {
		int overflow = !!a->high;
		a->high = a->low;
		a->low = 0U;
		return overflow;
	} else if (b) {
		int overflow = !!(a->high >> (LIBJ2_JU_BIT - b));
		a->high <<= b;
		a->high |= a->low >> (LIBJ2_JU_BIT - b);
		a->low <<= b;
		return overflow;
	} else {
		return 0;
	}
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to more signficant positions (left-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_lsh_to_j2u_overflow(a, b, res)` implements
 * `*res = *a << b, a != *res >> b`
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2
 * 
 * @param   a    The integer to shift
 * @param   b    The number of positions to shift each bit
 * @param   res  Output parameter for the result
 * @return       1 if any set bit was discarded because
 *               it was shifted out, 0 otherwise
 */
inline int
libj2_j2u_lsh_to_j2u_overflow(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	*res = *a;
	return libj2_j2u_lsh_overflow(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to more signficant positions (left-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_ju_lsh_to_j2u_overflow(a, b, res)` implements
 * `*res = a << b, a != *res >> b`, where `a` is converted
 * to a `struct libj2_j2u`
 * 
 * This is equivalent to multiplying `a` by the `b`th
 * power of 2
 * 
 * @param   a    The integer to shift
 * @param   b    The number of positions to shift each bit
 * @param   res  Output parameter for the result
 * @return       1 if any set bit was discarded because
 *               it was shifted out, 0 otherwise
 */
inline int
libj2_ju_lsh_to_j2u_overflow(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	libj2_ju_to_j2u(a, res);
	return libj2_j2u_lsh_overflow(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to less signficant positions (right-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_rsh(a, b)` implements `*a >>= b`
 * 
 * This is equivalent to dividing `a` by the `b`th
 * power of 2
 * 
 * @param  a  The integer to shift, also used as the
 *            output parameter for the result
 * @param  b  The number of positions to shift each bit
 */
inline void
libj2_j2u_rsh(struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_JU_BIT) {
		if (b >= LIBJ2_J2U_BIT)
			a->low = 0;
		else
			a->low = a->high >> (b - LIBJ2_JU_BIT);
		a->high = 0U;
	} else if (b) {
		a->low >>= b;
		a->low |= a->high << (LIBJ2_JU_BIT - b);
		a->high >>= b;
	}
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to less signficant positions (right-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_rsh_to_j2u(a, b, res)` implements `*res = *a >> b`
 * 
 * This is equivalent to dividing `a` by the `b`th
 * power of 2
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_rsh_to_j2u(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_rsh(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to less signficant positions (right-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_ju_rsh_to_j2u(a, b, res)` implements `*res = a >> b`,
 * where `a` is converted to a `struct libj2_j2u`
 * 
 * This is equivalent to dividing `a` by the `b`th
 * power of 2
 * 
 * @param  a    The integer to shift
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_rsh_to_j2u(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	libj2_ju_to_j2u(a, res);
	libj2_j2u_rsh(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to less signficant positions (right-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_rsh_underflow(a, b)` implements
 * `(*a >> b) << b == *a ? (*a >>= b, 0) : (*a >>= b, 1)`
 * 
 * This is equivalent to dividing `a` by the `b`th
 * power of 2
 * 
 * @param   a  The integer to shift, also used as the
 *             output parameter for the result
 * @param   b  The number of positions to shift each bit
 * @return     1 if any set bit was discarded because
 *             it was shifted out, 0 otherwise
 */
inline int
libj2_j2u_rsh_underflow(struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_J2U_BIT) {
		int underflow = a->high || a->low;
		a->high = 0;
		a->low = 0;
		return underflow;
	} else if (b > LIBJ2_JU_BIT) {
		int underflow = a->low || a->high >> (LIBJ2_J2U_BIT - b);
		a->low = a->high >> (b - LIBJ2_JU_BIT);
		a->high = 0U;
		return underflow;
	} else if (b == LIBJ2_JU_BIT) {
		int underflow = !!a->low;
		a->low = a->high;
		a->high = 0U;
		return underflow;
	} else if (b) {
		int underflow = !!(a->low << (LIBJ2_JU_BIT - b));
		a->low >>= b;
		a->low |= a->high << (LIBJ2_JU_BIT - b);
		a->high >>= b;
		return underflow;
	} else {
		return 0;
	}
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to less signficant positions (right-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_j2u_rsh_to_j2u_underflow(a, b, res)` implements
 * `*res = *a >> b, a != *res << b`
 * 
 * This is equivalent to dividing `a` by the `b`th
 * power of 2
 * 
 * @param   a    The integer to shift
 * @param   b    The number of positions to shift each bit
 * @param   res  Output parameter for the result
 * @return       1 if any set bit was discarded because
 *               it was shifted out, 0 otherwise
 */
inline int
libj2_j2u_rsh_to_j2u_underflow(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	*res = *a;
	return libj2_j2u_rsh_underflow(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to less signficant positions (right-shift)
 * 
 * Bits shifted out of precision will be discarded,
 * and positions without any new bit will be assigned
 * the bit value 0
 * 
 * `libj2_ju_rsh_to_j2u_underflow(a, b, res)` implements
 * `*res = a >> b, a != *res << b`, where `a` is converted
 * to a `struct libj2_j2u`
 * 
 * This is equivalent to dividing `a` by the `b`th
 * power of 2
 * 
 * @param   a    The integer to shift
 * @param   b    The number of positions to shift each bit
 * @param   res  Output parameter for the result
 * @return       1 if any set bit was discarded because
 *               it was shifted out, 0 otherwise
 */
inline int
libj2_ju_rsh_to_j2u_underflow(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	libj2_ju_to_j2u(a, res);
	return libj2_j2u_rsh_underflow(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to more signficant positions
 * 
 * Bits shifted out of precision are wrapped around
 * to the other edge of the bit array
 * 
 * `libj2_j2u_lrot(a, b)` implements
 * `*a = (*a << b) | (*a >> (n - b))`, where
 * `n` is the number of bits in `*a`
 * 
 * @param  a  The integer to rotate, also used as the
 *            output parameter for the result
 * @param  b  The number of positions to shift each bit
 */
inline void
libj2_j2u_lrot(struct libj2_j2u *a, unsigned b)
{
	uintmax_t c;
	b %= LIBJ2_J2U_BIT;
	if (b >= LIBJ2_JU_BIT) {
		b -= LIBJ2_JU_BIT;
		c = a->high;
		a->high = a->low;
		a->low = c;
	}
	if (b) {
		c = a->high;
		a->high <<= b;
		a->high |= a->low >> (LIBJ2_JU_BIT - b);
		a->low <<= b;
		a->low |= c >> (LIBJ2_JU_BIT - b);
	}
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to more signficant positions
 * 
 * Bits shifted out of precision are wrapped around
 * to the other edge of the bit array
 * 
 * `libj2_j2u_lrot_to_j2u(a, b, res)` implements
 * `*res = (*a << b) | (*a >> (n - b))`, where
 * `n` is the number of bits in `*a`
 * 
 * @param  a    The integer to rotate
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_lrot_to_j2u(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_lrot(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to more signficant positions
 * 
 * Bits shifted out of precision are wrapped around
 * to the other edge of the bit array
 * 
 * `libj2_ju_lrot_to_j2u(a, b, res)` implements
 * `*res = (a << b) | (a >> (n - b))`, where
 * `n` is the number of bits in `a`, and where
 * `a` is converted to a `struct libj2_j2u`
 * 
 * @param  a    The integer to rotate
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_lrot_to_j2u(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	libj2_ju_to_j2u(a, res);
	libj2_j2u_lrot(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to less signficant positions
 * 
 * Bits shifted out of precision are wrapped around
 * to the other edge of the bit array
 * 
 * `libj2_j2u_rrot(a, b)` implements
 * `*a = (*a >> b) | (*a << (n - b))`, where
 * `n` is the number of bits in `*a`
 * 
 * @param  a  The integer to rotate, also used as the
 *            output parameter for the result
 * @param  b  The number of positions to shift each bit
 */
inline void
libj2_j2u_rrot(struct libj2_j2u *a, unsigned b)
{
	uintmax_t c;
	b %= LIBJ2_J2U_BIT;
	if (b >= LIBJ2_JU_BIT) {
		b -= LIBJ2_JU_BIT;
		c = a->high;
		a->high = a->low;
		a->low = c;
	}
	if (b) {
		c = a->high;
		a->high >>= b;
		a->high |= a->low << (LIBJ2_JU_BIT - b);
		a->low >>= b;
		a->low |= c << (LIBJ2_JU_BIT - b);
	}
}


/**
 * Shift the bits an unsigned double-max precision
 * integer to less signficant positions
 * 
 * Bits shifted out of precision are wrapped around
 * to the other edge of the bit array
 * 
 * `libj2_j2u_rrot_to_j2u(a, b, res)` implements
 * `*res = (*a >> b) | (*a << (n - b))`, where
 * `n` is the number of bits in `*a`
 * 
 * @param  a    The integer to rotate
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_rrot_to_j2u(const struct libj2_j2u *a, unsigned b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_rrot(res, b);
}


/**
 * Shift the bits an unsigned double-max precision
 * integer, represented by an unsigned max precision
 * integer and whose high part is treated as having
 * the value 0, to less signficant positions
 * 
 * Bits shifted out of precision are wrapped around
 * to the other edge of the bit array
 * 
 * `libj2_ju_rrot_to_j2u(a, b, res)` implements
 * `*res = (a >> b) | (a << (n - b))`, where
 * `n` is the number of bits in `a`, and where
 * `a` is converted to a `struct libj2_j2u`
 * 
 * @param  a    The integer to rotate
 * @param  b    The number of positions to shift each bit
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_rrot_to_j2u(uintmax_t a, unsigned b, struct libj2_j2u *res)
{
	libj2_ju_to_j2u(a, res);
	libj2_j2u_rrot(res, b);
}


/**
 * Predict whether `libj2_j2u_lsh_overflow` or
 * `libj2_j2u_lsh_to_j2u_overflow` will return
 * a result-overflow signal
 * 
 * `libj2_j2u_lsh_overflow_p(a, b)` implements
 * `libj2_j2u_lsh_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The integer to shift (dry-run)
 * @param   b  The number of positions to shift each bit
 * @return     1 if set bit would be be shifted out, 0 otherwise
 */
inline int
libj2_j2u_lsh_overflow_p(const struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_J2U_BIT)
		return a->high || a->low;
	else if (b > LIBJ2_JU_BIT)
		return a->high || a->low >> (LIBJ2_J2U_BIT - b);
	else if (b == LIBJ2_JU_BIT)
		return !!a->high;
	else if (b)
		return !!(a->high >> (LIBJ2_JU_BIT - b));
	else
		return 0;
}


/**
 * Predict whether `libj2_ju_lsh_to_j2u_overflow`
 * will return a result-overflow signal
 * 
 * `libj2_ju_lsh_overflow_p(a, b)` implements
 * `libj2_ju_lsh_to_j2u_overflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The integer to shift (dry-run)
 * @param   b  The number of positions to shift each bit
 * @return     1 if set bit would be be shifted out, 0 otherwise
 */
inline int
libj2_ju_lsh_overflow_p(uintmax_t a, unsigned b)
{
	if (b >= LIBJ2_J2U_BIT)
		return !!a;
	else if (b > LIBJ2_JU_BIT)
		return !!(a >> (LIBJ2_J2U_BIT - b));
	else
		return 0;
}


/**
 * Predict whether `libj2_j2u_rsh_underflow` or
 * `libj2_j2u_rsh_to_j2u_underflow` will return
 * a result-underflow signal
 * 
 * `libj2_j2u_rsh_underflow_p(a, b)` implements
 * `libj2_j2u_rsh_to_j2u_underflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The integer to shift (dry-run)
 * @param   b  The number of positions to shift each bit
 * @return     1 if set bit would be be shifted out, 0 otherwise
 */
inline int
libj2_j2u_rsh_underflow_p(const struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_J2U_BIT)
		return a->high || a->low;
	else if (b > LIBJ2_JU_BIT)
		return a->low || a->high >> (LIBJ2_J2U_BIT - b);
	else if (b == LIBJ2_JU_BIT)
		return !!a->low;
	else if (b)
		return !!(a->low << (LIBJ2_JU_BIT - b));
	else
		return 0;
}


/**
 * Predict whether `libj2_ju_rsh_to_j2u_underflow`
 * will return a result-underflowflow signal
 * 
 * `libj2_ju_rsh_underflow_p(a, b)` implements
 * `libj2_ju_rsh_to_j2u_underflow(a, b, &(struct libj2_j2u){})`
 * in an efficient manner
 * 
 * @param   a  The integer to shift (dry-run)
 * @param   b  The number of positions to shift each bit
 * @return     1 if set bit would be be shifted out, 0 otherwise
 */
inline int
libj2_ju_rsh_underflow_p(uintmax_t a, unsigned b)
{
	if (b >= LIBJ2_JU_BIT)
		return !!a;
	else if (b)
		return !!(a << (LIBJ2_JU_BIT - b));
	else
		return 0;
}
