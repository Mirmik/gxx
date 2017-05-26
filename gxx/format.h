#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <assert.h>
#include <gxx/string.h>
#include <gxx/arglist.h>
#include <gxx/buffer.h>
#include <gxx/memory_writer.h>

namespace gxx {
	
	struct format_generic {
		template<typename T> static int genfunc(T* ptr, memory_writer& writer, const char* opts);
		template<typename T> static int genfunc_array(T* ptr, memory_writer& writer, const char* opts);
	};

	inline int format_argument(memory_writer& writer, const char*& fmt, auto& list, uint8_t& argnum) {
		int ret;

		printf("%s\n", "trace:format_argument");
		assert(*fmt++ == '{');

		if (isdigit(*fmt)) {
			argnum = atou32(fmt, 10);
		} 
		while(*fmt != '}' && *fmt != ':' && *fmt != 0) fmt++;
		switch(*fmt) {
			case '}': 
				ret = list.invoke(argnum, writer, nullptr);
				break;
			case ':': 
				ret = list.invoke(argnum, writer, ++fmt);
				break;
			case 0	: 
				return -1;
			default: 
				printf("format internal error");
				abort();
		}
		while(*fmt != '}' && *fmt != 0) fmt++;
		fmt++;
		return ret;
	} 


	template<typename ... Args>
	struct format_helper {
		static string format(const char* fmt, gxx::argument<Args>&& ... args) {
			//__label__ finish;
			uint8_t argnum = 0;
			
			gxx::string str;
			str.reserve(128);
	
			gxx::memory_writer writer(str.data(), str.capacity());
			
			const char* fmtptr = fmt;
	
			auto list = make_arglist<format_generic>(gxx::move(args) ...);
	
			while(*fmtptr != 0) {
				if (*fmtptr == '{') {
					format_argument(writer, fmtptr, list, argnum);
				} else {
					if (writer.write(*fmtptr++) == 0) break;
				}
			}
	
			//finish:
			return str.set_size(writer.size());
		}
	};
	
	template<typename ... T>
	string format(const char* fmt, T&& ... args) {
		return format_helper<T ...>::format(fmt, gxx::forward<T>(args) ...);
	}

	///const char* formater:
	template<> int format_generic::genfunc<gxx::object_buffer<const char>>(gxx::object_buffer<const char>* ptr, memory_writer& w, const char* opts) {
	/*	CaseChange case_change = CaseChange::None;
		Allignment allign = Allignment::Left;

		printf("%s\n", "genfunc(buffer)");
		//size_t size = ptr->size();
		
		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			if (*opts == 'U') { case_change = CaseChange::Upper; continue; }
			if (*opts == '<') { allign = Allignment::Left; continue; }
			if (*opts == '>') { allign = Allignment::Right; continue; }
			if (*opts == '^') { allign = Allignment::Center; continue; }
		}

		w.write_formatted(ptr->data(), ptr->size(), case_change);*/
	}

	template<> int format_generic::genfunc<int>(int* ptr, memory_writer& writer, const char* opts) {
		//printf("%s\n", "genfunc(int)");
	}
}

#endif