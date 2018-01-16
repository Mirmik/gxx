#ifndef GXX_IO_ISTREAM_H
#define GXX_IO_ISTREAM_H

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
					c = getchar();
					//dprln((int)c);
					if (c == -1) break;
					//dprhexln(c);
					*str++ = (char)c;
				} while(c != symb);
				return str - strt;
			}


			std::string readall(int bufsize = 512) {
				char buf[bufsize];
				std::string text;

				while(1) {
					int ret = read(buf, bufsize);
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
