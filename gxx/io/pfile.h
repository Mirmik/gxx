#ifndef GXX_PFILE_H
#define GXX_PFILE_H

#include <gxx/io/strm.h>

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
			int fd;
			gxx::string path;

		public:
			pfile();
			pfile(int fd);
			pfile(const char* path);

			bool open(uint8_t mode);
			void close();	
			int32_t read(char *data, size_t maxSize);	
			int32_t write(const char *data, size_t maxSize);

			void setFileDescriptor(int fd);
			void setPath(const gxx::string& path);
		};
	}
}

#endif