#ifndef GXX_WRITER_H
#define GXX_WRITER_H

#include <gxx/io2/strm.h>

namespace gxx {
	namespace io {
		class writer {
			strmout& out;
	
		public:
			writer(strmout& out) : out(out) {}
	
			int write(const char* str, size_t sz) {
				return out.write(str, sz);
			}
	
			int putchar(char c) {
			 	return out.putchar(c);
			}
		};
	}
}

#endif