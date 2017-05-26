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
					argnum++;
				} else {
					if (writer.putchar(*fmtptr++) == 0) break;
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
		CharStrSpec spec;

		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			switch (*opts) {
				case 'U': spec.charCase(CharCase::Upper); continue;
				case '<': spec.align(Alignment::Left); continue;
				case '>': spec.align(Alignment::Right); continue;
				case '^': spec.align(Alignment::Center); continue;
				case 'f': spec.fill(*++opts); continue;
			}
			if (isdigit(*opts)) { 
				spec.width(atou32(opts, 10)); 
				while(isdigit(*opts)) opts++; 
				opts--;
				continue;
			}
		}

		w.write(ptr->data(), ptr->size(), spec);
	}

	int format_integer(int64_t num, memory_writer& w, const char* opts) {
		IntegerSpec spec;

		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			switch(*opts) {
				case '<': spec.align(Alignment::Left); continue;
				case '>': spec.align(Alignment::Right); continue;
				case '^': spec.align(Alignment::Center); continue;
				case 'f': spec.fill(*++opts); continue;
				case 'X': spec.charCase(CharCase::Upper);
				case 'x': 
					spec.base(16); 
					if ( spec.prefix() == Prefix::Need ) spec.prefix(Prefix::Hex);  
					continue; 
				case 'p': 
					spec.prefix(Prefix::Need); 
			}
			if (isdigit(*opts)) { 
				spec.width(atou32(opts, 10)); 
				while(isdigit(*opts)) opts++; 
				opts--;
				continue;
			}
		}

		w.write_int(num, spec);
	}

	template<> int format_generic::genfunc<int8_t>(int8_t* ptr, memory_writer& w, const char* opts) {
		return format_integer(*ptr, w, opts);
	}
	
	template<> int format_generic::genfunc<int16_t>(int16_t* ptr, memory_writer& w, const char* opts) {
		return format_integer(*ptr, w, opts);
	}

	template<> int format_generic::genfunc<int32_t>(int32_t* ptr, memory_writer& w, const char* opts) {
		return format_integer(*ptr, w, opts);
	}

	template<> int format_generic::genfunc<int64_t>(int64_t* ptr, memory_writer& w, const char* opts) {
		return format_integer(*ptr, w, opts);
	}
}

#endif