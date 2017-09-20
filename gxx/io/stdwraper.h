#ifndef GXX_SSTREAM_H
#define GXX_SSTREAM_H

#include <gxx/io/ostream.h>

namespace gxx {
	namespace io {
		class std_string_writer : public gxx::io::ostream {
			std::string& str;
		public:
			std_string_writer(std::string& str) : str(str) {}
		protected: 
			virtual int writeData(const char* ptr, size_t sz) {
				//debug_write(ptr,sz);
				str.append(ptr, sz);
			}
		};


		class std_ostream_writer : public gxx::io::ostream {
			std::ostream& out;
		public:
			std_ostream_writer(std::ostream& out) : out(out) {}
		protected: 
			virtual int writeData(const char* ptr, size_t sz) {
				out.write(ptr, sz);
			}
		};
	}
}

#endif