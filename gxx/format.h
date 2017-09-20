#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <utility>

#include <gxx/arglist.h>
#include <gxx/io/stdwraper.h>
//#include <gxx/io/debug_ostream.h>

namespace gxx {
	//std::string format_args(const char* fmt, const visitable_arglist& args);
	
	template<typename ... Args>
	std::string format(const char* fmt, Args&& ... args) {
		std::string str;
		gxx::io::std_string_writer(str).format(fmt, std::forward<Args>(args) ...);	
		return str; 
	}
	
	//template<typename ... Args>
	//void dprint(const char* fmt, Args&& ... args) {
	//	gxx::io::debug_ostream out;
	//	gxx::io::format_ostream_writer writer(out);
	//	writer.print(fmt, std::forward<Args>(args) ...);
	//}

	inline namespace print_funcs {
		template<typename ... Args>
		void fmtpr(Args&& ... args) {
			gxx::io::std_ostream_writer(std::cout).format(std::forward<Args>(args) ...);
		}

		template<typename ... Args>
		void fmtprln(Args&& ... args) {
			gxx::io::std_ostream_writer(std::cout).fmtln(std::forward<Args>(args) ...);
		}

		template<typename ... Args>
		void print(Args&& ... args) {
			gxx::io::std_ostream_writer(std::cout).print(std::forward<Args>(args) ...);
		}

		template<typename ... Args>
		void println(Args&& ... args) {
			gxx::io::std_ostream_writer(std::cout).println(std::forward<Args>(args) ...);
		}
	}
}

//#define dprf(...) gxx::dprint(__VA_ARGS__) 

//template<typename ... Args>
//void dprln(const char* fmt, Args&& ... args) {
//	dprf(fmt,std::forward<Args>(args) ...);
//	dprln();
//}

#endif
