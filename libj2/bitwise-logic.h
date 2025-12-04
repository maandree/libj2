/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Test whether a specific bit in an unsigned
 * double-max precision integer is set
 * 
 * @param   a  The integer to inspect
 * @param   b  The index of the bit to test,
 *             0 for the least significant bit
 * @return     1 if the bit is set, 0 otherwise
 */
inline int
libj2_j2u_test_bit(const struct libj2_j2u *a, unsigned b)
{
	if (b >= LIBJ2_J2U_BIT)
		return 0;
	else if (b >= LIBJ2_JU_BIT) 
		return (int)((a->high >> (b - LIBJ2_JU_BIT)) & 1U);
	else
		return (int)((a->low >> b) & 1U);
}


/**
 * Test whether two unsigned double-max precision
 * integers have commonly set bits
 * 
 * @param   a  One of the integers
 * @param   b  The other integer
 * @return     1 if the two integers have set bits
 *             in common, 0 otherwise
 */
inline int
libj2_j2u_test_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b)
{
	return (a->high & b->high) || (a->low & b->low);
}


/**
 * Test whether an unsigned double-max precision
 * integer have commonly set bits with an unsigned
 * max precision integer
 * 
 * @param   a  The double-max precision integer
 * @param   b  The max precision integer
 * @return     1 if the two integers have set bits
 *             in common, 0 otherwise
 */
inline int
libj2_j2u_test_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return !!(a->low & b);
}


/**
 * Test whether the high part of an unsigned double-max
 * precision integer have commonly set bits with an unsigned
 * max precision integer
 * 
 * @param   a  The double-max precision integer
 * @param   b  The max precision integer
 * @return     1 if high part of `a` have set bits
 *             in common with `b`, 0 otherwise
 */
inline int
libj2_j2u_test_high_ju(const struct libj2_j2u *a, uintmax_t b)
{
	return !!(a->high & b);
}


/**
 * Calculate the bitwise NOT of an unsigned
 * double-max precision integer
 * 
 * @param  a  The integer, also used as output
 *            parameter for the result
 */
inline void
libj2_not_j2u(struct libj2_j2u *a)
{
	a->high = ~a->high;
	a->low = ~a->low;
}


/**
 * Calculate the bitwise NOT of an unsigned
 * double-max precision integer
 * 
 * @param  a    The integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_not_j2u_to_j2u(const struct libj2_j2u *a, struct libj2_j2u *res)
{
	res->high = ~a->high;
	res->low = ~a->low;
}


/**
 * Calculate the bitwise NOT of an unsigned double-max
 * precision integer represented by an unsigned max
 * precision integer (the high part is of the unsigned
 * double-max precision integer is treated as 0)
 * 
 * @param  a    The integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_not_ju_to_j2u(uintmax_t a, struct libj2_j2u *res)
{
	res->high = UINTMAX_MAX;
	res->low = ~a;
}


/**
 * Calculate the bitwise AND of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_and_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	a->high &= b->high;
	a->low &= b->low;
}


/**
 * Calculate the bitwise AND of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_and_ju(struct libj2_j2u *a, uintmax_t b)
{
	a->high = 0;
	a->low &= b;
}


/**
 * Calculate the bitwise AND of two unsigned double-max
 * precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_and_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	res->high = a->high & b->high;
	res->low = a->low & b->low;
}


/**
 * Calculate the bitwise AND of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_and_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	res->high = 0;
	res->low = a->low & b;
}


/**
 * Calculate the bitwise AND of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_and_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_and_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise OR of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_or_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	a->high |= b->high;
	a->low |= b->low;
}


/**
 * Calculate the bitwise OR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_or_ju(struct libj2_j2u *a, uintmax_t b)
{
	a->low |= b;
}


/**
 * Calculate the bitwise OR of two unsigned double-max
 * precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_or_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	res->high = a->high | b->high;
	res->low = a->low | b->low;
}


/**
 * Calculate the bitwise OR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_or_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	res->high = a->high;
	res->low = a->low | b;
}


/**
 * Calculate the bitwise OR of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_or_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_or_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise XOR of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_xor_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	a->high ^= b->high;
	a->low ^= b->low;
}


/**
 * Calculate the bitwise XOR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_xor_ju(struct libj2_j2u *a, uintmax_t b)
{
	a->low ^= b;
}


/**
 * Calculate the bitwise XOR of two unsigned double-max
 * precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_xor_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	res->high = a->high ^ b->high;
	res->low = a->low ^ b->low;
}


/**
 * Calculate the bitwise XOR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_xor_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	res->high = a->high;
	res->low = a->low ^ b;
}


/**
 * Calculate the bitwise XOR of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_xor_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_xor_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise NAND of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nand_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	libj2_j2u_and_j2u(a, b);
	libj2_not_j2u(a);
}


/**
 * Calculate the bitwise NAND of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nand_ju(struct libj2_j2u *a, uintmax_t b)
{
	libj2_j2u_and_ju(a, b);
	libj2_not_j2u(a);
}


/**
 * Calculate the bitwise NAND of two unsigned double-max
 * precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nand_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_and_j2u_to_j2u(a, b, res);
	libj2_not_j2u(res);
}


/**
 * Calculate the bitwise NAND of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nand_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	libj2_j2u_and_ju_to_j2u(a, b, res);
	libj2_not_j2u(res);
}


/**
 * Calculate the bitwise NAND of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_nand_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_nand_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise NOR of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nor_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	libj2_j2u_or_j2u(a, b);
	libj2_not_j2u(a);
}


/**
 * Calculate the bitwise NOR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nor_ju(struct libj2_j2u *a, uintmax_t b)
{
	libj2_j2u_or_ju(a, b);
	libj2_not_j2u(a);
}


/**
 * Calculate the bitwise NOR of two unsigned double-max
 * precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nor_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_or_j2u_to_j2u(a, b, res);
	libj2_not_j2u(res);
}


/**
 * Calculate the bitwise NOR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nor_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	libj2_j2u_or_ju_to_j2u(a, b, res);
	libj2_not_j2u(res);
}


/**
 * Calculate the bitwise NOR of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_nor_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_nor_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise XNOR of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_xnor_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	libj2_j2u_xor_j2u(a, b);
	libj2_not_j2u(a);
}


/**
 * Calculate the bitwise XNOR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_xnor_ju(struct libj2_j2u *a, uintmax_t b)
{
	libj2_j2u_xor_ju(a, b);
	libj2_not_j2u(a);
}


/**
 * Calculate the bitwise XNOR of two unsigned double-max
 * precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_xnor_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_xor_j2u_to_j2u(a, b, res);
	libj2_not_j2u(res);
}


/**
 * Calculate the bitwise XNOR of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_xnor_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	libj2_j2u_xor_ju_to_j2u(a, b, res);
	libj2_not_j2u(res);
}


/**
 * Calculate the bitwise XNOR of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_xnor_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_xnor_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise IMPLY of two unsigned double-max
 * precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_imply_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (a == b) {
		libj2_j2u_max(a);
	} else {
		libj2_not_j2u(a);
		libj2_j2u_or_j2u(a, b);
	}
}


/**
 * Calculate the bitwise IMPLY of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_imply_ju(struct libj2_j2u *a, uintmax_t b)
{
	libj2_not_j2u(a);
	libj2_j2u_or_ju(a, b);
}


/**
 * Calculate the bitwise IMPLY of two unsigned
 * double-max precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_imply_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (a == b) {
		res->high = UINTMAX_MAX;
		res->low = UINTMAX_MAX;
	} else if (res == b) {
		struct libj2_j2u c;
		libj2_not_j2u_to_j2u(a, &c);
		libj2_j2u_or_j2u(res, &c);
	} else {
		libj2_not_j2u_to_j2u(a, res);
		libj2_j2u_or_j2u(res, b);
	}
}


/**
 * Calculate the bitwise IMPLY of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_imply_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	libj2_not_j2u_to_j2u(a, res);
	libj2_j2u_or_ju(res, b);
}


/**
 * Calculate the bitwise IF of two unsigned
 * double-max precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_if_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c;
	libj2_not_j2u_to_j2u(b, &c);
	libj2_j2u_or_j2u(a, &c);
}


/**
 * Calculate the bitwise NIF of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_if_ju(struct libj2_j2u *a, uintmax_t b)
{
	struct libj2_j2u c;
	libj2_not_ju_to_j2u(b, &c);
	libj2_j2u_or_j2u(a, &c);
}


/**
 * Calculate the bitwise IF of two unsigned
 * double-max precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_if_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_imply_j2u_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise IF of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_if_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	if (res == a) {
		struct libj2_j2u c;
		libj2_not_ju_to_j2u(b, &c);
		libj2_j2u_or_j2u(res, &c);
	} else {
		libj2_not_ju_to_j2u(b, res);
		libj2_j2u_or_j2u(res, a);
	}
}


/**
 * Calculate the bitwise IMPLY of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_imply_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_if_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise IF of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_if_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_imply_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise NIMPLY of two unsigned
 * double-max precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nimply_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	struct libj2_j2u c;
	libj2_not_j2u_to_j2u(b, &c);
	libj2_j2u_and_j2u(a, &c);
}


/**
 * Calculate the bitwise NIMPLY of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nimply_ju(struct libj2_j2u *a, uintmax_t b)
{
	struct libj2_j2u c;
	libj2_not_ju_to_j2u(b, &c);
	libj2_j2u_and_j2u(a, &c);
}


/**
 * Calculate the bitwise NIMPLY of two unsigned
 * double-max precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nimply_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	if (a == b) {
		res->high = 0;
		res->low = 0;
	} else if (res == a) {
		struct libj2_j2u c;
		libj2_not_j2u_to_j2u(b, &c);
		libj2_j2u_and_j2u(res, &c);
	} else {
		libj2_not_j2u_to_j2u(b, res);
		libj2_j2u_and_j2u(res, a);
	}
}


/**
 * Calculate the bitwise NIMPLY of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nimply_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	if (res == a) {
		struct libj2_j2u c;
		libj2_not_ju_to_j2u(b, &c);
		libj2_j2u_and_j2u(res, &c);
	} else {
		libj2_not_ju_to_j2u(b, res);
		libj2_j2u_and_j2u(res, a);
	}
}


/**
 * Calculate the bitwise NIF of two unsigned
 * double-max precision integers
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nif_j2u(struct libj2_j2u *a, const struct libj2_j2u *b)
{
	if (a == b) {
		libj2_j2u_zero(a);
	} else {
		libj2_not_j2u(a);
		libj2_j2u_and_j2u(a, b);
	}
}


/**
 * Calculate the bitwise NIF of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a  The left-hand integer, also used as the
 *            output parameter for result
 * @param  b  The right-hand integer
 */
inline void
libj2_j2u_nif_ju(struct libj2_j2u *a, uintmax_t b)
{
	libj2_not_j2u(a);
	libj2_j2u_and_ju(a, b);
}


/**
 * Calculate the bitwise NIF of two unsigned
 * double-max precision integers
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nif_j2u_to_j2u(const struct libj2_j2u *a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_nimply_j2u_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise NIF of an unsigned double-max
 * precision integer (left-hand) and an unsigned max
 * precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_j2u_nif_ju_to_j2u(const struct libj2_j2u *a, uintmax_t b, struct libj2_j2u *res)
{
	libj2_not_j2u_to_j2u(a, res);
	libj2_j2u_and_ju(res, b);
}


/**
 * Calculate the bitwise NIMPLY of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_nimply_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_nif_ju_to_j2u(b, a, res);
}


/**
 * Calculate the bitwise NIF of an unsigned max
 * precision integer (left-hand) and an unsigned
 * double-max precision integer (right-hand)
 * 
 * @param  a    The left-hand integer
 * @param  b    The right-hand integer
 * @param  res  Output parameter for the result
 */
inline void
libj2_ju_nif_j2u_to_j2u(uintmax_t a, const struct libj2_j2u *b, struct libj2_j2u *res)
{
	libj2_j2u_nimply_ju_to_j2u(b, a, res);
}
