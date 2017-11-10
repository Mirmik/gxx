#ifndef GXX_SLINE_H
#define GXX_SLINE_H

#include <gxx/buffer.h>

namespace gxx {
	class sline {
		char* data;
		size_t capacity;
		size_t cursor;

	public:
		sline(gxx::buffer buf) : data(buf.data()), capacity(buf.size()), cursor(0) {}

		void back(int n) {
			cursor -= n;
		}

		void init() {
			cursor = 0;
		}

		int putchar(char c) {
			*(data + cursor) = c;
			cursor++;
		}

		operator gxx::buffer() {
			return gxx::buffer(data, cursor);
		}
	};
}

#endif