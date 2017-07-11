#ifndef GXX_ITERATIBLE_H
#define GXX_ITERATIBLE_H

#include <gxx/gen.h>
#include <gxx/buffer.h>
#include <string.h>

namespace gxx {

	class range {
		int stop;
		int m_value;
	
		using iterator = gxx::gen<int, range>;
	
	public:
		range(int start, int stop) : m_value(start), stop(stop) {}
	
		int& value() {
			return m_value;
		}
	
		bool next() {
			m_value++;
			return m_value == stop;
		}	
	
		iterator begin() {
			return iterator(*this); 
		}
	
		iterator end() {
			return iterator(*this, true);
		}
	};

	class split_tokenizer {
		char* ptr;
		size_t room;
		gxx::buffer m_value;

		char delim;

		using iterator = gxx::gen<gxx::buffer, split_tokenizer>;
	
	public:
		split_tokenizer(const char* str, char dlm) : ptr((char*)str), room(strlen(str)), delim(dlm), m_value(0,0) {}
	
		gxx::buffer& value() {
			return m_value;
		}
	
		bool next() {
			if (room == 0) return true;
			char* start = ptr;

			while(room && (*ptr != delim)) {
				ptr++;
				room--;
			}
			
			m_value = gxx::buffer(start, ptr - start);
			if (room != 0) {
				ptr++;
				room--;	
			}

			return false;
		}	
	
		iterator begin() {
			next();
			return iterator(*this); 
		}
	
		iterator end() {
			return iterator(*this, true);
		}
	};
}

#endif