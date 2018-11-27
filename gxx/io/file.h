#ifndef GXX_IO_FSTREAM_H
#define GXX_IO_FSTREAM_H

#include <gxx/io/iostream.h>

namespace gxx
{
    namespace io
    {
        enum OpenMode {
            NotOpen = 0x00,
            ReadOnly = 0x01,
            WriteOnly = 0x02,
            ReadWrite = 0x04,
            Append = 0x08,
            Truncate = 0x10
        };

        class file_like : public gxx::io::iostream
        {
        protected:
            uintptr_t fd = -1;
            bool _is_open;

        public:
            file_like() {}
            file_like(uintptr_t fd) : fd(fd) {}

            int nonblock(bool en);
            int close();

            bool is_open();
            CONSTREF_GETTER(file_descriptor, fd);
        };

        class file : public gxx::io::file_like
        {
        public:
            file();
            file(int fd);
            file(const char* path, uint8_t mode = ReadWrite);

            ssize_t readData(char *data, size_t maxSize) override;  
            ssize_t writeData(const char *data, size_t maxSize) override;
            
            //bool open(uint8_t mode);
            bool open(const char* path, uint8_t mode = ReadWrite);
        };
    }
}

#endif
