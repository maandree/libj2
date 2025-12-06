/* See LICENSE file for copyright and license details. */
#ifndef LIBJ2_H
# error Do not include this header directly, include <libj2.h> instead
#endif


/**
 * Convert an unsigned double-max precision
 * integer to a string
 * 
 * The string will be terminated by a NUL byte
 * (unless `bufsize` is 0) and will otherwise
 * only contain the digits, and will not contain
 * any leading zeroes (except that the value
 * zero will be represented as "0")
 * 
 * @param   a        The integer to convert into a string
 * @param   buf      Buffer for the string
 * @param   bufsize  The size of `buf`
 * @param   digits   List of digits to use, each byte is
 *                   regarded as a symbol, starting from
 *                   the zero-digit. If `NULL`, "0123456789"
 *                   (the decimal system) will be used. Minimum
 *                   length is 2. May not contain duplicates.
 * @return           The number of digits used to represent
 *                   the integer, even if not all of them
 *                   fit into the buffer; or zero on failure
 *                   (`digits` has a length less than 2 or
 *                   contains duplicate symbols)
 * 
 * This function does not set `errno`
 * 
 * @since  1.1
 */
#if defined(__GNUC__)
__attribute__((__nonnull__(1)))
#endif
size_t libj2_j2u_to_str(const struct libj2_j2u *a, char *buf, size_t bufsize, const char *digits);


/**
 * Convert a string into a an unsigned
 * double-max precision integer
 * 
 * Any leading ASCII whitespace, as well
 * as any leading '+' character, will be
 * ignored, the all digits will be parsed
 * until any other character is encountered
 * 
 * Parsing will stop after `slen` bytes,
 * when a NUL byte is encountered, or a
 * non-digit is encountered after any
 * leading skipped character; whichever
 * comes first
 * 
 * @param   s        The string to parse
 * @param   slen     The maximum number of bytes to read from `s`
 * @param   end      Output parameter for where parsing stopped
 *                   (pointing to the first byte that is is not
 *                   a leading ASCII whitespace, leading '+'
 *                   character, nor a digit)
 * @param   digits1  List of digits to use, each byte is
 *                   regarded as a symbol, starting from
 *                   the zero-digit. If `NULL`, "0123456789"
 *                   (the decimal system) will be used. Any
 *                   symbol in this list will be removed from the
 *                   set of ignored leading characeters; minimum
 *                   length is 2. May not contain duplicates.
 * @param   digits2  List of symbols to use as synonyms for
 *                   the symbols in `digits`, must be of the
 *                   same length as `digits1`, or `NULL` if
 *                   `digit1` is `NULL` or to use no additional
 *                   symbols
 * @param   a        Output parameter for the decoded integer
 * @return           0 upon successful completion, or an error
 *                   code on failure
 *
 * @throws  EINVAL  `digits1` or `digits2` is misconfigured
 * @throws  EINVAL  No digit was encountered;
 *                  `*a` (unless it's `NULL`) will be set to
 *                  the value zero
 * @throws  ERANGE  The value is too large to be represented;
 *                  `*a` (unless it's `NULL`) will be set to
 *                  the maximum value
 * 
 * This function does not set `errno`
 * 
 * @since  1.1
 */
int libj2_str_to_j2u(const char *s, size_t slen, char **end, const char *digits1,
		     const char *digits2, struct libj2_j2u *a);
