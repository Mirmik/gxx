#ifndef GXX_SSTREAM_H
#define GXX_SSTREAM_H

#include <iostream>
#include <gxx/io/iostream.h>

namespace gxx {
	namespace io {
		class std_string_writer : public gxx::io::ostream {
			std::string& str;
		public:
			std_string_writer(std::string& str) : str(str) {}
		protected: 
			virtual int writeData(const char* ptr, size_t sz) {
				str.append(ptr, sz);
				return sz;
			}
		};

		class std_ostream_writer : public gxx::io::ostream {
			std::ostream& out;
		public:
			std_ostream_writer(std::ostream& out) : out(out) {}
		protected: 
			virtual int writeData(const char* ptr, size_t sz) {
				out.write(ptr, sz);
				return sz;
			}
		};

		class std_ostream : public gxx::io::ostream {
		private:
			std::ostream& out;

		public:
			std_ostream(std::ostream& out) : out(out) {}
			int writeData(const char* ptr, size_t sz) override {
				out.write(ptr, sz);
				return sz;				
			}
		};

		/*class std_istream : public gxx::io::istream, public std::istream {
		public:
			std_istream(std::basic_streambuf<char>* sb) : std::istream(sb) {}
			int readData(char* ptr, size_t sz) override {
				std::istream::read(ptr, sz);
				return sz;
			}
		};*/


		//std_ostream cout(std::cout.rdbuf());
		extern std_ostream cout;
		//extern std_ostream cerr;
		//extern std_istream cin;
	}
}

#endif
