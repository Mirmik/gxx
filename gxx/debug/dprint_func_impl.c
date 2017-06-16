#include <gxx/debug/dprint.h>
#include <stdint.h>
//#include <stdio.h>
#include <ctype.h>

int debug_printhex_uint4(uint8_t b){
	uint8_t c = b < 10 ? b + '0' : b + 'A' - 10;
	return debug_putchar(c);
}

int debug_printhex_uint8 (uint8_t b){
	int ret = 0;
	ret += debug_printhex_uint4((b & 0xF0)>>4);	
	ret += debug_printhex_uint4(b & 0x0F);
	return ret;
}
	
int debug_printbin_uint8 (uint8_t b){
	int ret = 0;
	ret += debug_putchar((b & 0x80) ? '1': '0');
	ret += debug_putchar((b & 0x40) ? '1': '0');
	ret += debug_putchar((b & 0x20) ? '1': '0');
	ret += debug_putchar((b & 0x10) ? '1': '0');
	ret += debug_putchar((b & 0x08) ? '1': '0');
	ret += debug_putchar((b & 0x04) ? '1': '0');
	ret += debug_putchar((b & 0x02) ? '1': '0');
	ret += debug_putchar((b & 0x01) ? '1': '0');
	return ret;
}

int debug_printhex_uint32(uint32_t a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printhex_uint8(*(p+3));
	ret += debug_printhex_uint8(*(p+2));
	ret += debug_printhex_uint8(*(p+1));
	ret += debug_printhex_uint8(*(p+0));
	return ret;
}

int debug_printhex_uint64(uint64_t a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printhex_uint8(*(p+7));
	ret += debug_printhex_uint8(*(p+6));
	ret += debug_printhex_uint8(*(p+5));
	ret += debug_printhex_uint8(*(p+4));
	ret += debug_printhex_uint8(*(p+3));
	ret += debug_printhex_uint8(*(p+2));
	ret += debug_printhex_uint8(*(p+1));
	ret += debug_printhex_uint8(*(p+0));
	return ret;
}

int debug_printhex_uint16(uint16_t a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printhex_uint8(*(p+1));
	ret += debug_printhex_uint8(*(p+0));
	return ret;
}

int debug_printbin_uint32(uint32_t a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printbin_uint8(*(p+3));
	ret += debug_printbin_uint8(*(p+2));
	ret += debug_printbin_uint8(*(p+1));
	ret += debug_printbin_uint8(*(p+0));
	return ret;
}

int debug_printbin_uint64(uint64_t a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printbin_uint8(*(p+7));
	ret += debug_printbin_uint8(*(p+6));
	ret += debug_printbin_uint8(*(p+5));
	ret += debug_printbin_uint8(*(p+4));
	ret += debug_printbin_uint8(*(p+3));
	ret += debug_printbin_uint8(*(p+2));
	ret += debug_printbin_uint8(*(p+1));
	ret += debug_printbin_uint8(*(p+0));
	return ret;
}

int debug_printbin_uint16(uint16_t a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printbin_uint8(*(p+1));
	ret += debug_printbin_uint8(*(p+0));
	return ret;
}

int debug_printdec_float(float a, int prec)
{
	int ret = 0;
	ret += debug_printdec_double((double)a, prec);
	return ret;
}

int debug_printdec_double(double a, int prec) {	
	int ret = 0;
	int64_t n = (int64_t) a;
	ret += debug_printdec_int64 ( n );
	ret += debug_putchar('.');
	double o = a - n;
	for(int _iteration = 0; _iteration < prec; ++_iteration ) 
		o *= 10;
	o += 0.5;
	ret += debug_printdec_int64 ( o );
	return ret;
}

#ifdef sp_float
int debug_printbin_spf(sp_float a) {
	int ret = 0;
	uint8_t *p =(uint8_t*) &a;
	ret += debug_printbin_uint8(*(p+3));
	ret += debug_printbin_uint8(*(p+2));
	ret += debug_printbin_uint8(*(p+1));
	ret += debug_printbin_uint8(*(p+0));
	return ret;
}
#endif

int debug_printhex_ptr(int* v) {
	int ret = 0;
	#if __WORDSIZE == 8 
		ret += debug_printhex_uint8 ((uint8_t )v);
	#elif __WORDSIZE == 16
		ret += debug_printhex_uint16((uint16_t)v);
	#elif __WORDSIZE == 32
		ret += debug_printhex_uint32((uint32_t)v);
	#elif __WORDSIZE == 64
		ret += debug_printhex_uint64((uint64_t)v);
	#else
		#error "Wrong __WORDSIZE"
	#endif
	return ret;
}
	


int debug_strlen(const char *c)
{	
	int i;
	for(i=0;c[i]!=0;i++);
	return i;
}

int debug_print(const char *c)
{	
	return debug_write((char*)c, debug_strlen(c));	
}

int debug_print_line()
{	
	int ret = 0;
	ret += debug_putchar('\r');	
	ret += debug_putchar('\n');
	return ret;
}

int debug_print_bool(uint8_t b)
{
	int ret = 0;
	ret += debug_print(b ? "true" : "false");	
	return ret;
}

int debug_print_bool_num(uint8_t b)
{
	int ret = 0;
	ret += debug_putchar(b ? '1' : '0');	
	return ret;
}

int debug_print_test()
{
	int ret = 0;
	ret += debug_putchar('G');
	ret += debug_printhex_uint32(0xABCDEF00);
	ret += debug_putchar('\n');debug_putchar('\r');
	ret += debug_print("DEBUG_print_TEST\n\r");	
	return ret;	
}

/*int debug_print_dump(const void* address, uint16_t size)
{
	//debug_printhex_ptr(address);
	//debug_printhex_uint16(size);
	//while(1);
	int ret = 0;
	
	uint8_t* dump = (uint8_t*) address; 
	uintptr_t addr_tmp = (uintptr_t) address;
	uint32_t i = 0;
	uint32_t mark = 0;
	
	for (i = 0; i < size; i++)
	{
		
		if (mark == 0)
		{
			ret += debug_printhex_uint32(addr_tmp);
			ret += debug_putchar(':');
			ret += debug_putchar(' ');
		}
		
		ret += debug_printhex_uint8(dump[i]);
		
		if ( mark == 7 )
		{
			ret += debug_putchar('|');
			mark++;
		}
		else if ( mark == 15 )
		{
			ret += debug_putchar('\n');
			ret += debug_putchar('\r');
			mark = 0;
			
			addr_tmp += 0x10;
		}
		else
		{
			ret += debug_putchar(' ');
			mark++;
		}
	} 
	ret += debug_putchar('\n');
	ret += debug_putchar('\r');
	return ret;	
}*/

int debug_print_dump(const void *mem, uint16_t len) {
	uint16_t i, j;
	int HEXDUMP_COLS = 8;
	
	for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++) {
		/* print offset */
		if(i % HEXDUMP_COLS == 0) {
			debug_printhex_ptr((void*)(i + mem));
			debug_putchar(':');
		}

		/* print hex data */
		if(i < len) {
			debug_printhex_uint8(((char*)mem)[i]);
			debug_putchar(' ');
		}

		/* end of block, just aligning for ASCII dump */
		else {
			debug_print("   ");
		}
		
		/* print ASCII dump */
		if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)) {
			for(j = i - (HEXDUMP_COLS - 1); j <= i; j++) {
				
				/* end of block, not really printing */
				if(j >= len) {
					debug_putchar(' ');
				}

				/* printable char */
				else if(isprint(((char*)mem)[j])) {
					debug_putchar(0xFF & ((char*)mem)[j]);        
				}

				/* other char */
				else {
					debug_putchar('.');
				}
			}
			debug_putchar('\n');
		}
	}
}

int debug_print_dump_ascii(const void* address, uint16_t size)
{
	int ret = 0;
	uint8_t* dump = (uint8_t*) address; 
	uintptr_t addr_tmp = (uintptr_t) address;
	uint32_t i = 0;
	uint32_t mark = 0;
	
	for (i = 0; i < size; i++)
	{
		
		if (mark == 0)
		{
			ret += debug_printhex_uint32(addr_tmp);
			ret += debug_putchar(':');
			ret += debug_putchar(' ');
		}
		
		ret += debug_putchar(dump[i]);
		
		if ( mark == 7 )
		{
			ret += debug_putchar(' ');
			mark++;
		}
		else if ( mark == 15 )
		{
			ret += debug_putchar('\n');
			ret += debug_putchar('\r');
			mark = 0;
			
			addr_tmp += 0x10;
		}
		else
		{
			ret += debug_putchar(' ');
			mark++;
		}
	} 
	ret += debug_putchar('\n');
	ret += debug_putchar('\r');
	return ret;	
}

int debug_print_dump_simple(void* ptr, uint16_t size)
{
	int ret = 0;
	uint8_t* _ptr = (uint8_t*) ptr;
	while(size--) {ret += debug_printhex_uint8(*_ptr++);}
	return ret;	
}

int debug_printdec_int8  (int8_t   x) { return debug_printdec_int64( x ); }
int debug_printdec_int16 (int16_t  x) { return debug_printdec_int64( x ); }
int debug_printdec_int32 (int32_t  x) { return debug_printdec_int64( x ); }
int debug_printdec_int64 (int64_t  x) {
	int ret = 0;
	if (x<0) {
		x=-x; 
		ret += debug_putchar('-');
	} 
	ret += debug_printdec_uint64(x);
	return ret;
}

int debug_printdec_uint8 (uint8_t  x) { return debug_printdec_uint64( x ); }
int debug_printdec_uint16(uint16_t x) { return debug_printdec_uint64( x ); }
int debug_printdec_uint32(uint32_t x) { return debug_printdec_uint64( x ); }
int debug_printdec_uint64(uint64_t x) {
	int ret = 0;
	char c[24];
	char* end_buf = c + 24;
	char* ptr = end_buf;
	if (x==0) ret += debug_putchar('0');
	*--ptr='\0';
	for (; x != 0; x /= 10)
	{
		*--ptr = ((x % 10) + '0');
	}
	ret += debug_print(ptr);
	return ret;
}

int debug_asmlink_test(){
	int ret = 0;
	ret += debug_putchar('A');
	ret += debug_putchar('B');
	ret += debug_putchar('C');
	ret += debug_putchar('D');
	ret += debug_putchar('E');
	ret += debug_putchar('1');
	ret += debug_putchar('2');
	ret += debug_putchar('3');
	ret += debug_putchar('4');
	ret += debug_putchar('5');
	return ret;
}


int debug_asmlink_uint16_dpr(uint16_t a) {
	int ret = 0;
	ret += debug_printhex_uint16(a); ret+= debug_putchar(':');
	return ret;
}

int debug_asmlink_uint16_dpr2(uint16_t a, uint16_t b) {
	int ret = 0;
	ret += debug_printhex_uint16(a); ret+= debug_putchar(':');
	ret += debug_printhex_uint16(b); ret+= debug_putchar(':');
	return ret;
}

int debug_asmlink_uint16_dpr4(uint16_t a, uint16_t b, uint16_t c, uint16_t d) {
	int ret = 0;
	ret += debug_printhex_uint16(a); ret+= debug_putchar(':');
	ret += debug_printhex_uint16(b); ret+= debug_putchar(':');
	ret += debug_printhex_uint16(c); ret+= debug_putchar(':');
	ret += debug_printhex_uint16(d); ret+= debug_putchar(':');
	return ret;
}

int debug_asmlink_uint8_dpr4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
	int ret = 0;
	ret += debug_printhex_uint8(a); ret+= debug_putchar(':');
	ret += debug_printhex_uint8(b); ret+= debug_putchar(':');
	ret += debug_printhex_uint8(c); ret+= debug_putchar(':');
	ret += debug_printhex_uint8(d); ret+= debug_putchar(':');
	return ret;
}

int debug_asmlink_uint8_dpr3(uint8_t a, uint8_t b, uint8_t c) {
	int ret = 0;
	ret += debug_printhex_uint8(a); ret+= debug_putchar(':');
	ret += debug_printhex_uint8(b); ret+= debug_putchar(':');
	ret += debug_printhex_uint8(c); ret+= debug_putchar(':');
	return ret;
}

int debug_asmlink_uint8_dpr2(uint8_t a, uint8_t b) {
	int ret = 0;
	ret += debug_printhex_uint8(a); ret+= debug_putchar(':');
	ret += debug_printhex_uint8(b); ret+= debug_putchar(':');
	return ret;
}

int debug_asmlink_uint8_dpr1(uint8_t a) {
	int ret = 0;
	ret += debug_printhex_uint8(a); ret+= debug_putchar(':');
	return ret;
}

uint16_t debug_asmlink_test_uint16_ret()
{
	return 0xACAB;
}

uint64_t debug_asmlink_test_uint64_ret()
{
	return 0x0123456789ABCDEF;
}
/*	uint16_t debug_simple_test_uint16_2(uint16_t a, uint16_t b)
	{
	debug_printhex_uint16(a);debug_putchar(':');
	debug_printhex_uint16(b);debug_putchar(':');
	return 0xACAB;
	}
	
	uint16_t debug_simple_test_uint16_1(uint16_t a)
	{
	debug_printhex_uint16(a);debug_putchar(':');
	return 0xACAB;
}*/
