#ifndef GXX_HISTORY_H
#define GXX_HISTORY_H

#include <string>
#include <gxx/ring.h>
#include <gxx/bytearray.h>

namespace gxx {
	class history {
		gxx::ring<gxx::bytearray> hist;

	public:
		history(int histlen) : hist(histlen) {}

		void push_string(const char* data, size_t size) {
			hist.emplace(data, size);
		}

		void push_string(const char* data) {
			if (hist.size() == hist.capacity()) hist.pop();
			hist.emplace(data, strlen(data));
		}

		gxx::bytearray& operator[](int i) {
			return hist[i];
		}
	};
}

#endif