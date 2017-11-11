#ifndef GXX_PRINT_H
#define GXX_PRINT_H

#include <gxx/util/print.h>
#include <gxx/fmt/format.h>
#include <gxx/io/ostream.h>
#include <gxx/debug/debug_ostream.h>
#include <gxx/arglist.h>
#include <gxx/io/stdstream.h>

namespace gxx {
	template<typename Arg> 
	int print(gxx::io::ostream& out, const Arg& arg) {
		gxx::print_functions<Arg>::print(out, arg);
	}
	
	template<typename Arg> 
	int print(const Arg& arg) {
		gxx::debug_ostream out;
		gxx::print(out, arg);
	}

	template<typename ... Args> 
	int println(Args&& ... args) {
		print(std::forward<Args>(args) ...);
		gxx::debug_ostream().println();	
	}

	inline int fprint_format_argument(gxx::io::ostream& out, const char*& fmt, const gxx::visitable_arglist& list, uint8_t argnum) {
		int ret;		
		char* pend;
		assert(*fmt++ == '{');
		
		const visitable_argument* varg = nullptr;
		
		if (isalpha(*fmt)) {
			const char* count_ptr = fmt;
			int len = 0;
			while(isalpha(*count_ptr++)) len++;
			varg = &list[gxx::buffer(fmt, len)];
		} else if (isdigit(*fmt)) {
			varg = &list[atou32(fmt, 10, &pend)];
		} else {
			varg = &list[argnum];
		}
		
		while(*fmt != '}' && *fmt != ':' && *fmt != 0) fmt++;
		switch(*fmt) {
			case '}': 
				ret = gxx::fmt::format_visitor::visit(*varg, out, gxx::buffer());
				break;
			case ':': 
				++fmt;
				ret = gxx::fmt::format_visitor::visit(*varg, out, gxx::buffer(fmt, strchr(fmt, '}') - fmt));
				break;
			case 0	: 
				return -1;
			default: 
				dprln("format internal error");
				abort();
		}
		while(*fmt != '}' && *fmt != 0) fmt++;
		fmt++;
		return ret;
	}

	inline int fprint_impl(gxx::io::ostream& out, const char* fmt, const visitable_arglist& args) {
		uint8_t argnum = 0;
		const char* fmtptr = fmt;
		size_t ret = 0;

		while(*fmtptr != 0) {
			if (*fmtptr == '{') {
				ret += fprint_format_argument(out, fmtptr, args, argnum);
				argnum++;
			} else {
				auto strttxt = fmtptr;
				while (*fmtptr != 0 && *fmtptr != '{') fmtptr++;
				ret += out.write(strttxt, fmtptr - strttxt);
			}
		}
		return ret;
	}

	template<typename ... Args>
	int fprint(gxx::io::ostream& out, const char* fmt, Args&& ... args) {
		visitable_argument buffer[sizeof ... (Args)];
		return fprint_impl(out, fmt, gxx::make_visitable_arglist<gxx::fmt::format_visitor>(buffer, std::forward<Args>(args) ...));		
	}
		
	template<typename ... Args>
	int fprint(const char* fmt, Args&& ... args) {
		gxx::debug_ostream out;
		gxx::fprint(out, fmt,  std::forward<Args>(args) ...);		
	}
		
	template<typename ... Args> 
	int fprintln(Args&& ... args) {
		fprint(std::forward<Args>(args) ...);
		gxx::debug_ostream().println();	
	}

	template<typename ... Args>
	std::string format(const char* fmt, Args&& ... args) {
		std::string str;
		gxx::io::ostringstream writer(str);
		gxx::fprint(writer, fmt, std::forward<Args>(args) ...);
		return str; 
	}

	template<typename Arg>
	std::string to_string(Arg&& arg) {
		std::string str;
		gxx::io::ostringstream writer(str);
		gxx::print(writer, std::forward<Arg>(arg));
		return str; 
	}
}

#endif
