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

		protected: 
			virtual int readData(char* str, size_t sz) = 0;
		};
	}
}

#endif