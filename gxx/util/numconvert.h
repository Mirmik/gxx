#ifndef UTIL_NUMBER_CONVERT
#define UTIL_NUMBER_CONVERT

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <gxx/util/asciiconvert.h>

static inline char *i64toa( int64_t num, char *buf, uint8_t base )
{
	char *p = buf;
	char *p1, *p2;
	uint64_t ud = 0;

	*buf = '\0';	/* initialize buffer. In the case of an error, this will already be in the buffer, indicating that the result is invalid (NULL). */
	p1 = buf;	/* start of buffer */

	// check base
	if( base < 2 || base > 36 )
		{ return buf; }

	/* If num < 0, put `-' in the head.  */
	if( num < 0 )
	{
		*(p++) = '-';
		p1++;
		ud = -num;
	}
	else
		{ ud = num; }

	/* Divide ud by base until ud == 0.  */
	int16_t remainder = 0;
	do {
		remainder = ud % base;
		*(p++) = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while( ud /= base );

	/* Terminate buf.  */
	*p = '\0';

	/* Reverse buffer.  */
	p2 = p - 1;	/* end of buffer */
	char tmp;
	while( p1 < p2 )
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	return buf;
}

static inline char *i32toa( int32_t num, char *buf, uint8_t base ) {
	return i64toa(num, buf, base);
}

static inline char *i16toa( int16_t num, char *buf, uint8_t base ) {
	return i64toa(num, buf, base);
}

static inline char *i8toa( int8_t num, char *buf, uint8_t base ) {
	return i64toa(num, buf, base);
}

static inline char *u64toa( uint64_t num, char *buf, uint8_t base )
{
	char *p = buf;
	char *p1, *p2;
	uint64_t ud = 0;

	*buf = '\0';	/* initialize buffer. In the case of an error, this will already be in the buffer, indicating that the result is invalid (NULL). */
	p1 = buf;	/* start of buffer */

	// check base
	if( base < 2 || base > 36 )
		{ return buf; }

	ud = num;

	/* Divide ud by base until ud == 0.  */
	int16_t remainder = 0;
	do {
		remainder = ud % base;
		*(p++) = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
	} while( ud /= base );

	/* Terminate buf.  */
	*p = '\0';

	/* Reverse buffer.  */
	p2 = p - 1;	/* end of buffer */
	char tmp;
	while( p1 < p2 )
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	return buf;
}

static inline char *u32toa( uint64_t num, char *buf, uint8_t base ) {
	return u64toa(num, buf, base);
}

static inline char *u16toa( uint64_t num, char *buf, uint8_t base ) {
	return u64toa(num, buf, base);
}

static inline char *u8toa( uint64_t num, char *buf, uint8_t base ) {
	return u64toa(num, buf, base);
}

static inline uint32_t atou32(const char *buf, uint8_t base, char** end) {
	char c;
	uint32_t res = 0;
	while(isxdigit(c = *buf++)) {
		res = res * base + sym2byte(c);
	}
	*end = (char*) buf - 1;
	return res; 
}

static inline int32_t atoi32(const char *buf, uint8_t base, char** end) {
	uint8_t minus = 0;
	if (*buf == '-') {
		minus = 1;
		buf++;
	}
	int32_t u = atou32(buf, base, end);
	return minus ? -u : u;
}











/**************************************************
 *
 *    ftoa - converts float to string
 *
 ***************************************************
 *
 *    This is a simple implemetation with rigid
 *    parameters:
 *            - Buffer must be 8 chars long
 *            - 3 digits precision max
 *            - absolute range is -524,287 to 524,287 
 *            - resolution (epsilon) is 0.125 and
 *              always rounds down
 **************************************************/
 /*static void ftoa(float Value, char* Buffer)
 {
	 union
	 {
		 float f;
	 
		 struct
		 {
			 unsigned int    mantissa_lo : 16;
			 unsigned int    mantissa_hi : 7;    
			 unsigned int     exponent : 8;
			 unsigned int     sign : 1;
		 };
	 } helper;
	 
	 unsigned long mantissa;
	 signed char exponent;
	 unsigned int int_part;
	 char frac_part[3];
	 int i, count = 0;
	 
	 helper.f = Value;
	 //mantissa is LS 23 bits
	 mantissa = helper.mantissa_lo;
	 mantissa += ((unsigned long) helper.mantissa_hi << 16);
	 //add the 24th bit to get 1.mmmm^eeee format
	 mantissa += 0x00800000;
	 //exponent is biased by 127
	 exponent = (signed char) helper.exponent - 127;
	 
	 //too big to shove into 8 chars
	 if (exponent > 18)
	 {
		 Buffer[0] = 'I';
		 Buffer[1] = 'n';
		 Buffer[2] = 'f';
		 Buffer[3] = '\0';
		 return;
	 }
	 
	 //too small to resolve (resolution of 1/8)
	 if (exponent < -3)
	 {
		 Buffer[0] = '0';
		 Buffer[1] = '\0';
		 return;
	 }
	 
	 count = 0;
	 
	 //add negative sign (if applicable)
	 if (helper.sign)
	 {
		 Buffer[0] = '-';
		 count++;
	 }
	 
	 //get the integer part
	 int_part = mantissa >> (23 - exponent);    
	 //convert to string
	 i32toa(int_part, &Buffer[count], 10);
	 
	 //find the end of the integer
	 for (i = 0; i < 8; i++)
		 if (Buffer[i] == '\0')
		 {
			 count = i;
			 break;
		 }        
 
	 //not enough room in the buffer for the frac part    
	 if (count > 5)
		 return;
	 
	 //add the decimal point    
	 Buffer[count++] = '.';
	 
	 //use switch to resolve the fractional part
	 switch (0x7 & (mantissa  >> (20 - exponent)))
	 {
		 case 0:
			 frac_part[0] = '0';
			 frac_part[1] = '0';
			 frac_part[2] = '0';
			 break;
		 case 1:
			 frac_part[0] = '1';
			 frac_part[1] = '2';
			 frac_part[2] = '5';            
			 break;
		 case 2:
			 frac_part[0] = '2';
			 frac_part[1] = '5';
			 frac_part[2] = '0';            
			 break;
		 case 3:
			 frac_part[0] = '3';
			 frac_part[1] = '7';
			 frac_part[2] = '5';            
			 break;
		 case 4:
			 frac_part[0] = '5';
			 frac_part[1] = '0';
			 frac_part[2] = '0';            
			 break;
		 case 5:
			 frac_part[0] = '6';
			 frac_part[1] = '2';
			 frac_part[2] = '5';            
			 break;
		 case 6:
			 frac_part[0] = '7';
			 frac_part[1] = '5';
			 frac_part[2] = '0';            
			 break;
		 case 7:
			 frac_part[0] = '8';
			 frac_part[1] = '7';
			 frac_part[2] = '5';                    
			 break;
	 }
	 
	 //add the fractional part to the output string
	 for (i = 0; i < 3; i++)
		 if (count < 7)
			 Buffer[count++] = frac_part[i];
	 
	 //make sure the output is terminated
	 Buffer[count] = '\0';
 }*/


#define MAX_PRECISION   (10)
static const double rounders[MAX_PRECISION + 1] =
{
	0.5,                // 0
	0.05,               // 1
	0.005,              // 2
	0.0005,             // 3
	0.00005,            // 4
	0.000005,           // 5
	0.0000005,          // 6
	0.00000005,         // 7
	0.000000005,        // 8
	0.0000000005,       // 9
	0.00000000005       // 10
};

inline char * ftoa(double f, char * buf, int precision)
{
	if (auto r = __builtin_isinf_sign(f)) {
		*buf++ = r == 1 ? '+' : '-';
		return ::strcpy(buf, "inf");
	}

	char * ptr = buf;
	char * p = ptr;
	char * p1;
	char c;
	long intPart;

	// check precision bounds
	if (precision > MAX_PRECISION)
		precision = MAX_PRECISION;

	// sign stuff
	if (f < 0)
	{
		f = -f;
		*ptr++ = '-';
	}

	if (precision < 0)  // negative precision == automatic precision guess
	{
		if (f < 1.0) precision = 6;
		else if (f < 10.0) precision = 5;
		else if (f < 100.0) precision = 4;
		else if (f < 1000.0) precision = 3;
		else if (f < 10000.0) precision = 2;
		else if (f < 100000.0) precision = 1;
		else precision = 0;
	}

	// round value according the precision
	if (precision)
		f += rounders[precision];

	// integer part...
	intPart = f;
	f -= intPart;

	if (!intPart)
		*ptr++ = '0';
	else
	{
		// save start pointer
		p = ptr;

		// convert (reverse order)
		while (intPart)
		{
			*p++ = '0' + intPart % 10;
			intPart /= 10;
		}

		// save end pos
		p1 = p;

		// reverse result
		while (p > ptr)
		{
			c = *--p;
			*p = *ptr;
			*ptr++ = c;
		}

		// restore end pos
		ptr = p1;
	}

	// decimal part
	if (precision)
	{
		// place decimal point
		*ptr++ = '.';

		// convert
		while (precision--)
		{
			f *= 10.0;
			c = f;
			*ptr++ = '0' + c;
			f -= c;
		}
	}

	// terminating zero
	*ptr = 0;

	return buf;
}


#include <gxx/debug/dprint.h>
static double atod(const char* str, char** pend) {
	if (!isdigit(*str) && *str != '-') {
		return 0;
	}

	char* end;
	int i = atoi32(str, 10, &end);
	uint8_t minus = i < 0 ? 1 : 0; 
	if (minus) {
		i = -i;
	}

	str = end;
	if (*str == '.') {
		int d = atou32(++str, 10, &end);
//		dprln(d);

		*pend = end;
		double ret = (double)i + d / (pow(10, end - str)); 
		return minus ? -ret : ret;
	} else {
		*pend = end;
		return i;
	}
}





#endif
