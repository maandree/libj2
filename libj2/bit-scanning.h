/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Get the number of leading zeroes in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The number of zeroes after the most signficant set
 *             bit in `a`, `LIBJ2_J2U_BIT` if `a` has the value 0
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_clz_j2u(const struct libj2_j2u *a)
{
	uintmax_t x;
	unsigned r, n;
	if (a->high) {
		x = a->high;
		r = 0;
	} else if (a->low) {
		x = a->low;
		r = LIBJ2_JU_BIT;
	} else {
		return LIBJ2_J2U_BIT;
	}
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	n = (unsigned)__builtin_clzg(x);
	return r + n;
#else
	for (n = LIBJ2_JU_BIT; !((x >> --n) & 1U); r++);
	return r;
#endif
}


/**
 * Get the number of leading ones in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The number of ones after the most signficant cleared
 *             bit in `a`, `LIBJ2_J2U_BIT` if all bits in `a` are set
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_clo_j2u(const struct libj2_j2u *a)
{
	return libj2_clz_j2u(&(struct libj2_j2u){.high = ~a->high, .low = ~a->low});
}


/**
 * Get the number of trailing zeroes in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The number of zeroes before the least signficant set
 *             bit in `a`, `LIBJ2_J2U_BIT` if `a` has the value 0
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_ctz_j2u(const struct libj2_j2u *a)
{
	uintmax_t x;
	unsigned r, n;
	if (a->low) {
		x = a->low;
		r = 0;
	} else if (a->high) {
		x = a->high;
		r = LIBJ2_JU_BIT;
	} else {
		return LIBJ2_J2U_BIT;
	}
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	n = (unsigned)__builtin_ctzg(x);
#else
	for (n = 0; !((x >> n) & 1U); n++);
#endif
	return r + n;
}


/**
 * Get the number of trailing ones in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The number of ones before the leadt signficant cleared
 *             bit in `a`, `LIBJ2_J2U_BIT` if all bits in `a` are set
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_cto_j2u(const struct libj2_j2u *a)
{
	return libj2_ctz_j2u(&(struct libj2_j2u){.high = ~a->high, .low = ~a->low});
}


/**
 * Count the number of set bits in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The number of set bits in `a`
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_co_j2u(const struct libj2_j2u *a)
{
#if defined(LIBJ2_USE_GCC_INTRINSIC_FUNCTIONS_)
	return (unsigned)__builtin_popcountg(a->high) + (unsigned)__builtin_popcountg(a->low);
#else
	uintmax_t x, r = 0;
#if UINT64_MAX < UINTMAX_MAX
	uintmax_t y;
	for (y = a->low; y; y >>= 64) {
		x = y & UINT64_MAX;
#else
		x = a->high;
#endif
		x = (x & UINTMAX_C(0x5555555555555555)) + ((x >>  1) & UINTMAX_C(0x5555555555555555));
		x = (x & UINTMAX_C(0x3333333333333333)) + ((x >>  2) & UINTMAX_C(0x3333333333333333));
		x = (x & UINTMAX_C(0x0F0F0F0F0F0F0F0F)) + ((x >>  4) & UINTMAX_C(0x0F0F0F0F0F0F0F0F));
		x = (x & UINTMAX_C(0x00FF00FF00FF00FF)) + ((x >>  8) & UINTMAX_C(0x00FF00FF00FF00FF));
		x = (x & UINTMAX_C(0x0000FFFF0000FFFF)) + ((x >> 16) & UINTMAX_C(0x0000FFFF0000FFFF));
		x = (x & UINTMAX_C(0x00000000FFFFFFFF)) + ((x >> 32) & UINTMAX_C(0x00000000FFFFFFFF));
		r += x;
#if UINT64_MAX < UINTMAX_MAX
	}
#endif
#if UINT64_MAX < UINTMAX_MAX
	for (y = a->low; y; y >>= 64) {
		x = y & UINT64_MAX;
#else
		x = a->low;
#endif
		x = (x & UINTMAX_C(0x5555555555555555)) + ((x >>  1) & UINTMAX_C(0x5555555555555555));
		x = (x & UINTMAX_C(0x3333333333333333)) + ((x >>  2) & UINTMAX_C(0x3333333333333333));
		x = (x & UINTMAX_C(0x0F0F0F0F0F0F0F0F)) + ((x >>  4) & UINTMAX_C(0x0F0F0F0F0F0F0F0F));
		x = (x & UINTMAX_C(0x00FF00FF00FF00FF)) + ((x >>  8) & UINTMAX_C(0x00FF00FF00FF00FF));
		x = (x & UINTMAX_C(0x0000FFFF0000FFFF)) + ((x >> 16) & UINTMAX_C(0x0000FFFF0000FFFF));
		x = (x & UINTMAX_C(0x00000000FFFFFFFF)) + ((x >> 32) & UINTMAX_C(0x00000000FFFFFFFF));
		r += x;
#if UINT64_MAX < UINTMAX_MAX
	}
#endif
	return (unsigned)r;
#endif
}


/**
 * Count the number of cleared bits in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The number of cleared bits in `a`
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_cz_j2u(const struct libj2_j2u *a)
{
	return LIBJ2_J2U_BIT - libj2_co_j2u(a);
}


/**
 * Get the index of the least significant set
 * bit in an unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The index, counting from index one
 *             at the least significant bit, of the
 *             least significant set bit in `a`, or
 *             0 if no bit is set
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_ffs_j2u(const struct libj2_j2u *a)
{
	unsigned r = libj2_ctz_j2u(a);
	return r == LIBJ2_J2U_BIT ? 0U : r + 1U;
}


/**
 * Get the index of the least significant cleared
 * bit in an unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The index, counting from index one
 *             at the least significant bit, of the
 *             least significant cleared bit in `a`,
 *             or 0 if no bit is cleared
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_ffc_j2u(const struct libj2_j2u *a)
{
	return libj2_ffs_j2u(&(struct libj2_j2u){.high = ~a->high, .low = ~a->low});
}


/**
 * Get the index of the most significant set
 * bit in an unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The index, counting from index one
 *             at the least significant bit, of the
 *             most significant set bit in `a`,
 *             or 0 if no bit is set
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_fls_j2u(const struct libj2_j2u *a)
{
	unsigned r = libj2_clz_j2u(a);
	return LIBJ2_J2U_BIT - r;
}


/**
 * Get the index of the most significant cleared
 * bit in an unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     The index, counting from index one
 *             at the least significant bit, of the
 *             most significant cleared bit in `a`,
 *             or 0 if no bit is cleared
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_flc_j2u(const struct libj2_j2u *a)
{
	return libj2_fls_j2u(&(struct libj2_j2u){.high = ~a->high, .low = ~a->low});
}


/**
 * Calculate the parity of the bits in
 * an unsigned double-max precision integer
 * 
 * @param   a  The integer to inspect
 * @return     1 if the number of set bits in `a`
 *             is odd, 0 otherwise (if even)
 * 
 * @since  1.0
 */
LIBJ2_PURE_ inline unsigned
libj2_parity_j2u(const struct libj2_j2u *a)
{
#if defined(LIBJ2_USE_GCC_PARITYG_)
	return (unsigned)(__builtin_parityg(a->high) ^ __builtin_parityg(a->low));
#else
	unsigned s = LIBJ2_JU_BIT >> 1;
	uintmax_t x = a->high ^ a->low;
	uintmax_t mask = ((uintmax_t)1 << s) - 1U;
	while (s) {
		x = (x ^ (x >> s)) & mask;
		mask >>= s >>= 1;
	}
	return (unsigned)x;
#endif
}


/**
 * Clears all bits in an unsigned double-max precision
 * integer except the least significant set bit
 * 
 * @param  a  The integer to modify; will be updated
 * 
 * @since  1.0
 */
inline void
libj2_kfs_j2u(struct libj2_j2u *a)
{
	unsigned i = libj2_ffs_j2u(a);
	if (i)
		libj2_j2u_and_bit(a, i - 1U);
}


/**
 * Clears all bits in an unsigned double-max precision
 * integer except the least significant set bit
 * 
 * @param  a    The integer to modify
 * @param  res  Output parameter for the result
 * 
 * @since  1.0
 */
inline void
libj2_kfs_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	unsigned i = libj2_ffs_j2u(a);
	if (i)
		libj2_j2u_and_bit_to_j2u(a, i - 1U, res);
	else
		*res = *a;
}


/**
 * Clears all bits in an unsigned double-max precision
 * integer except the most significant set bit
 * 
 * @param   a  The integer to modify; will be modified
 * 
 * @since  1.0
 */
inline void
libj2_kls_j2u(struct libj2_j2u *a)
{
	unsigned i = libj2_fls_j2u(a);
	if (i)
		libj2_j2u_and_bit(a, i - 1U);
}


/**
 * Clears all bits in an unsigned double-max precision
 * integer except the most significant set bit
 * 
 * @param  a    The integer to modify
 * @param  res  Output parameter for the result
 * 
 * @since  1.0
 */
inline void
libj2_kls_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	unsigned i = libj2_fls_j2u(a);
	if (i)
		libj2_j2u_and_bit_to_j2u(a, i - 1U, res);
	else
		*res = *a;
}


/**
 * Clear the least significant set bit in an
 * unsigned double-max precision integer
 * 
 * @param  a  The integer to modify; will be updated
 * 
 * @since  1.0
 */
inline void
libj2_cfs_j2u(struct libj2_j2u *a)
{
	unsigned i = libj2_ffs_j2u(a);
	if (i)
		libj2_j2u_xor_bit(a, i - 1U);
}


/**
 * Clear the least significant set bit in an
 * unsigned double-max precision integer
 * 
 * @param  a    The integer to modify
 * @param  res  Output parameter for the result
 * 
 * @since  1.0
 */
inline void
libj2_cfs_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	unsigned i = libj2_ffs_j2u(a);
	if (i)
		libj2_j2u_xor_bit_to_j2u(a, i - 1U, res);
	else
		*res = *a;
}


/**
 * Clear the most significant set bit in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to modify; will be modified
 * 
 * @since  1.0
 */
inline void
libj2_cls_j2u(struct libj2_j2u *a)
{
	unsigned i = libj2_fls_j2u(a);
	if (i)
		libj2_j2u_xor_bit(a, i - 1U);
}


/**
 * Clear the most significant set bit in an
 * unsigned double-max precision integer
 * 
 * @param  a    The integer to modify
 * @param  res  Output parameter for the result
 * 
 * @since  1.0
 */
inline void
libj2_cls_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	unsigned i = libj2_fls_j2u(a);
	if (i)
		libj2_j2u_xor_bit_to_j2u(a, i - 1U, res);
	else
		*res = *a;
}


/**
 * Set the least significant cleared bit in an
 * unsigned double-max precision integer
 * 
 * @param  a  The integer to modify; will be updated
 * 
 * @since  1.0
 */
inline void
libj2_sfc_j2u(struct libj2_j2u *a)
{
	unsigned i = libj2_ffc_j2u(a);
	if (i)
		libj2_j2u_or_bit(a, i - 1U);
}


/**
 * Set the least significant cleared bit in an
 * unsigned double-max precision integer
 * 
 * @param  a    The integer to modify
 * @param  res  Output parameter for the result
 * 
 * @since  1.0
 */
inline void
libj2_sfc_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	unsigned i = libj2_ffc_j2u(a);
	if (i)
		libj2_j2u_or_bit_to_j2u(a, i - 1U, res);
	else
		*res = *a;
}


/**
 * Set the most significant cleared bit in an
 * unsigned double-max precision integer
 * 
 * @param   a  The integer to modify; will be modified
 * 
 * @since  1.0
 */
inline void
libj2_slc_j2u(struct libj2_j2u *a)
{
	unsigned i = libj2_flc_j2u(a);
	if (i)
		libj2_j2u_or_bit(a, i - 1U);
}


/**
 * Set the most significant cleared bit in an
 * unsigned double-max precision integer
 * 
 * @param  a    The integer to modify
 * @param  res  Output parameter for the result
 * 
 * @since  1.0
 */
inline void
libj2_slc_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	unsigned i = libj2_flc_j2u(a);
	if (i)
		libj2_j2u_or_bit_to_j2u(a, i - 1U, res);
	else
		*res = *a;
}
