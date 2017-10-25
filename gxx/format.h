#ifndef GXX_FORMAT_H
#define GXX_FORMAT_H

#include <utility>

#include <iostream>
#include <gxx/arglist.h>
#include <gxx/io/stdwraper.h>
#include <gxx/debug/debug_ostream.h>

namespace gxx {
	//std::string format_args(const char* fmt, const visitable_arglist& args);
	
	//namespace fmt {
	

	/*inline namespace print_funcs {
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
	}*/
	}
}

//#define dprf(...) gxx::dprint(__VA_ARGS__) 

//template<typename ... Args>
//void dprln(const char* fmt, Args&& ... args) {
//	dprf(fmt,std::forward<Args>(args) ...);
//	dprln();
//}

#endif
