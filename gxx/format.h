#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <gxx/utility.h>
#include <gxx/string.h>
#include <gxx/arglist.h>
#include <gxx/io/format_writer.h>

namespace gxx {

	template<typename ... Args>
	gxx::string format(const char* fmt, Args&& ... args) {
		gxx::string retstr;
		retstr.reserve(2*strlen(fmt));
		gxx::io::format_string_writer writer(retstr);
		writer.print(fmt, gxx::forward<Args>(args) ...);
		return retstr;
	}

	gxx::string format_args(const char* fmt, const arglist& args) {
		gxx::string retstr;
		retstr.reserve(2*strlen(fmt));
		gxx::io::format_string_writer writer(retstr);
		writer.print_impl(fmt, args);
		return retstr;
	}

	template<typename ... Args>
	void dprint(const char* fmt, Args&& ... args) {
		gxx::io::debug_strmout out;
		gxx::io::format_stream_writer writer(out);
		writer.print(fmt, gxx::forward<Args>(args) ...);
	}

}

#define dprf(...) gxx::dprint(__VA_ARGS__) 

#endif