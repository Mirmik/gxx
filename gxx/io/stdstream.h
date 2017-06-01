#ifndef GXX_STDSTREAM_H
#define GXX_STDSTREAM_H

#include <gxx/io/iostream.h>
#include <unistd.h>

namespace gxx {

	class stdstream : public gxx::iostream {

		virtual int read(char* str, size_t sz) {
			return ::read(1, str, sz);
		}

		virtual int getchar() {
			char c;
			int ret = ::read(1, &c,1);
			return c;
		}

		virtual int write(const char* str, size_t sz) {
			return ::write(0, str, sz);
		}

		virtual int putchar(char c) {
			return ::write(0, &c,1);
		}

	};

}

#endif