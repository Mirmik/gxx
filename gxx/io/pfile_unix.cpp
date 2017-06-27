#include <gxx/io/pfile.h>
#include <fcntl.h>
#include <unistd.h>

namespace gxx {
	namespace io {

		pfile::pfile(const char* path) : path(path) {}
		pfile::pfile(int fd) : fd(fd) {}
		
		bool pfile::open(uint8_t mode) {
			uint16_t flags = O_CREAT;
			if (mode == gxx::io::NotOpen) return false;
			if (mode & gxx::io::ReadOnly) flags |= O_RDONLY;
			if (mode & gxx::io::WriteOnly) flags |= O_WRONLY;
			if (mode & gxx::io::Append) flags |= O_APPEND;
			if (mode & gxx::io::Truncate) flags |= O_TRUNC;
			fd = ::open(path.c_str(), flags, 0666);
			return true;
		}
		
		void pfile::close() {
			::close(fd);
		}
		
		int32_t pfile::readData(char *data, size_t maxSize) {
			return ::read(fd, data, maxSize);
		}
		
		int32_t pfile::writeData(const char *data, size_t maxSize) {
			return ::write(fd, data, maxSize);
		}
	
	
		void pfile::setFileDescriptor(int fd) {
			this->fd = fd;
		}
		
		void pfile::setPath(const gxx::string& path) {
			this->path = path;
		}
	
	}

	io::pfile strmout(0);
	io::pfile strmin(1);
	io::pfile strmerr(2);

}