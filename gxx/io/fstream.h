#ifndef GXX_IO_FSTREAM_H
#define GXX_IO_FSTREAM_H

#include <gxx/io/ostream.h>

namespace gxx {
	namespace io {
		class fstream : public gxx::io::ostream {
			int fd;
		protected:
			fstream(int fd) : fd(fd) {}

		protected:
			int writeData(const char* str, size_t sz) override;

		public:
			static fstream from_file_descriptor(int fd) {
				return fstream(fd);
			}
		};
	}
}

#endif