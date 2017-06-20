#ifndef GXX_PFILE_H
#define GXX_PFILE_H

#include <gxx/io2/strm.h>

namespace gxx {
	namespace io {
		enum OpenMode {
			NotOpen = 0x00,
			ReadOnly = 0x01,
			WriteOnly = 0x02,
			ReadWrite = ReadOnly | WriteOnly,
			Append = 0x04,
			Truncate = 0x08
		};

		class pfile : public io::strmio {
		public:
			virtual bool open(uint8_t mode) = 0;
			virtual void close() = 0;	
			virtual int32_t read(char *data, size_t maxSize) = 0;	
			virtual int32_t write(const char *data, size_t maxSize) = 0;
		};
	}
}

#endif