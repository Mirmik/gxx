#ifndef GXX_TOKENIZER_H
#define GXX_TOKENIZER_H

#include <gxx/buffer.h>
#include <gxx/gen.h>

namespace gxx {
	template <typename strategy>
	class tokenizer {
	/*	gxx::buffer buf;
		const strategy& strat; 

	public:
		tokenizer(const std::string& str, const strategy& strat) 
			: strat(strat), buf(const_cast<std::string&>(str)) {}

		class iterator {
			gxx::buffer cbuf;
			gxx::buffer nbuf;
		
			iterator(gxx::buffer cbuf, gxx::buffer nbuf) : cbuf() {}
		};

		iterator begin() {
			return iterator();
		}

		iterator end() {
			return iterator(gxx::buffer(nullptr, 0), gxx::buffer(nullptr, 0));
		}
	};

	class char_separator {
		char sep;
	
	public:
		char_separator(char sep) : sep(sep) {};
		gxx::buffer next(char** pptr, size_t* proom) {
			char* start = *pptr;
			char* ptr = *pptr;
			size_t room = *proom;

			if (room == 0) {
				return gxx::buffer(nullptr, 0);
			}

			while(room-- && *ptr != sep) ++ptr;
			
			*pptr = ptr++;
			*proom = room;

			return gxx::buffer(start, ptr - start);
		}*/
	};
}

#endif