#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <assert.h>
#include <gxx/string.h>
#include <gxx/arglist.h>
#include <gxx/buffer.h>
#include <gxx/memory_writer.h>

#include <gxx/debug/dprint.h>

namespace gxx {
	
	struct format_generic {
		template<typename T> static int genfunc(T* ptr, memory_writer& writer, const char* opts);
		template<typename T> static int genfunc_array(T* ptr, size_t sz, memory_writer& writer, const char* opts);
	};

	inline int format_argument(memory_writer& writer, const char*& fmt, const gxx::arglist<format_generic>& list, uint8_t& argnum) {
		int ret;

		assert(*fmt++ == '{');

		if (isdigit(*fmt)) {
			argnum = atou32(fmt, 10);
		} 

		if (isalpha(*fmt)) {
			const char* count_ptr = fmt;
			int len = 0;
			while(isalpha(*count_ptr++)) len++;
			argnum = list.find_name(fmt,len);
			if (argnum == 0xFF) return -1;
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
	
	void format_impl(memory_writer& writer, const char* fmt, const gxx::arglist<format_generic>& list) {
		uint8_t argnum = 0;
		const char* fmtptr = fmt;
	
		while(*fmtptr != 0) {
			if (*fmtptr == '{') {
				format_argument(writer, fmtptr, list, argnum);
				argnum++;
			} else {
				if (writer.putchar(*fmtptr++) == 0) break;
			}
		}
	}

	string format_impl(const char* fmt, const gxx::arglist<format_generic>& list) {
		gxx::string str;
		str.reserve(128);
		gxx::memory_writer writer(str.data(), str.capacity());
		format_impl(writer, fmt, list);
		return str.set_size(writer.size());
	}

	template<typename ... Args>
	string format(const char* fmt, Args&& ... args) {
		return format_impl(fmt, make_arglist<format_generic>(args ...));
	}

	///const char* formater:
	template<> 
	int format_generic::genfunc_array<const char*>(const char* ptr, size_t sz, memory_writer& w, const char* opts) {
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

		w.write(ptr, sz, spec);
	}

	template<> 
	int format_generic::genfunc<const char*>(const char* ptr, size_t sz, memory_writer& w, const char* opts) {
		return format_generic::genfunc_array<char>(ptr, sz, w, opts);
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