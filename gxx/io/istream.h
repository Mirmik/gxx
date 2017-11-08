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
				read(&c,1);
				return c;
			}

                        virtual int read_until(char* str, size_t max, char symb) {
                            int c;
                            char* strt = str;
                            do {
                                c = getchar();
        						if (c == -1)
                                //dprhexln(c);
                                *str++ = (char)c;
                            } while(c != symb);
                            return str - strt;
                        }

		protected: 
			virtual int readData(char* str, size_t sz) = 0;
		};
	}
}

#endif
