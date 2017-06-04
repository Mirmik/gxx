#ifndef GENOS_DEBUG_PRINT
#define GENOS_DEBUG_PRINT
	
#include <inttypes.h> 
//#include <compiler.h>

#ifdef __cplusplus
#include "gxx/buffer.h"
#endif

/*	
	2012-2015 Mirmik
	Библиотека низкоуровневого отладочного вывода.
	
	Библиотека предназначена для облегчения низкоуровневой отладки.
	Функции не имеют внешних зависимостей (кроме определения типов 
	и аппаратнозависимой инициализации и функции вывода символа), 
	линкуются по стандарту "С", что позволяет
	вызывать их в том числе с использованием ассемблера. 
	
	Библиотека призвана помочь в создании плацдарма на неосвоенном железе,
	а так же при отладке средств ввода-вывода.
	
	Для подключения библиотеки необходимо реализовать платформозависимую функцию
	debug_putchar, выводящую один символ char и 
	блокирующую процессор на время проведения этой операции.
*/

__BEGIN_DECLS
//Инициализация вывода
//int debug_print_init(); - в platform

//Платформозависимый !блокирующий процессор! вывод char
int debug_putchar(char c);

//Вывод строки указанной длины.
int debug_write(const char* c, int i);
//Вывод интов, согласно типам. Возможен вывод в системах dec, hex, bin.
 int debug_printhex_uint4(uint8_t b);
 int debug_printhex_uint8 (uint8_t b);
 int debug_printhex_uint64(uint64_t a);
 int debug_printhex_uint32(uint32_t a);

 #define debug_printhex_int4(a) debug_printhex_uint4(a)
 #define debug_printhex_int8(a) debug_printhex_uint8(a)
 #define debug_printhex_int16(a) debug_printhex_uint16(a) 
 #define debug_printhex_int32(a) debug_printhex_uint32(a)

 int debug_printhex_ptr(int* a);
 int debug_printhex_uint16(uint16_t a);
 int debug_printbin_uint4 (uint8_t b);
 int debug_printbin_uint8 (uint8_t b);
 int debug_printbin_uint64(uint64_t a);
 int debug_printbin_uint32(uint32_t a);
 int debug_printbin_uint16(uint16_t a);
 int debug_printdec_uint8 (uint8_t b);
 int debug_printdec_uint64(uint64_t a);
 int debug_printdec_uint32(uint32_t a);
 int debug_printdec_uint16(uint16_t a);
 int debug_printdec_int8 (int8_t b);
 int debug_printdec_int64(int64_t a);
 int debug_printdec_int32(int32_t a);
 int debug_printdec_int16(int16_t a);

 int debug_printdec_float(float a, int prec);
 int debug_printdec_double(double a, int prec);

//strlen для внутреннего использования
 int debug_strlen(const char *c);

//Вывод нульформатированной строки
 int debug_print(const char *c);
 int debug_print_line();

//Вывод дампа памяти. size - размер в байтах.
 int debug_print_dump(const void* address, uint16_t size);
 int debug_print_dump_ascii(const void* address, uint16_t size);
 
 int debug_print_dump_simple(void* address, uint16_t size);

//Вывод логического значения.
 int debug_print_bool(uint8_t b);
 int debug_print_bool_num(uint8_t b);

//Вывод float одинарной точности. //TODO дополнить
//int debug_printbin_spf(sp_float a);

//Проверка функций библиотеки debug_print.
int debug_print_test();

//Тесты для проверки ассемблерной линковки.
 int dasm_test();
 //int dasm_uint8_dpr1(uint8_t a);
 //int dasm_uint8_dpr2(uint8_t a, uint8_t b);
 //int dasm_uint8_dpr3(uint8_t a, uint8_t b, uint8_t c);
 //int dasm_uint8_dpr4(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
 int dasm_printhex_uint16(uint16_t a);
 int dasm_uint16_dpr2(uint16_t a, uint16_t b);
 int dasm_uint16_dpr4(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
 uint16_t dasm_uint16_ret();
 uint64_t dasm_uint64_ret();

__END_DECLS

#define dln() {debug_putchar('\r');debug_putchar('\n');}

#ifdef __cplusplus

int dprln();

int dpr(char obj);
int dpr(char* obj);
int dpr(const char* obj);

//template<> int dpr(genos::charptr obj) 
//{ 
//	debug_write(obj.to_buf(),obj.length()); 
//};

int dpr(uint8_t obj);
int dpr(uint16_t obj);
int dpr(uint32_t obj);
int dpr(uint64_t obj);

int dpr(int8_t obj);
int dpr(int16_t obj);
int dpr(int32_t obj);
int dpr(int64_t obj);

int dpr(bool obj);

int dpr(float obj);
int dpr(double obj);

template <typename Buffer>
int dpr(const Buffer& obj) {
	int ret = 0; ret += debug_write(obj.data(), obj.size()); return ret;
}

int dprbin(uint8_t obj);
int dprbin(uint16_t obj);
int dprbin(uint32_t obj);
int dprbin(uint64_t obj);

int dprbin(int8_t obj);
int dprbin(int16_t obj);
int dprbin(int32_t obj);
int dprbin(int64_t obj);

template <typename Buffer>
int dprhex(const Buffer& obj) {
	int ret = 0; ret += debug_print_dump(obj.data(), obj.size()); return ret;
}

int dprhex(const char* obj);
int dprhex(char obj);

int dprhex(uint8_t obj);
int dprhex(uint16_t obj);
int dprhex(uint32_t obj);
int dprhex(uint64_t obj);

int dprhex(int8_t obj);
int dprhex(int16_t obj);
int dprhex(int32_t obj);
int dprhex(int64_t obj);

//template<> int dprhex(float obj);
//template<> int dprhex(double obj);
//int dpr(gxx::string obj);

int dpr_dump(int* obj, uint32_t size);
int dpr_dump_ascii(int* obj, uint32_t size);

template<typename T> int dprptr(const T* const& obj) 
	{ int ret = 0; ret += debug_printhex_ptr((int*)obj); return ret; }

template<typename T> int dprln(const T& obj) 
	{ int ret = 0; ret += dpr(obj); ret += debug_write("\r\n", 2); return ret; }

template<typename T> int dprbinln(const T& obj) 
	{ int ret = 0; ret += dprbin(obj); ret += debug_write("\r\n", 2); return ret; }

template<typename T> int dprhexln(const T& obj) 
	{ int ret = 0; ret += dprhex(obj); ret += debug_write("\r\n", 2); return ret; }

template<typename T> int dprptrln(const T& obj) 
	{ int ret = 0; ret += dprptr(obj); ret += debug_write("\r\n", 2); return ret; }

int dprtab();
int dprtab(uint8_t obj);

#endif //__cplusplus

#include <stdlib.h>
static void abort_dprln(const char* str) {
	debug_print(str);
	dln();
	abort();
}


#endif