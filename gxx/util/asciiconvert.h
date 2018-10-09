#ifndef GXX_ASCII_CONVERT_H
#define GXX_ASCII_CONVERT_H

#include <sys/cdefs.h>
#include <stdint.h>

__BEGIN_DECLS

__attribute__((deprecated))
static inline uint8_t sym2byte(char c) {
	return (uint8_t)(c <= '9' ? c - '0' : c - 'A' + 10);
}

__attribute__((deprecated))
static inline char byte2sym(uint8_t n) {
	return n < 10 ? '0' + n : 'A' - 10 + n;
}

__END_DECLS

#endif