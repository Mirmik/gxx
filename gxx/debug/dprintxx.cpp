#include "gxx/debug/dprint.h"

int dprln() {debug_print("\r\n");};

int dpr(char obj) { debug_putchar(obj); };
int dpr(char* obj) { debug_print(obj); };
int dpr(const char* obj) { debug_print(obj); };

int dpr(uint8_t obj) { debug_printdec_uint8(obj); };
int dpr(uint16_t obj) { debug_printdec_uint16(obj); };
int dpr(uint32_t obj) { debug_printdec_uint32(obj); };
int dpr(uint64_t obj) { debug_printdec_uint64(obj); };

int dpr(int8_t obj) { debug_printdec_int8(obj); };
int dpr(int16_t obj) { debug_printdec_int16(obj); };
int dpr(int32_t obj) { debug_printdec_int32(obj); };
int dpr(int64_t obj) { debug_printdec_int64(obj); };

int dpr(double obj) { debug_printdec_double(obj, 2); };
int dpr(float obj) { debug_printdec_float(obj, 2); };

int dpr(bool obj) { debug_print_bool(obj); };

int dprbin(uint8_t obj) { debug_printbin_uint8(obj); };
int dprbin(uint16_t obj) { debug_printbin_uint16(obj); };
int dprbin(uint32_t obj) { debug_printbin_uint32(obj); };
int dprbin(uint64_t obj) { debug_printbin_uint64(obj); };

int dprbin(int8_t obj) { debug_printbin_uint8(obj); };
int dprbin(int16_t obj) { debug_printbin_uint16(obj); };
int dprbin(int32_t obj) { debug_printbin_uint32(obj); };
int dprbin(int64_t obj) { debug_printbin_uint64(obj); };


int dprhex(const char* obj) { debug_print_dump_simple((int*)obj, debug_strlen(obj));   };
int dprhex(char obj) { debug_printhex_uint8((uint8_t) obj); };

int dprhex(uint8_t obj) { debug_printhex_uint8(obj); };
int dprhex(uint16_t obj) { debug_printhex_uint16(obj); };
int dprhex(uint32_t obj) { debug_printhex_uint32(obj); };
int dprhex(uint64_t obj) { debug_printhex_uint64(obj); };

int dprhex(int8_t obj) { debug_printhex_uint8(obj); };
int dprhex(int16_t obj) { debug_printhex_uint16(obj); };
int dprhex(int32_t obj) { debug_printhex_uint32(obj); };
int dprhex(int64_t obj) { debug_printhex_uint64(obj); };

//template<> int dprhex(float obj) { dprhex(horrible_cast<float_uint, float>(obj)); };
//template<> int dprhex(double obj) { dprhex(horrible_cast<double_uint, double>(obj)); };
//int dpr(gxx::string obj) {dpr(obj.c_str());};

int dpr_dump(void* obj, uint32_t size) 
{ 
	debug_print_dump(obj, size); 
};

int dpr_dump_ascii(void* obj, uint32_t size)
{ 
	debug_print_dump_ascii(obj, size); 
};

int dprtab() {
	debug_putchar('\t');
};

int dprtab(uint8_t obj) {
	while(obj--) {
		debug_putchar('\t');
	}
};