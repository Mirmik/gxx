#ifndef GXX_UTIL_PRINT_H
#define GXX_UTIL_PRINT_H

#include <gxx/util/numconvert.h>
#include <gxx/io/ostream.h>
#include <vector>
#include <array>

namespace gxx {
	template <typename T, typename U = int>
	struct IsPrintable : std::false_type { };

	template <typename T>
	struct IsPrintable <T, decltype((void) T::fmtPrintTo, 0)> : std::true_type { };

	namespace io { class ostream; }
	class buffer;

	template<typename T> struct print_functions {
		static int print(gxx::io::ostream& o, const T& obj) { return o.print(obj); };
	};

	template<typename T, bool Printable = true> struct fprint_functions_basic {
		static int format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt) { 
			return obj.fmtPrintTo(o, opt); 
		};
	};

	template<typename T> struct fprint_functions_basic<T, false> {
		static int format_print(const T& obj, gxx::io::ostream& o, gxx::buffer opt) { 
			return print_functions<T>::print(o, obj); 
		};
	};

	template<typename T> struct fprint_functions : public fprint_functions_basic<T, IsPrintable<T>::value> {};

	template<> struct fprint_functions<char*> {
		static int format_print(const char* const obj, gxx::io::ostream& o, gxx::buffer opt) { 
			return print_functions<const char*>::print(o, obj); 
		};
	};
}

#endif