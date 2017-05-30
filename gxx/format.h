#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <assert.h>
#include <gxx/string.h>
#include <gxx/arglist.h>
#include <gxx/buffer.h>
#include <gxx/memory_writer.h>

#include <gxx/debug/dprint.h>

namespace gxx {
	template<typename T>
	int format_arg(const T& ref, memory_writer&, const char* opts) {
		dprln("FORMATE_ARGUMENT");
	}

	struct format_visitor {
		template<typename T>
		using FuncPtr = int(*)(const T&, memory_writer&, const char* opts); 
		using VoidFuncPtr = int(*)(const void*, memory_writer&, const char* opts); 

		template <typename T>
		static FuncPtr<T> function_pointer() { return &format_arg<T>; }

		static int visit(gxx::argument arg, memory_writer& w, const char* opts);
		static int visit_int64(const int64_t& num, memory_writer& w, const char* opts);
		static int visit_uint64(const uint64_t& i, memory_writer&, const char* opts);
		static int visit_cstring(const char*& str, memory_writer& w, const char* opts);
		static int visit_custom(const gxx::argument::custom_value& c, memory_writer& w, const char* opts);
	};

	int format_argument(memory_writer& writer, const char*& fmt, const gxx::arglist& list, uint8_t& argnum);
	void format_impl(memory_writer& writer, const char* fmt, const gxx::arglist& list);
	string format_impl(const char* fmt, const gxx::arglist& list);

	template<typename ... Args>
	string format(const char* fmt, Args&& ... args) {
		return format_impl(fmt, arglist(gxx::make_argument<format_visitor>(args) ...));
	}
}

#endif