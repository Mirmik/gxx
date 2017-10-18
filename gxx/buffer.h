#ifndef GENOS_UTILXX_BUFFER_H
#define GENOS_UTILXX_BUFFER_H

#include <string>
#include <string.h>
#include <stdlib.h>

#include <gxx/util/setget.h>

namespace gxx {
	class buffer {
		char* buf;
		size_t sz;
	public:
		buffer() : buf(nullptr), sz(0) {}
		buffer(const char* buf) : buf((char*)buf), sz(strlen(buf)) {}
		buffer(const void* buf, size_t sz) : buf((char*)buf), sz(sz) {}
		buffer(const std::string& str) : buf((char*)str.data()), sz(str.size()) {}

		template<typename T, size_t N>
		inline buffer(T (&arr) [N]) : buf((char*)arr), sz(N) {}

		//bool empty() { return buf == nullptr; }

		bool operator==(const buffer& other) const {
			return (sz == other.sz) && (strncmp(buf, other.buf, sz < other.sz ? sz : other.sz) == 0);
		}

		ACCESSOR(data, buf);
		ACCESSOR(size, sz);

		bool empty() {
			return buf == nullptr;
		}
	};

	static inline gxx::buffer allocate_buffer(int sz) {
		void* ptr = malloc(sz);
		return gxx::buffer(ptr, sz);
	}

	class line_buffer {
		char* m_data;
		char* m_end;
		char* m_cursor;

		line_buffer(const void* buf, size_t sz);


	};
}

#endif 
