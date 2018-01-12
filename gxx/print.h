#ifndef GXX_PRINT_H
#define GXX_PRINT_H

#include <gxx/print/meta.h>
#include <gxx/print/format.h>
#include <gxx/io/ostream.h>
#include <gxx/io/stdstream.h>
#include <gxx/arglist.h>

namespace gxx {
	extern gxx::io::ostream* stdout;

	template<typename Arg> 
	int print_to(gxx::io::ostream& out, const Arg& arg) {
		gxx::print_functions<Arg>::print(out, arg);
	}
	
	template<typename Head, typename ... Tail> 
	int print_to(gxx::io::ostream& out, const Head& head, const Tail& ... tail) {
		print_to(out, head);
		out.putchar(' ');
		print_to(out, tail ...);
	}
	
	template<typename ... Args> 
	int println_to(gxx::io::ostream& out, const Args& ... args) {
		print_to(out, args ...);
		out.println();	
	}

	template<typename Arg> 
	int print(const Arg& arg) {
		gxx::print_to(*stdout, arg);
	}

	template<typename Head, typename ... Tail> 
	int print(const Head& head, const Tail& ... tail) {
		print(head);
		stdout->putchar(' ');
		print(tail ...);
	}
	
	template<typename ... Args> 
	int println(const Args& ... args) {
		print(args ...);
		stdout->println();	
	}

	template<typename C>
	int print_as_matrix(const C& c, int rlen) {
		int n = 0;
		for (const auto& v : c) {
			stdout->print(v); 
			stdout->putchar(' ');
			++n;
			if (n == rlen) {
				n = 0;
				stdout->println();
			}
		}
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
		//gxx::debug_ostream out;
		gxx::fprint(*stdout, fmt,  std::forward<Args>(args) ...);		
	}
		
	template<typename ... Args> 
	int fprintln(Args&& ... args) {
		fprint(std::forward<Args>(args) ...);
		stdout->println();	
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
