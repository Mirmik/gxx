#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <inttypes.h>
#include <stdbool.h>
#include <sys/cdefs.h>

/**
	@file
	2012-2018 mirmik
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

/// Базовая функция вывода символа. 
/// @detail Имплементируется вне библиотеки. 
void debug_putchar(char c);

/// Базовая функция вывода строки указанной длины. 
/// @detail Имплементируется вне библиотеки.
void debug_write(const char* c, int i);

/// Internal strlen implementation
int debug_strlen(const char *c);

// Print null-terminated string
void debug_print(const char *c);

// Print null-terminated string with newline
void debug_print_line(const char *c);

static inline void debug_print_empty_line() {
	debug_putchar('\r');
	debug_putchar('\n');
}

/// Print pointer as hexdecimal uint (in natural endian)
void debug_printhex_ptr(const void* a);

// Debug print boolean as 'true' or 'false'.
void debug_print_bool(uint8_t b);

// Debug print boolean as '1' or '0'.
void debug_print_bool_num(uint8_t b);

/// Hexidecimal integer type`s representation (in natural endian)
void debug_printhex_uint4(uint8_t b);
void debug_printhex_uint8 (uint8_t b);
void debug_printhex_uint16(uint16_t a);
void debug_printhex_uint32(uint32_t a);
void debug_printhex_uint64(uint64_t a);
#define debug_printhex_int4(a) debug_printhex_uint4(a)
#define debug_printhex_int8(a) debug_printhex_uint8(a)
#define debug_printhex_int16(a) debug_printhex_uint16(a)
#define debug_printhex_int32(a) debug_printhex_uint32(a)
#define debug_printhex_int64(a) debug_printhex_uint64(a)

/// Binary integer type`s representation (in natural endian)
void debug_printbin_uint4 (uint8_t b);
void debug_printbin_uint8 (uint8_t b);
void debug_printbin_uint16(uint16_t a);
void debug_printbin_uint32(uint32_t a);
void debug_printbin_uint64(uint64_t a);
#define debug_printbin_int4(a) debug_printbin_uint4(a)
#define debug_printbin_int8(a) debug_printbin_uint8(a)
#define debug_printbin_int16(a) debug_printbin_uint16(a)
#define debug_printbin_int32(a) debug_printbin_uint32(a)
#define debug_printbin_int64(a) debug_printbin_uint64(a)

/// Decimal integer type`s representation
void debug_printdec_uint8 (uint8_t b);
void debug_printdec_uint16(uint16_t a);
void debug_printdec_uint32(uint32_t a);
void debug_printdec_uint64(uint64_t a);
void debug_printdec_int8 (int8_t b);
void debug_printdec_int16(int16_t a);
void debug_printdec_int32(int32_t a);
void debug_printdec_int64(int64_t a);

/// Float types debug print
void debug_printdec_float_prec(float a, int prec);
void debug_printdec_double_prec(double a, int prec);
static inline void debug_printdec_float(float a) {
	debug_printdec_float_prec(a,8);
}
static inline void debug_printdec_double(double a) {
	debug_printdec_double_prec(a,8);
}

void debug_printhex_float(float a);
void debug_printhex_double(double a);

/// Шестнацатеричное представление строки (in machine endian)
void debug_writehex(const void* address, uint16_t size);
void debug_writehex_reversed(const void* address, uint16_t size);

/// Бинарное представление строки (in machine endian)
void debug_writebin(const void* address, uint16_t size);
void debug_writebin_reversed(const void* address, uint16_t size);

/// Вывод дампа памяти в виде размеченной таблицы
void debug_print_dump(const void* address, uint16_t size);

//Тесты для проверки ассемблерной линковки.
void debug_asmlink_test();

uint8_t debug_asmlink_ret8();
uint16_t debug_asmlink_ret16();
uint32_t debug_asmlink_ret32();
uint64_t debug_asmlink_ret64();

void debug_asmlink_args8x1(uint8_t a);
void debug_asmlink_args8x2(uint8_t a, uint8_t b);
void debug_asmlink_args8x3(uint8_t a, uint8_t b, uint8_t c);
void debug_asmlink_args8x4(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

void debug_asmlink_args16x1(uint16_t a);
void debug_asmlink_args16x2(uint16_t a, uint16_t b);
void debug_asmlink_args16x3(uint16_t a, uint16_t b, uint16_t c);
void debug_asmlink_args16x4(uint16_t a, uint16_t b, uint16_t c, uint16_t d);

void debug_asmlink_args32x1(uint32_t a);
void debug_asmlink_args32x2(uint32_t a, uint32_t b);
void debug_asmlink_args32x3(uint32_t a, uint32_t b, uint32_t c);
void debug_asmlink_args32x4(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

void debug_asmlink_args64x1(uint64_t a);
void debug_asmlink_args64x2(uint64_t a, uint64_t b);
void debug_asmlink_args64x3(uint64_t a, uint64_t b, uint64_t c);
void debug_asmlink_args64x4(uint64_t a, uint64_t b, uint64_t c, uint64_t d);

int dprf(const char*, ...);

#define dln() debug_print_empty_line()
#define dprdec(arg) debug_printdec_int64(arg)

void dprptr(const void* ptr);
void dprptrln(const void* ptr);

__END_DECLS

#ifndef __cplusplus

#define dpr(X) _Generic((X), 	 				\
    const char*: 		debug_print, 			\
    char*: 				debug_print, 			\
    uint8_t:			debug_printdec_uint8, 	\
    uint16_t:			debug_printdec_uint16, 	\
    uint32_t:			debug_printdec_uint32, 	\
    uint64_t:			debug_printdec_uint64, 	\
    int8_t:				debug_printdec_int8, 	\
    int16_t:			debug_printdec_int16, 	\
    int32_t:			debug_printdec_int32, 	\
    int64_t:			debug_printdec_int64, 	\
	float:				debug_printdec_float, 	\
    double:				debug_printdec_double, 	\
    bool:				debug_print_bool 		\
)(X)

#define dprhex(X) _Generic((X), 	 			\
    uint8_t:			debug_printhex_uint8, 	\
    uint16_t:			debug_printhex_uint16, 	\
    uint32_t:			debug_printhex_uint32, 	\
    uint64_t:			debug_printhex_uint64, 	\
    int8_t:				debug_printhex_int8, 	\
    int16_t:			debug_printhex_int16, 	\
    int32_t:			debug_printhex_int32, 	\
    int64_t:			debug_printhex_int64, 	\
	float:				debug_printhex_float, 	\
    double:				debug_printhex_double 	\
)(X)

#else 

static inline void dpr(char* obj) { debug_print(obj); }
static inline void dpr(const char* obj) { debug_print(obj); }
static inline void dpr(uint8_t obj) { debug_printdec_uint8(obj); }
static inline void dpr(uint16_t obj) { debug_printdec_uint16(obj); }
static inline void dpr(uint32_t obj) { debug_printdec_uint32(obj); }
static inline void dpr(uint64_t obj) { debug_printdec_uint64(obj); }
static inline void dpr(int8_t obj) { debug_printdec_int8(obj); }
static inline void dpr(int16_t obj) { debug_printdec_int16(obj); }
static inline void dpr(int32_t obj) { debug_printdec_int32(obj); }
static inline void dpr(int64_t obj) { debug_printdec_int64(obj); }
static inline void dpr(double obj) { debug_printdec_double(obj); }
static inline void dpr(float obj) { debug_printdec_float(obj); }
static inline void dpr(bool obj) { debug_print_bool(obj); }

static inline void dprhex(uint8_t obj) { debug_printhex_uint8(obj); }
static inline void dprhex(uint16_t obj) { debug_printhex_uint16(obj); }
static inline void dprhex(uint32_t obj) { debug_printhex_uint32(obj); }
static inline void dprhex(uint64_t obj) { debug_printhex_uint64(obj); }
static inline void dprhex(int8_t obj) { debug_printhex_int8(obj); }
static inline void dprhex(int16_t obj) { debug_printhex_int16(obj); }
static inline void dprhex(int32_t obj) { debug_printhex_int32(obj); }
static inline void dprhex(int64_t obj) { debug_printhex_int64(obj); }
static inline void dprhex(double obj) { debug_printhex_double(obj); }
static inline void dprhex(float obj) { debug_printhex_float(obj); }

#endif

#define dprln(X) do{dpr(X);dln();}while(0)
#define dprhexln(X) do{dprhex(X);dln();}while(0)




#ifdef __cplusplus


template <typename Buffer>
void dpr(const Buffer& obj) {
	debug_write(obj.data(), obj.size());
}

template <typename T, typename ... Tail>
inline void dpr(const T& obj, const Tail& ... tail) {
	dpr(obj);
	debug_putchar(' ');
	dpr(tail ...);
}

/*void dprbin(uint8_t obj);
void dprbin(uint16_t obj);
void dprbin(uint32_t obj);
void dprbin(uint64_t obj);

void dprbin(int8_t obj);
void dprbin(int16_t obj);
void dprbin(int32_t obj);
void dprbin(int64_t obj);
*/


//void dprhex(const char* obj);
//void dprhex(char obj);

/*void dprhex(uint8_t obj);
void dprhex(uint16_t obj);
void dprhex(uint32_t obj);
void dprhex(uint64_t obj);

void dprhex(int8_t obj);
void dprhex(int16_t obj);
void dprhex(int32_t obj);
void dprhex(int64_t obj);
*/

template<typename T>
void dprbin(const T& obj) {
	debug_print_reverse_binary_dump_simple(&obj, sizeof(T));
}

//template<> void dprhex(float obj);
//template<> void dprhex(double obj);
//void dpr(gxx::string obj);

void dpr_dump(const void* obj, uint32_t size);
void dpr_dump_ascii(void* obj, uint32_t size);

template<typename T> void dprptr(const T* const& obj)
	{ debug_printhex_ptr((void*)obj); }

//template<typename ... T> void dprln(const T& ... obj)
//	{ dpr(obj ...); debug_write("\r\n", 2); }

template<typename T> void dprbinln(const T& obj)
	{ dprbin(obj); debug_write("\r\n", 2); }

//template<typename T> void dprhexln(const T& obj)
//	{ dprhex(obj); debug_write("\r\n", 2); }

template<typename T> void dprptrln(const T& obj)
	{ dprptr(obj); debug_write("\r\n", 2); }

void dprtab();
void dprtab(uint8_t obj);

#endif //__cplusplus

#define DTRACE() { debug_print("DTRACE: "); debug_print(__PRETTY_FUNCTION__); debug_print_line(); }

#endif
