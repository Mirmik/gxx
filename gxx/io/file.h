#ifndef GXX_FILE_H
#define GXX_FILE_H

#include <fcntl.h>
#include <gxx/string.h>
#include <gxx/io/iodevice.h>

namespace gxx {
	class File : gxx::IODevice {
		int fd;
		gxx::string path;

	public:
		file(const char* path) : path(path) {}

		bool open(IODevice::OpenMode mode) override {
			uint8_t flags;
			if (mode == IODevice::NotOpen) return;
			if (mode & IODevice::ReadOnly) flag |= O_RDONLY;
			if (mode & IODevice::WriteOnly) flag |= O_WRONLY;
			if (mode & IODevice::Append) flag |= O_APPEND;
			if (mode & IODevice::Truncate) flag |= O_TRUNCATE;
			fd = ::open(path.c_str(), flags);
		}

		void close() override {
			::close(fd);
		}

		int32_t readData(char *data, size_t maxSize) override {

		}

		int32_t writeData(const char *data, size_t maxSize) override {

		}
	}
}

#endif