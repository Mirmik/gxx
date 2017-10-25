#ifndef GXX_UTIL_PRINT_H
#define GXX_UTIL_PRINT_H

#include <gxx/util/numconvert.h>
#include <vector>
#include <array>

namespace gxx {
	namespace io { class ostream; }
	class buffer;

	template<typename T> struct print_functions {
		static int print(gxx::io::ostream& o, const T& i);
		static int format_print(const T& i, gxx::io::ostream& o, gxx::buffer opt);
	};

	template<> struct print_functions<char*> {
		static int print(gxx::io::ostream& o, const char* const& i);
		static int format_print(const char* const& i, gxx::io::ostream& o, gxx::buffer opt);
	};
}

#endif