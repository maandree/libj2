/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_divmod_j2u_to_j2u(a, b, res_q)`
 * implements `*res_q = *a / *b, *a %= *b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * @param  a      The dividend (left-hand), also used as
 *                the output parameter for the remainder
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * 
 * @since  1.0
 */
inline void
libj2_j2u_divmod_j2u_to_j2u(struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res_q)
{
	struct libj2_j2u q = {0, 0};
	struct libj2_j2u c;
	const struct libj2_j2u d = *b;
	unsigned e = LIBJ2_J2U_BIT;
	int cmp = libj2_j2u_cmp_j2u(a, b);

	if (cmp <= 0) {
		if (cmp == 0) {
			q.low = 1U;
			libj2_j2u_zero(a);
		}
		goto out;
	}

#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	e = libj2_clz_j2u(b) - libj2_clz_j2u(a) + 1U;
#endif

	while (!libj2_j2u_is_zero(a) && e--) {
		if (libj2_j2u_lsh_to_j2u_overflow(&d, e, &c))
			continue;
		if (libj2_j2u_gt_j2u(&c, a))
			continue;
		if (e < LIBJ2_JU_BIT)
			q.low |= (uintmax_t)1 << e;
		else
			q.high |= (uintmax_t)1 << (e - LIBJ2_JU_BIT);
		libj2_j2u_sub_j2u(a, &c);
	}

out:
	*res_q = q;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_divmod_j2u_to_j2u_j2u(a, b, res_q, res_r)`
 * implements `*res_q = *a / *b, *res_r = *a % *b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * @param  a      The dividend (left-hand)
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * @param  res_r  Output parameter for the remainder
 * 
 * @since  1.0
 */
inline void
libj2_j2u_divmod_j2u_to_j2u_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b,
                                struct libj2_j2u *res_q, struct libj2_j2u *res_r)
{
	if (res_r == b) {
		struct libj2_j2u r = *a;
		libj2_j2u_divmod_j2u_to_j2u(&r, b, res_q);
		*res_r = r;
	} else {
		*res_r = *a;
		libj2_j2u_divmod_j2u_to_j2u(res_r, b, res_q);
	}
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two unsigned
 * double-max precision integers
 * 
 * `libj2_j2u_divmod_j2u(a, b)` implements
 * `t = (uintmax_t)(*a / *b), *a %= *b, t`
 * (using an intermediate variable `t`)
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n; however the high half
 * of the q is discarded in this function's
 * return value
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the remainder
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.0
 */
inline uintmax_t
libj2_j2u_divmod_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u res;
	libj2_j2u_divmod_j2u_to_j2u(a, b, &res);
	return res.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of an unsigned
 * double-max precision integer (dividend) and
 * an unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_divmod_ju(a, b)` implements
 * `t = (uintmax_t)(*a / b), *a %= b, t`
 * (using an intermediate variable `t`)
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n; however the high half
 * of the q is discarded in this function's
 * return value
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the remainder
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.0
 */
inline uintmax_t
libj2_j2u_divmod_ju(struct libj2_j2u *a, uintmax_t b)
{
	uintmax_t q = 0;
	struct libj2_j2u c;
	unsigned e = LIBJ2_J2U_BIT;
	a->high %= b;
	while (a->high && e--) {
		if (libj2_ju_lsh_to_j2u_overflow(b, e, &c))
			continue;
		if (libj2_j2u_gt_j2u(&c, a))
			continue;
		q |= (uintmax_t)1 << e;
		libj2_j2u_sub_j2u(a, &c);
	}
	q += a->low / b;
	a->low %= b;
	return q;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of an unsigned
 * double-max precision integer (dividend) and
 * an unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_divmod_ju_to_j2u(a, b, res_q)`
 * implements `*res_q = *a / b, *a %= b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * @param  a      The dividend (left-hand), also used as
 *                the output parameter for the remainder
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * 
 * @since  1.0
 */
inline void
libj2_j2u_divmod_ju_to_j2u(struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res_q)
{
	res_q->high = a->high / b;
	res_q->low = libj2_j2u_divmod_ju(a, b);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of an unsigned
 * double-max precision integer (dividend) and
 * an unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_divmod_ju_to_j2u_j2u(a, b, res_q, res_r)`
 * implements `*res_q = *a / b, *res_r = *a % b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * @param  a      The dividend (left-hand)
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * @param  res_r  Output parameter for the remainder
 * 
 * @since  1.0
 */
inline void
libj2_j2u_divmod_ju_to_j2u_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res_q, struct libj2_j2u *res_r)
{
	*res_r = *a;
	res_q->high = res_r->high / b;
	res_q->low = libj2_j2u_divmod_ju(res_r, b);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two unsigned
 * double-max precision integers; in this variant
 * of `libj2_j2u_rdivmod_j2u_to_j2u`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2u_rdivmod_j2u_to_j2u(a, b, res_q)`
 * implements `*res_q = *b / *a, *a = *b % *a`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * @param  a      The divisor (right-hand), also used as
 *                the output parameter for the remainder
 * @param  b      The dividend (left-hand)
 * @param  res_q  Output parameter for the quotient
 * 
 * @since  1.0
 */
inline void
libj2_j2u_rdivmod_j2u_to_j2u(struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res_q)
{
	struct libj2_j2u res_r;
	libj2_j2u_divmod_j2u_to_j2u_j2u(b, a, res_q, &res_r);
	*a = res_r;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two unsigned
 * double-max precision integers; in this variant
 * of `libj2_j2u_rdivmod_j2u_to_j2u`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2u_rdivmod_j2u(a, b)` implements
 * `t = (uintmax_t)(*b / *a), *a = *b % *a, t`
 * (using an intermediate variable `t`)
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n; however the high half
 * of the q is discarded in this function's
 * return value
 * 
 * @param   a  The divisor (right-hand), also used as
 *             the output parameter for the remainder
 * @param   b  The dividend (left-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.0
 */
inline uintmax_t
libj2_j2u_rdivmod_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u q;
	libj2_j2u_divmod_j2u_to_j2u_j2u(b, a, &q, a);
	return q.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_div_j2u(a, b)` implements `*a /= *b`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the quotient
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_div_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_j2u_to_j2u(&c, b, a);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_div_j2u_to_j2u(a, b, res)`
 * implements `*res = *a / *b`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the quotient
 * 
 * @since  1.0
 */
inline void
libj2_j2u_div_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_j2u_to_j2u(&c, b, res);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_div_j2u_return(a, b)`
 * implements `(uintmax_t)(*a / *b)`
 * 
 * @param   a  The dividend (left-hand)
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline uintmax_t
libj2_j2u_div_j2u_return(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *a;
	return libj2_j2u_divmod_j2u(&c, b);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers; in this variant
 * of `libj2_j2u_div_j2u`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2u_rdiv_j2u(a, b)` implements `*a = *b / *a`
 * 
 * @param  a  The divisor (right-hand), also used as
 *            the output parameter for the quotient
 * @param  b  The dividend (left-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_rdiv_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *b;
	libj2_j2u_divmod_j2u_to_j2u(&c, a, a);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of an unsigned double-max
 * precision integer (dividend) and an
 * unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_div_ju(a, b)` implements `*a /= b`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the quotient
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_div_ju(struct libj2_j2u *a, uintmax_t b)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_ju_to_j2u(&c, b, a);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of an unsigned double-max
 * precision integer (dividend) and an
 * unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_div_ju_to_j2u(a, b, res)`
 * implements `*res = *a / b`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the quotient
 * 
 * @since  1.0
 */
inline void
libj2_j2u_div_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_ju_to_j2u(&c, b, res);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of an unsigned double-max
 * precision integer (dividend) and an
 * unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_div_ju_return(a, b)`
 * implements `(uintmax_t)(*a / b)`
 * 
 * @param   a  The dividend (left-hand)
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline uintmax_t
libj2_j2u_div_ju_return(const struct libj2_j2u *a, uintmax_t b)
{
	struct libj2_j2u c = *a;
	return libj2_j2u_divmod_ju(&c, b);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of two unsigned double-max precision integers
 * 
 * `libj2_j2u_mod_j2u(a, b)` implements `*a %= *b`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the remainder
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_mod_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	(void) libj2_j2u_divmod_j2u(a, b);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of two unsigned double-max precision integers
 * 
 * `libj2_j2u_mod_j2u_to_j2u(a, b, res)`
 * implements `*res = *a % *b`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the remainder
 * 
 * @since  1.0
 */
inline void
libj2_j2u_mod_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (res == b) {
		struct libj2_j2u r = *a;
		libj2_j2u_mod_j2u(&r, b);
		*res = r;
	} else {
		*res = *a;
		libj2_j2u_mod_j2u(res, b);
	}
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of two unsigned double-max precision integers;
 * in this variant of `libj2_j2u_mod_j2u`, the
 * dividend (left-hand) is the second parameter
 * and the divisor (right-hand) is the first parameter
 * 
 * `libj2_j2u_rmod_j2u_to_j2u(a, b)` implements
 * `*a = *b % *a`
 * 
 * @param  a  The divisor (right-hand), also used as
 *            the output parameter for the remainder
 * @param  b  The dividend (left-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_rmod_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	libj2_j2u_mod_j2u_to_j2u(b, a, a);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of an unsigned double-max precision integer
 * (dividend) and an unsigned max precision
 * integer (divisor)
 * 
 * `libj2_j2u_mod_ju(a, b)` implements `*a %= b`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the remainder
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.0
 */
inline void
libj2_j2u_mod_ju(struct libj2_j2u *a, uintmax_t b)
{
	struct libj2_j2u c;
	unsigned e = LIBJ2_JU_BIT;
	a->high %= b;
	while (a->high && e--) {
		libj2_ju_lsh_to_j2u(b, e, &c);
		if (libj2_j2u_gt_j2u(&c, a))
			continue;
		libj2_j2u_sub_j2u(a, &c);
	}
	a->low %= b;
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of an unsigned double-max precision integer
 * (dividend) and an unsigned max precision
 * integer (divisor)
 * 
 * `libj2_j2u_mod_ju_to_j2u(a, b, res)`
 * implements `*res = *a % b`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the remainder
 * 
 * @since  1.0
 */
inline void
libj2_j2u_mod_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	*res = *a;
	libj2_j2u_mod_ju(res, b);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_div_j2u_underflow(a, b)` implements
 * `t = !!(*a % b), *a /= *b, t`
 * (using an intermediate variable `t`)
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the quotient
 * @param   b  The divisor (right-hand)
 * @return     1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_div_j2u_underflow(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_j2u_to_j2u(&c, b, a);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers
 * 
 * `libj2_j2u_div_j2u_to_j2u_underflow(a, b, res)`
 * implements `*res = *a / *b, !!(a % b)`
 * 
 * @param   a    The dividend (left-hand)
 * @param   b    The divisor (right-hand)
 * @param   res  Output parameter for the quotient
 * @return       1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_div_j2u_to_j2u_underflow(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_j2u_to_j2u(&c, b, res);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two unsigned double-max
 * precision integers; in this variant
 * of `libj2_j2u_div_j2u`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2u_rdiv_j2u_underflow(a, b)` implements
 * `t = !!(*a % *b), *a = *b / *a, t`
 * (using an intermediate variable `t`)
 * 
 * @param   a  The divisor (right-hand), also used as
 *             the output parameter for the quotient
 * @param   b  The dividend (left-hand)
 * @return     1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_rdiv_j2u_underflow(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c = *b;
	libj2_j2u_divmod_j2u_to_j2u(&c, a, a);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of an unsigned double-max
 * precision integer (dividend) and an
 * unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_div_ju_underflow(a, b)` implements
 * `t = !!(a % b), *a /= b, t`
 * (using an intermediate variable `t`)
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the quotient
 * @param   b  The divisor (right-hand)
 * @return     1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_div_ju_underflow(struct libj2_j2u *a, uintmax_t b)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_ju_to_j2u(&c, b, a);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of an unsigned double-max
 * precision integer (dividend) and an
 * unsigned max precision integer (divisor)
 * 
 * `libj2_j2u_div_ju_to_j2u_underflow(a, b, res)`
 * implements `*res = *a / b, !!(a % b)`
 * 
 * @param   a    The dividend (left-hand)
 * @param   b    The divisor (right-hand)
 * @param   res  Output parameter for the quotient
 * @return       1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.0
 */
inline int
libj2_j2u_div_ju_to_j2u_underflow(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	struct libj2_j2u c = *a;
	libj2_j2u_divmod_ju_to_j2u(&c, b, res);
	return c.high || c.low;
}





/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two signed
 * double-max precision integers
 * 
 * `libj2_j2i_divmod_j2i_to_j2i(a, b, res_q)`
 * implements `*res_q = *a / *b, *a %= *b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param  a      The dividend (left-hand), also used as
 *                the output parameter for the remainder
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * 
 * @since  1.1
 */
inline void
libj2_j2i_divmod_j2i_to_j2i(struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res_q)
{
	int a_neg = libj2_j2i_is_negative(a);
	int b_neg = libj2_j2i_is_negative(b);
	struct libj2_j2u u, v, rq;
	if (b_neg)
		libj2_minus_j2i_to_j2u(b, &v);
	else
		libj2_j2i_to_j2u(b, &v);
	if (a_neg)
		libj2_minus_j2i(a);
	libj2_j2i_to_j2u(a, &u);
	libj2_j2u_divmod_j2u_to_j2u(&u, &v, &rq);
	libj2_j2u_to_j2i(&u, a);
	libj2_j2u_to_j2i(&rq, res_q);
	if (a_neg)
		libj2_minus_j2i(a);
	if (a_neg != b_neg)
		libj2_minus_j2i(res_q);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two signed
 * double-max precision integers
 * 
 * `libj2_j2i_divmod_j2i_to_j2i_j2i(a, b, res_q, res_r)`
 * implements `*res_q = *a / *b, *res_r = *a % *b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param  a      The dividend (left-hand)
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * @param  res_r  Output parameter for the remainder
 * 
 * @since  1.1
 */
inline void
libj2_j2i_divmod_j2i_to_j2i_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b,
                                struct libj2_j2i *res_q, struct libj2_j2i *res_r)
{
	if (res_r == b) {
		struct libj2_j2i r = *a;
		libj2_j2i_divmod_j2i_to_j2i(&r, b, res_q);
		*res_r = r;
	} else {
		*res_r = *a;
		libj2_j2i_divmod_j2i_to_j2i(res_r, b, res_q);
	}
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two signed
 * double-max precision integers
 * 
 * `libj2_j2i_divmod_j2i(a, b)` implements
 * `t = (intmax_t)(*a / *b), *a %= *b, t`
 * (using an intermediate variable `t`)
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n; however the high half
 * of the q is discarded in this function's
 * return value
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the remainder
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.1
 */
inline intmax_t
libj2_j2i_divmod_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i q;
	libj2_j2i_divmod_j2i_to_j2i(a, b, &q);
	if (libj2_j2i_is_negative(&q)) {
		libj2_minus_j2i(&q);
		return -(intmax_t)q.low;
	} else {
		return (intmax_t)q.low;
	}
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of a signed
 * double-max precision integer (dividend) and
 * a signed max precision integer (divisor)
 * 
 * `libj2_j2i_divmod_ji(a, b)` implements
 * `t = (intmax_t)(*a / b), *a %= b, t`
 * (using an intermediate variable `t`)
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n; however the high half
 * of the q is discarded in this function's
 * return value
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the remainder
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.1
 */
inline intmax_t
libj2_j2i_divmod_ji(struct libj2_j2i *a, intmax_t b)
{
	int a_neg = libj2_j2i_is_negative(a);
	struct libj2_j2u u;
	uintmax_t v, q;
	if (a_neg)
		libj2_minus_j2i(a);
	if (b < 0)
		v = (uintmax_t)-(b + 1) + 1U;
	else
		v = (uintmax_t)b;
	libj2_j2i_to_j2u(a, &u);
	q = libj2_j2u_divmod_ju(&u, v);
	libj2_j2u_to_j2i(&u, a);
	if (a_neg)
		libj2_minus_j2i(a);
	return a_neg != (b < 0) ? -(intmax_t)q : (intmax_t)q;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of a signed
 * double-max precision integer (dividend) and
 * a signed max precision integer (divisor)
 * 
 * `libj2_j2i_divmod_ji_to_j2i(a, b, res_q)`
 * implements `*res_q = *a / b, *a %= b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param  a      The dividend (left-hand), also used as
 *                the output parameter for the remainder
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * 
 * @since  1.1
 */
inline void
libj2_j2i_divmod_ji_to_j2i(struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res_q)
{
	int a_neg = libj2_j2i_is_negative(a);
	struct libj2_j2u u;
	uintmax_t v;
	if (a_neg)
		libj2_minus_j2i(a);
	if (b < 0)
		v = (uintmax_t)-(b + 1) + 1U;
	else
		v = (uintmax_t)b;
	libj2_j2i_to_j2u(a, &u);
	res_q->high = a->high / v;
	res_q->low = libj2_j2u_divmod_ju(&u, v);
	libj2_j2u_to_j2i(&u, a);
	if (a_neg)
		libj2_minus_j2i(a);
	if (a_neg != (b < 0))
		libj2_minus_j2i(res_q);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of a signed
 * double-max precision integer (dividend) and
 * a signed max precision integer (divisor)
 * 
 * `libj2_j2i_divmod_ji_to_j2i_j2i(a, b, res_q, res_r)`
 * implements `*res_q = *a / b, *res_r = *a % b`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param  a      The dividend (left-hand)
 * @param  b      The divisor (right-hand)
 * @param  res_q  Output parameter for the quotient
 * @param  res_r  Output parameter for the remainder
 * 
 * @since  1.1
 */
inline void
libj2_j2i_divmod_ji_to_j2i_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res_q, struct libj2_j2i *res_r)
{
	int a_neg = libj2_j2i_is_negative(a);
	struct libj2_j2u rr;
	uintmax_t u;
	if (a_neg)
		libj2_minus_j2i_to_j2u(a, &rr);
	else
		libj2_j2i_to_j2u(a, &rr);
	if (b < 0)
		u = (uintmax_t)-(b + 1) + 1U;
	else
		u = (uintmax_t)b;
	res_q->high = rr.high / u;
	res_q->low = libj2_j2u_divmod_ju(&rr, u);
	libj2_j2u_to_j2i(&rr, res_r);
	if (a_neg)
		libj2_minus_j2i(res_r);
	if (a_neg != (b < 0))
		libj2_minus_j2i(res_q);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two signed
 * double-max precision integers; in this variant
 * of `libj2_j2i_rdivmod_j2i_to_j2i`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2i_rdivmod_j2i_to_j2i(a, b, res_q)`
 * implements `*res_q = *b / *a, *a = *b % *a`
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n
 * 
 * Overflows if `libj2_j2i_is_min(b) && libj2_j2i_eq_ji(a, -1)`
 * 
 * @param  a      The divisor (right-hand), also used as
 *                the output parameter for the remainder
 * @param  b      The dividend (left-hand)
 * @param  res_q  Output parameter for the quotient
 * 
 * @since  1.1
 */
inline void
libj2_j2i_rdivmod_j2i_to_j2i(struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res_q)
{
	struct libj2_j2i res_r;
	libj2_j2i_divmod_j2i_to_j2i_j2i(b, a, res_q, &res_r);
	*a = res_r;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, and remainder of two signed
 * double-max precision integers; in this variant
 * of `libj2_j2i_rdivmod_j2i_to_j2i`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2i_rdivmod_j2i(a, b)` implements
 * `t = (intmax_t)(*b / *a), *a = *b % *a, t`
 * (using an intermediate variable `t`)
 * 
 * For the quotient q, and remainder r,
 * dividend n, and divisor d, it will be true
 * that qd + r = n; however the high half
 * of the q is discarded in this function's
 * return value
 * 
 * Overflows if `libj2_j2i_is_min(b) && libj2_j2i_eq_ji(a, -1)`
 * 
 * @param   a  The divisor (right-hand), also used as
 *             the output parameter for the remainder
 * @param   b  The dividend (left-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.1
 */
inline intmax_t
libj2_j2i_rdivmod_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i q;
	libj2_j2i_divmod_j2i_to_j2i_j2i(b, a, &q, a);
	if (libj2_j2i_is_negative(&q)) {
		libj2_minus_j2i(&q);
		return -(intmax_t)q.low;
	} else {
		return (intmax_t)q.low;
	}
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_div_j2i(a, b)` implements `*a /= *b`
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the quotient
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_div_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_j2i_to_j2i(&c, b, a);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_div_j2i_to_j2i(a, b, res)`
 * implements `*res = *a / *b`
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the quotient
 * 
 * @since  1.1
 */
inline void
libj2_j2i_div_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_j2i_to_j2i(&c, b, res);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_div_j2i_return(a, b)`
 * implements `(intmax_t)(*a / *b)`
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param   a  The dividend (left-hand)
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline intmax_t
libj2_j2i_div_j2i_return(const struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i c = *a;
	return libj2_j2i_divmod_j2i(&c, b);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers; in this variant
 * of `libj2_j2i_div_j2i`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2i_rdiv_j2i(a, b)` implements `*a = *b / *a`
 * 
 * Overflows if `libj2_j2i_is_min(b) && libj2_j2i_eq_ji(a, -1)`
 * 
 * @param  a  The divisor (right-hand), also used as
 *            the output parameter for the quotient
 * @param  b  The dividend (left-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_rdiv_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i c = *b;
	libj2_j2i_divmod_j2i_to_j2i(&c, a, a);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of a signed double-max
 * precision integer (dividend) and a
 * signed max precision integer (divisor)
 * 
 * `libj2_j2i_div_ji(a, b)` implements `*a /= b`
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the quotient
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_div_ji(struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_ji_to_j2i(&c, b, a);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of a signed double-max
 * precision integer (dividend) and a
 * signed max precision integer (divisor)
 * 
 * `libj2_j2i_div_ji_to_j2i(a, b, res)`
 * implements `*res = *a / b`
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the quotient
 * 
 * @since  1.1
 */
inline void
libj2_j2i_div_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_ji_to_j2i(&c, b, res);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of a signed double-max
 * precision integer (dividend) and a
 * signed max precision integer (divisor)
 * 
 * `libj2_j2i_div_ji_return(a, b)`
 * implements `(intmax_t)(*a / b)`
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param   a  The dividend (left-hand)
 * @param   b  The divisor (right-hand)
 * @return     The low half of the quotient
 * 
 * @since  1.1
 */
LIBJ2_PURE_ inline intmax_t
libj2_j2i_div_ji_return(const struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i c = *a;
	return libj2_j2i_divmod_ji(&c, b);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of two signed double-max precision integers
 * 
 * `libj2_j2i_mod_j2i(a, b)` implements `*a %= *b`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the remainder
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mod_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	(void) libj2_j2i_divmod_j2i(a, b);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of two signed double-max precision integers
 * 
 * `libj2_j2i_mod_j2i_to_j2i(a, b, res)`
 * implements `*res = *a % *b`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the remainder
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mod_j2i_to_j2i(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	if (res == b) {
		struct libj2_j2i r = *a;
		libj2_j2i_mod_j2i(&r, b);
		*res = r;
	} else {
		*res = *a;
		libj2_j2i_mod_j2i(res, b);
	}
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of two signed double-max precision integers;
 * in this variant of `libj2_j2i_mod_j2i`, the
 * dividend (left-hand) is the second parameter
 * and the divisor (right-hand) is the first parameter
 * 
 * `libj2_j2i_rmod_j2i_to_j2i(a, b)` implements
 * `*a = *b % *a`
 * 
 * @param  a  The divisor (right-hand), also used as
 *            the output parameter for the remainder
 * @param  b  The dividend (left-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_rmod_j2i(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	libj2_j2i_mod_j2i_to_j2i(b, a, a);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of a signed double-max precision integer
 * (dividend) and a signed max precision
 * integer (divisor)
 * 
 * `libj2_j2i_mod_ji(a, b)` implements `*a %= b`
 * 
 * @param  a  The dividend (left-hand), also used as
 *            the output parameter for the remainder
 * @param  b  The divisor (right-hand)
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mod_ji(struct libj2_j2i *a, intmax_t b)
{
	int a_neg = libj2_j2i_is_negative(a);
	struct libj2_j2u u;
	uintmax_t v;
	if (a_neg)
		libj2_minus_j2i(a);
	if (b < 0)
		v = (uintmax_t)-(b + 1) + 1U;
	else
		v = (uintmax_t)b;
	libj2_j2i_to_j2u(a, &u);
	libj2_j2u_mod_ju(&u, v);
	libj2_j2u_to_j2i(&u, a);
	if (a_neg)
		libj2_minus_j2i(a);
}


/**
 * Calculate the integer remainder, for integer
 * division with the quotient rounded towards zero,
 * of a signed double-max precision integer
 * (dividend) and a signed max precision
 * integer (divisor)
 * 
 * `libj2_j2i_mod_ji_to_j2i(a, b, res)`
 * implements `*res = *a % b`
 * 
 * @param  a    The dividend (left-hand)
 * @param  b    The divisor (right-hand)
 * @param  res  Output parameter for the remainder
 * 
 * @since  1.1
 */
inline void
libj2_j2i_mod_ji_to_j2i(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	*res = *a;
	libj2_j2i_mod_ji(res, b);
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_div_j2i_underflow(a, b)` implements
 * `t = !!(*a % b), *a /= *b, t`
 * (using an intermediate variable `t`)
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the quotient
 * @param   b  The divisor (right-hand)
 * @return     1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_div_j2i_underflow(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_j2i_to_j2i(&c, b, a);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers
 * 
 * `libj2_j2i_div_j2i_to_j2i_underflow(a, b, res)`
 * implements `*res = *a / *b, !!(a % b)`
 * 
 * @param   a    The dividend (left-hand)
 * @param   b    The divisor (right-hand)
 * @param   res  Output parameter for the quotient
 * @return       1 if the remainder is non-zero, 0 otherwise
 * 
 * Overflows if `libj2_j2i_is_min(a) && libj2_j2i_eq_ji(b, -1)`
 * 
 * @since  1.1
 */
inline int
libj2_j2i_div_j2i_to_j2i_underflow(const struct libj2_j2i *a, const struct libj2_j2i *b, struct libj2_j2i *res)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_j2i_to_j2i(&c, b, res);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of two signed double-max
 * precision integers; in this variant
 * of `libj2_j2i_div_j2i`, the dividend
 * (left-hand) is the second parameter and the
 * divisor (right-hand) is the first parameter
 * 
 * `libj2_j2i_rdiv_j2i_underflow(a, b)` implements
 * `t = !!(*a % *b), *a = *b / *a, t`
 * (using an intermediate variable `t`)
 * 
 * Overflows if `libj2_j2i_is_min(b) && libj2_j2i_eq_ji(a, -1)`
 * 
 * @param   a  The divisor (right-hand), also used as
 *             the output parameter for the quotient
 * @param   b  The dividend (left-hand)
 * @return     1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_rdiv_j2i_underflow(struct libj2_j2i *a, const struct libj2_j2i *b)
{
	struct libj2_j2i c = *b;
	libj2_j2i_divmod_j2i_to_j2i(&c, a, a);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of a signed double-max
 * precision integer (dividend) and a
 * signed max precision integer (divisor)
 * 
 * `libj2_j2i_div_ji_underflow(a, b)` implements
 * `t = !!(a % b), *a /= b, t`
 * (using an intermediate variable `t`)
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param   a  The dividend (left-hand), also used as
 *             the output parameter for the quotient
 * @param   b  The divisor (right-hand)
 * @return     1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_div_ji_underflow(struct libj2_j2i *a, intmax_t b)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_ji_to_j2i(&c, b, a);
	return c.high || c.low;
}


/**
 * Calculate the integer quotient, rounded
 * towards zero, of a signed double-max
 * precision integer (dividend) and a
 * signed max precision integer (divisor)
 * 
 * `libj2_j2i_div_ji_to_j2i_underflow(a, b, res)`
 * implements `*res = *a / b, !!(a % b)`
 * 
 * Overflows if `libj2_j2i_is_min(a) && b == -1`
 * 
 * @param   a    The dividend (left-hand)
 * @param   b    The divisor (right-hand)
 * @param   res  Output parameter for the quotient
 * @return       1 if the remainder is non-zero, 0 otherwise
 * 
 * @since  1.1
 */
inline int
libj2_j2i_div_ji_to_j2i_underflow(const struct libj2_j2i *a, intmax_t b, struct libj2_j2i *res)
{
	struct libj2_j2i c = *a;
	libj2_j2i_divmod_ji_to_j2i(&c, b, res);
	return c.high || c.low;
}
