#include "gxx/debug/dprint.h"

int dasm_test() {
	return debug_print("AssemblerDebugLibraryLinkageSuccess\r\n");
}

int dasm_printhex_uint16(uint16_t a) {
	return debug_printhex_uint16(a);
}
