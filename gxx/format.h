#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <assert.h>
#include <gxx/string.h>
#include <gxx/arglist.h>
#include <gxx/buffer.h>
#include <gxx/io/text_writer.h>
#include <gxx/io/memory_stream.h>

#include <gxx/debug/dprint.h>

namespace gxx {
	template<typename T>
	int format_arg(T& ref, text_writer&, const char* opts) {
		dprln("FORMATE_ARGUMENT");
		return 0;
	}

	template<>int format_arg(const int8_t& ptr, text_writer&, const char* opts);
	template<>int format_arg(const int16_t& ptr, text_writer&, const char* opts);
	template<>int format_arg(const int32_t& ptr, text_writer&, const char* opts);
	template<>int format_arg(const int64_t& ptr, text_writer&, const char* opts);

	template<>int format_arg(const uint8_t& ptr, text_writer&, const char* opts);
	template<>int format_arg(const uint16_t& ptr, text_writer&, const char* opts);
	template<>int format_arg(const uint32_t& ptr, text_writer&, const char* opts);
	template<>int format_arg(const uint64_t& ptr, text_writer&, const char* opts);

	template<>int format_arg(const char* const& ptr, text_writer&, const char* opts);
	template<>int format_arg(const gxx::string& ptr, text_writer&, const char* opts);

	struct format_visitor {
		template<typename T>
		using FuncPtr = int(*)(T&, text_writer&, const char* opts); 
		using VoidFuncPtr = int(*)(const void*, text_writer&, const char* opts); 

		template <typename T>
		static FuncPtr<T> function_pointer() { 
			//pretty_that_function();dln();
			return &format_arg<T>; 
		}

		static int visit(gxx::argument arg, text_writer& w, const char* opts);
	};

	int format_argument(text_writer& writer, const char*& fmt, const gxx::arglist& list, uint8_t& argnum);
	void format_impl(text_writer& writer, const char* fmt, const gxx::arglist& list);

	string format_impl(const char* fmt, const gxx::arglist& list);

	template<typename ... T>
	string format(const char* fmt, T&& ... args) {
		return format_impl(fmt, gxx::arglist(gxx::make_argument<format_visitor>(gxx::make_argument_temporary(gxx::forward<T>(args))) ...));
	}	
}

#define dprf(...) dprln(gxx::format(__VA_ARGS__));

#endif