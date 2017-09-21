#include <gxx/io/fstream.h>
#include <fcntl.h>
#include <unistd.h>

namespace gxx {
	namespace io {

		fstream::fstream(){}
        fstream::fstream(const std::string& path, uint8_t mode) { open(path, mode); }
		fstream::fstream(int m_fd) : m_fd(m_fd) {}
		
        bool fstream::open(const std::string& path, uint8_t mode) {
			//uint16_t flags = O_CREAT | O_NOCTTY;
            uint16_t flags = O_CREAT;
			if (mode == gxx::io::NotOpen) return false;
			if (mode & gxx::io::ReadWrite) flags |= O_RDWR;
			if (mode & gxx::io::ReadOnly) flags |= O_RDONLY;
			if (mode & gxx::io::WriteOnly) flags |= O_WRONLY;
			if (mode & gxx::io::Append) flags |= O_APPEND;
			if (mode & gxx::io::Truncate) flags |= O_TRUNC;
			m_fd = ::open(path.c_str(), flags, 0666);
    		return true;
		}
		
		void fstream::close() {
			::close(m_fd);
		}
		
		int32_t fstream::readData(char *data, size_t maxSize) {
			//dprln(m_fd);
			return ::read(m_fd, data, maxSize);
		}
		
		int32_t fstream::writeData(const char *data, size_t maxSize) {
			return ::write(m_fd, data, maxSize);
		}
	
	
        /*void fstream::setFileDescriptor(int m_fd) {
			this->m_fd = m_fd;
		}
		
		void fstream::setPath(const std::string& path) {
			this->path = path;
        }*/

		int fstream::nodelay(bool en) {
            //int flags = fcntl(m_fd, F_GETFL);
            //flags = en ? flags | O_NDELAY : flags & (~O_NDELAY);      /* turn off delay flag */
            //fcntl(m_fd, F_SETFL, flags);
			//perror("ss");
			//while(1);
	
		}	

		bool fstream::is_open() {
			return m_fd >= 0;
		}
	}

	io::fstream cout(0);
	io::fstream cin(1);
	io::fstream crr(2);

}
