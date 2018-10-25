#include "gxx/debug/dprint.h"
//#include "utilxx/horrible_cast.h"

/*
void dprbin(uint8_t obj) { debug_printbin_uint8(obj); }
void dprbin(uint16_t obj) { debug_printbin_uint16(obj); }
void dprbin(uint32_t obj) { debug_printbin_uint32(obj); }
void dprbin(uint64_t obj) { debug_printbin_uint64(obj); }

void dprbin(int8_t obj) { debug_printbin_uint8(obj); }
void dprbin(int16_t obj) { debug_printbin_uint16(obj); }
void dprbin(int32_t obj) { debug_printbin_uint32(obj); }
void dprbin(int64_t obj) { debug_printbin_uint64(obj); }
*/

/*
void dprhex(const char* obj) { debug_print_dump_simple((void*)obj, debug_strlen(obj));   }
void dprhex(char obj) { debug_printhex_uint8((uint8_t) obj); }

void dprhex(uint8_t obj) { debug_printhex_uint8(obj); }
void dprhex(uint16_t obj) { debug_printhex_uint16(obj); }
void dprhex(uint32_t obj) { debug_printhex_uint32(obj); }
void dprhex(uint64_t obj) { debug_printhex_uint64(obj); }

void dprhex(int8_t obj) { debug_printhex_uint8(obj); }
void dprhex(int16_t obj) { debug_printhex_uint16(obj); }
void dprhex(int32_t obj) { debug_printhex_uint32(obj); }
void dprhex(int64_t obj) { debug_printhex_uint64(obj); }
*/

//template<> void dprhex(float obj) { dprhex(horrible_cast<float_uint, float>(obj)); }
//template<> void dprhex(double obj) { dprhex(horrible_cast<double_uint, double>(obj)); }
//void dpr(gxx::string obj) {dpr(obj.c_str());}

void dpr_dump(const void* obj, uint32_t size)
{
	debug_print_dump(obj, size);
}

void dprtab() {
	debug_putchar('\t');
}

void dprtab(uint8_t obj) {
	while(obj--) {
		debug_putchar('\t');
	}
}
