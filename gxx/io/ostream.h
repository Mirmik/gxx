#ifndef GXX_IO_OSTREAM_H
#define GXX_IO_OSTREAM_H

#include <string.h>
#include <string>

namespace gxx {
	namespace io {
		class format_arglist;
		class ostream {
		public:
			virtual int write(const char* str, size_t sz) {
				return writeData(str, sz);
			}

			virtual int putchar(char c) {
				return write(&c,1);
			}

			template<typename ... Args> int print(const char* fmt, Args ... args);
			int print(const char* fmt, const format_arglist& args);
			
			template <typename T>
			int print(const T& obj) {
				return obj.printTo(*this);
			}

			int print(const char* str) {
				return write(str, strlen(str));
			}

			int print(bool obj) {
				return print(obj ? "true" : "false");
			}

			int print(const int8_t obj) { return print("INTEGER"); }
			int print(const int16_t obj) { return print("INTEGER"); }
			int print(const int32_t obj) { return print("INTEGER"); }
			int print(const int64_t obj) { return print("INTEGER"); }

			int print(const uint8_t obj) { return print("INTEGER"); }
			int print(const uint16_t obj) { return print("INTEGER"); }
			int print(const uint32_t obj) { return print("INTEGER"); }
			int print(const uint64_t obj) { return print("INTEGER"); }

			int print(const std::string str) {
				return write(str.data(), str.size());
			}

			template<typename ... Args>
			int println(Args ... args) {
				int ret = print(args ...);
				return ret + write("\r\n", 2);
			}	

		protected: 
			virtual int writeData(const char* str, size_t sz) = 0;
		};
	}
}

#include <gxx/io/printable.h>
#include <gxx/io/fmtarg.h>

template<typename ... Args> int gxx::io::ostream::print(const char* fmt, Args ... args) {
	return print( fmt, gxx::io::__make_format_arglist(std::forward<Args>(args) ...) );
}

#endif
