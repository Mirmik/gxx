#ifndef GXX_WRITER_H
#define GXX_WRITER_H

#include <gxx/debug/dprint.h>
#include <gxx/util/numconvert.h>
#include <gxx/io/iostream.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

namespace gxx {
	class writer {
		ostream& out;

	public:
		writer(ostream& out) : out(out) {}

		virtual int write(const char* str, size_t sz) {
			return out.write(str, sz);
		}

		virtual int putchar(char c) {
		 	return out.putchar(c);
		}
	};

	
}

#endif