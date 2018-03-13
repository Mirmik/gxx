#ifndef GXX_IO_ISTREAM_H
#define GXX_IO_ISTREAM_H

#include <gxx/panic.h>

namespace gxx {
	namespace io {
		class istream {
		public:
			virtual int read(char* str, size_t sz) {
				return readData(str, sz);
			}

			virtual int getchar() {
				char c;
				int ret = read(&c,1);
				if (ret == -1 || ret == 0) return -1;
				return c;
			}

			virtual int read_until(char* str, size_t max, char symb) {
				int c;
				char* strt = str;
				do {
                                        if (str - strt >= max) { gxx::panic("read_until::more_than_max"); }

					c = getchar();
                                        //dprln((int)c);
					if (c == -1) break;
					//dprhexln(c);
					*str++ = (char)c;
				} while(c != symb);
				return str - strt;
			}


			std::string readall() {
				char buf[64];
				std::string text;

				while(1) {
					int ret = read(buf, 64);
					if (ret <= 0) break;
					text.append(buf, ret);
				}
				return text;
			}


		protected:
			virtual int readData(char* str, size_t sz) = 0;
		};
	}
}

#endif
