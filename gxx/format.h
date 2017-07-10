#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <utility>

#include <gxx/arglist.h>
#include <gxx/io/format_writer.h>
#include <gxx/io/debug_ostream.h>

namespace gxx {

	std::string format_args(const char* fmt, const arglist& args);
	
	template<typename ... Args>
	std::string format(const char* fmt, Args&& ... args) {
		return format_args(fmt, gxx::arglist(gxx::make_argument<format_visitor>(gxx::make_argument_temporary(std::forward<Args>(args))) ...));	
	}
	
	template<typename ... Args>
	void dprint(const char* fmt, Args&& ... args) {
		gxx::io::debug_ostream out;
		gxx::io::format_stream_writer writer(out);
		writer.print(fmt, std::forward<Args>(args) ...);
	}

	inline namespace print_funcs {
		template<typename ... Args>
		void print(const char* fmt, Args&& ... args) {
			gxx::io::format_stream_writer writer(std::cout);
			writer.print(fmt, std::forward<Args>(args) ...);
		}

		template<typename ... Args>
		void println(const char* fmt, Args&& ... args) {
			gxx::io::format_stream_writer writer(std::cout);
			writer.println(fmt, std::forward<Args>(args) ...);
		}
	}
}

#define dprf(...) gxx::dprint(__VA_ARGS__) 

template<typename ... Args>
void dprln(const char* fmt, Args&& ... args) {
	dprf(fmt,std::forward<Args>(args) ...);
	dprln();
}

#endif