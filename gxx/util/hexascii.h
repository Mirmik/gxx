#ifndef GXX_UTIL_BASE64_H
#define GXX_UTIL_BASE64_H

#ifdef __cplusplus

#include <string>

namespace gxx {
	//bool is_base64(unsigned char c);
	std::string hexascii_encode(const uint8_t *indata, size_t size);
	std::string hexascii_encode(std::string const& str);
	std::string hexascii_decode(std::string const& encoded_string);
}

#endif

#include "access.h"

static inline uint8_t hex2half(char c) {
	return (uint8_t)(c <= '9' ? c - '0' : c - 'A' + 10);
}

static inline char half2hex(uint8_t n) {
	return n < 10 ? '0' + n : 'A' - 10 + n;
}

static inline uint8_t hex2byte(char hi, char lo) {
	return (hex2half(hi) << 4) + hex2half(lo);
}

static inline uint8_t hex_to_uint8 (const char* hex) {
	uint8_t out;

	out = hex2byte(*(hex+0), *(hex+1));

	return out;
}

static inline uint16_t hex_to_uint16 (const char* hex) {
	uint16_t out;

	UINT16_HI(out) = hex2byte(*(hex+0), *(hex+1));
	UINT16_LO(out) = hex2byte(*(hex+2), *(hex+3));

	return out;
}

static inline uint32_t hex_to_uint32 (const char* hex) {
	uint32_t out;

	UINT32_HHI(out) = hex2byte(*(hex+0), *(hex+1));
	UINT32_HLO(out) = hex2byte(*(hex+2), *(hex+3));
	UINT32_LHI(out) = hex2byte(*(hex+4), *(hex+5));
	UINT32_LLO(out) = hex2byte(*(hex+6), *(hex+7));

	return out;
}

static inline uint64_t hex_to_uint64 (const char* hex) {
	uint64_t out;

	UINT64_HHHI(out) = hex2byte(*(hex+ 0), *(hex+ 1));
	UINT64_HHLO(out) = hex2byte(*(hex+ 2), *(hex+ 3));
	UINT64_HLHI(out) = hex2byte(*(hex+ 4), *(hex+ 5));
	UINT64_HLLO(out) = hex2byte(*(hex+ 6), *(hex+ 7));
	UINT64_LHHI(out) = hex2byte(*(hex+ 8), *(hex+ 9));
	UINT64_LHLO(out) = hex2byte(*(hex+10), *(hex+11));
	UINT64_LLHI(out) = hex2byte(*(hex+12), *(hex+13));
	UINT64_LLLO(out) = hex2byte(*(hex+14), *(hex+15));

	return out;
}

#endif