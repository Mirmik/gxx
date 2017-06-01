#ifndef GXX_IOSTREAM_H
#define GXX_IOSTREAM_H

#include <stdlib.h>
#include <gxx/debug/dprint.h>

namespace gxx {
	
	class istream {
	public:
		virtual int read(char* str, size_t sz) = 0;
		virtual int getchar() = 0;
	};
	
	class ostream {
	public:
		virtual int write(const char* str, size_t sz) = 0;
		virtual int putchar(char c) = 0;

		int print(const char* str) {
			write(str, strlen(str));
		}
	};
	
	class iostream : public istream, public ostream {};
	
	class debug_ostream : public ostream {
	public:
		int write(const char* str, size_t sz) override {
			return debug_write(str, sz);
		}
		
		int putchar(const char c) override {
			return debug_putchar(c);
		}
	};

}

#endif