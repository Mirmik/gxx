#include "gxx/debug/dprint.h"

int dprln() { return debug_print("\r\n");}

int dpr(char obj) { return debug_putchar(obj); }
int dpr(char* obj) { return debug_print(obj); }
int dpr(const char* obj) { return debug_print(obj); }

int dpr(uint8_t obj) { return debug_printdec_uint8(obj); }
int dpr(uint16_t obj) { return debug_printdec_uint16(obj); }
int dpr(uint32_t obj) { return debug_printdec_uint32(obj); }
int dpr(uint64_t obj) { return debug_printdec_uint64(obj); }

int dpr(int8_t obj) { return debug_printdec_int8(obj); }
int dpr(int16_t obj) { return debug_printdec_int16(obj); }
int dpr(int32_t obj) { return debug_printdec_int32(obj); }
int dpr(int64_t obj) { return debug_printdec_int64(obj); }

int dpr(double obj) { return debug_printdec_double(obj, 2); }
int dpr(float obj) { return debug_printdec_float(obj, 2); }

int dpr(bool obj) { return debug_print_bool(obj); }

int dprbin(uint8_t obj) { return debug_printbin_uint8(obj); }
int dprbin(uint16_t obj) { return debug_printbin_uint16(obj); }
int dprbin(uint32_t obj) { return debug_printbin_uint32(obj); }
int dprbin(uint64_t obj) { return debug_printbin_uint64(obj); }

int dprbin(int8_t obj) { return debug_printbin_uint8(obj); }
int dprbin(int16_t obj) { return debug_printbin_uint16(obj); }
int dprbin(int32_t obj) { return debug_printbin_uint32(obj); }
int dprbin(int64_t obj) { return debug_printbin_uint64(obj); }


int dprhex(const char* obj) { return debug_print_dump_simple((int*)obj, debug_strlen(obj));   }
int dprhex(char obj) { return debug_printhex_uint8((uint8_t) obj); }

int dprhex(uint8_t obj) { return debug_printhex_uint8(obj); }
int dprhex(uint16_t obj) { return debug_printhex_uint16(obj); }
int dprhex(uint32_t obj) { return debug_printhex_uint32(obj); }
int dprhex(uint64_t obj) { return debug_printhex_uint64(obj); }

int dprhex(int8_t obj) { return debug_printhex_uint8(obj); }
int dprhex(int16_t obj) { return debug_printhex_uint16(obj); }
int dprhex(int32_t obj) { return debug_printhex_uint32(obj); }
int dprhex(int64_t obj) { return debug_printhex_uint64(obj); }

//template<> int dprhex(float obj) { dprhex(horrible_cast<float_uint, float>(obj)); }
//template<> int dprhex(double obj) { dprhex(horrible_cast<double_uint, double>(obj)); }
//int dpr(gxx::string obj) {dpr(obj.c_str());}

int dpr_dump(void* obj, uint32_t size) 
{ 
	return debug_print_dump(obj, size); 
}

int dpr_dump_ascii(void* obj, uint32_t size)
{ 
	return debug_print_dump_ascii(obj, size); 
}

int dprtab() {
	return debug_putchar('\t');
}

int dprtab(uint8_t obj) {
	int ret = 0;
	while(obj--) {
		ret += debug_putchar('\t');
	}
	return ret;
}