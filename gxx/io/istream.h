#ifndef GXX_IO_ISTREAM_H
#define GXX_IO_ISTREAM_H

#include <gxx/panic.h>
#include <gxx/print.h>

namespace gxx {
	namespace io {
		class istream {
		public:
			virtual int read(char* str, size_t sz) {
				return readData(str, sz);
			}

			virtual int getchar() {
				char c;
				gxx::println("here5");
				int ret = read(&c,1);
				gxx::println("here6");
				if (ret == -1 || ret == 0) return -1;
				return c;
			}

			virtual int read_until(char* str, size_t max, char symb) {
				int c;
				char* strt = str;
				gxx::println("here1");
				do {
					gxx::println("here2");
          			if ((size_t)(str - strt) >= max) return max;
					gxx::println("here3");
					c = getchar();
					gxx::println("here4");
                                        //dprln((int)c);
					if (c == -1) break;
					//dprhexln(c);
					*str++ = (char)c;
				} while(c != symb);
				return str - strt;
			}


			/*std::string readall() {
				char buf[64];
				std::string text;

				while(1) {
					int ret = read(buf, 64);
					if (ret <= 0) break;
					text.append(buf, ret);
				}
				return text;
			}*/


		protected:
			virtual int readData(char* str, size_t sz) = 0;
		};
	}
}

#endif
