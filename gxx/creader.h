#ifndef GXX_CREADER_H
#define GXX_CREADER_H

#include <string>
#include <gxx/buffer.h>

namespace gxx {
	class creader {
		const char* ptr;

	public:
		creader(const char* ptr) : ptr(ptr) {}

		template<typename Functor> 
		std::string string_while(Functor&& func) {
			const char* strt = ptr;
			while(func(*ptr)) ++ptr;
			return std::string(strt, ptr - strt);
		} 

		template<typename Functor> 
		bool next_is(Functor&& func) {
			return func(*ptr);
		}

		bool next_is(char c) {
			return *ptr == c;
		}

		bool next_is(gxx::buffer smbs) {
			int len = smbs.size();
			const char* smb = smbs.data();
			const char* end = smbs.data() + len;
			for(;smb != end; ++smb) {
				if (*ptr == *smb) return true;
			}
			return false;
		}

		void skip() {
			ptr++;
		}

		template<typename Functor> 
		void skip_while(Functor&& func) {
			while(func(*ptr)) ++ptr;	
		}

		void skip_while(const char* smbs) {
			while(true) {	
				const char* strt = ptr;
				const char* smb = smbs;
				while(*smb != 0) {
					while (*ptr == *smb) ptr++;
					smb++;
				}
				if (strt == ptr) return;
			}
		}

		void skip_while(char smb) {
			while(smb == *ptr) ptr++;
		}

		int integer() {
			int ret = atoi(ptr);
			while(isdigit(*ptr)) ++ptr;	
			return ret;
		}
	};
}

#endif