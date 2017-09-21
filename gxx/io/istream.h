#ifndef GXX_IO_ISTREAM_H
#define GXX_IO_ISTREAM_H

namespace gxx {
	namespace io {
		class istream {

		protected: 
			virtual int readData(char* str, size_t sz) = 0;
		};
	}
}

#endif