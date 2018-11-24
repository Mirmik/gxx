#ifndef GXX_IO_ISTREAM_H
#define GXX_IO_ISTREAM_H

#include <gxx/panic.h>
#include <gxx/print.h>

namespace gxx {
	namespace io {
		class istream {
		public:
			virtual ssize_t read(char* str, size_t sz) {
				return readData(str, sz);
			}

			virtual int getchar() {
				char c;
				ssize_t ret = readData(&c,1);
				if (ret == -1 || ret == 0) return -1;
				return c;
			}

			virtual int read_until(char* str, size_t maxlen, char symb) {
				int c;
				char* strt = str;
				do {
					if ((size_t)(str - strt) >= maxlen) return (int) maxlen;
					c = getchar();
					if (c == -1) break;
					*str++ = (char)c;
				} while(c != symb);
				return (int) (str - strt);
			}

			int readline(char* str, size_t maxlen, char symb) {
				return read_until(str, maxlen, symb);
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
			virtual ssize_t readData(char* str, size_t sz) = 0;
		};
	}
}

#endif
