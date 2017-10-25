#ifndef GXX_PRINT_H
#define GXX_PRINT_H

#include <gxx/util/print.h>
#include <gxx/io/ostream.h>
#include <gxx/debug/debug_ostream.h>
#include <gxx/io/stdwraper.h>

namespace gxx {
	template<typename Arg> 
	int print(const Arg& arg) {
		gxx::debug_ostream().print(arg);
	}

	template<typename Arg> 
	int print(gxx::io::ostream& out, const Arg& arg) {
		gxx::print_functions<Arg>::print(out, arg);
		//out.print(arg);
	}

	template<typename ... Args> 
	int println(Args&& ... args) {
		print(std::forward<Args>(args) ...);
		gxx::debug_ostream().println();	
	}


	//template<typename ... Args>
	//std::string format(const char* fmt, Args&& ... args) {
	//	std::string str;
	//	gxx::io::std_string_writer(str).fmtprint(fmt, std::forward<Args>(args) ...);	
	//	return str; 
	//}
		
	//template<typename ... Args>
	//void fmtprint(const char* fmt, Args&& ... args) {
	//	gxx::debug_ostream out;
//		out.fmtprint(fmt, std::forward<Args>(args) ...);
//	}
	
//	template<typename ... Args>
//	void fmtprintln(const char* fmt, Args&& ... args) {
//		gxx::debug_ostream out;
//		out.fmtprint(fmt, std::forward<Args>(args) ...);
//		out.println();
//	}
}

#endif