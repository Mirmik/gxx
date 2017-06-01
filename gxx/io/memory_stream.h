#ifndef GXX_MEMORY_WRITER_H
#define GXX_MEMORY_WRITER_H

#include <gxx/io/iostream.h>
#include <gxx/util/numconvert.h>
#include <string.h>

namespace gxx {
	

	class memory_stream : public ostream {
	protected:
		char* m_data;
		char* m_data_end;
		char* m_cursor;

	public:
		memory_stream(char* data, size_t sz) 
			: m_data(data), m_data_end(data + sz), m_cursor(data) {}

		int write(const char* str, size_t sz) override {
			char* sstr = const_cast<char*>(str);
			while(m_cursor != m_data_end && sz--) {
				*m_cursor++ = *str++;
			}
			return str - sstr;

		}

		int putchar(const char c) override {
			if(m_cursor != m_data_end) {
				*m_cursor++ = c;
				return 1; 
			}
			else return 0; 
		}

		CONSTREF_GETTER(data, m_data);
		VALUE_GETTER(size, (m_cursor - m_data));
	};
}

#endif