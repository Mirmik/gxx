#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <gxx/utility.h>
#include <gxx/string.h>
#include <gxx/arglist.h>
#include <gxx/io2/format_writer.h>

namespace gxx {

	template<typename ... Args>
	gxx::string format(const char* fmt, Args&& ... args) {
		gxx::string retstr;
		retstr.reserve(2*strlen(fmt));

		gxx::io::format_string_writer writer(retstr);
		writer.print(fmt, gxx::forward<Args>(args) ...);
		return retstr;
	}

}

#endif