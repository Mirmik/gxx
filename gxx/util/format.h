#ifndef GXX_UTIL_FORMAT_H
#define GXX_UTIL_FORMAT_H

#include <gxx/string.h>
#include <gxx/arglist.h>

namespace gxx {
	namespace io {
		class format_writer;
	}

	template<typename T>
	int format_arg(T& ref, io::format_writer&, const char* opts) {
		dprln("FORMAT_UNREGISTRED_ARGUMENT");
		return 0;
	}

	template<>int format_arg(const int8_t& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const int16_t& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const int32_t& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const int64_t& ptr, io::format_writer&, const char* opts);

	template<>int format_arg(const uint8_t& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const uint16_t& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const uint32_t& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const uint64_t& ptr, io::format_writer&, const char* opts);

	template<>int format_arg(const char* const& ptr, io::format_writer&, const char* opts);
	template<>int format_arg(const gxx::string& ptr, io::format_writer&, const char* opts);

	struct format_visitor {
		template<typename T>
		using FuncPtr = int(*)(T&, io::format_writer&, const char* opts); 
		using VoidFuncPtr = int(*)(const void*, io::format_writer&, const char* opts); 

		template <typename T>
		static FuncPtr<T> function_pointer() { 
			return &format_arg<T>; 
		}

		static int visit(gxx::argument arg, io::format_writer& w, const char* opts);
	};
}

#endif