#ifndef GXX_UTIL_MATH_H
#define GXX_UTIL_MATH_H

#include <assert.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <stdbool.h>
#include <gxx/util/ftypes.h>

#define __MAX__(a,b) ((a) > (b) ? (a) : (b))
#define __MIN__(a,b) ((a) < (b) ? (a) : (b))

__BEGIN_DECLS

/*
 *  Bit  31      Sign
 *  Bits 30-23   Exponent
 *  Bits 22-00   Mantissa
 */
static inline bool is_IEEE754_32BitFloat_AnInt(sfloat val)
{
    // Put the value in an int so we can do bitwise operations.
    uint32_t  valAsInt = *(uint32_t*)(&val);

    // Remember to subtract 127 from the exponent (to get real value)
    int16_t  exponent = ((valAsInt >> 23) & 0xFF) - 127;

    int16_t bitsInFraction = 23 - exponent;
    uint32_t mask = exponent < 0
                    ? 0x7FFFFFFF
                    : exponent > 23
                         ? 0x00
                         : (1 << bitsInFraction) - 1;

    return !(valAsInt & mask);
}

/*
 *  Bit  63      Sign
 *  Bits 62-52   Exponent
 *  Bits 51-00   Mantissa
 */
static inline bool is_IEEE754_64BitFloat_AnInt(dfloat val)
{
    // Put the value in an long long so we can do bitwise operations.
    uint64_t  valAsInt = *(uint64_t*)(&val);

    // Remember to subtract 1023 from the exponent (to get real value)
    int16_t  exponent = ((valAsInt >> 52) & 0x7FF) - 1023;

    int16_t bitsInFraction = 52 - exponent;
    uint64_t mask = exponent < 0
                    ? 0x7FFFFFFFFFFFFFFFLL
                    : exponent > 52
                        ? 0x00
                        : (1LL << bitsInFraction) - 1;

    return !(valAsInt & mask);
}

static inline bool isint_sfloat(sfloat arg) 
{
	return is_IEEE754_64BitFloat_AnInt(arg);
}

static inline bool isint_dfloat(dfloat arg) 
{
	return is_IEEE754_32BitFloat_AnInt(arg);
}

__END_DECLS

#ifdef __cplusplus
static inline bool isint(int arg) { return isint_dfloat(arg); }
static inline bool isint(dfloat arg) { return isint_dfloat(arg); }
static inline bool isint(sfloat arg) { return isint_sfloat(arg); }
#else
#define isint(X) _Generic((X),dfloat:isint_dfloat,sfloat:isint_sfloat)(X)
#endif

#endif