#ifndef GXX_IO_SERIAL_PORT_H
#define GXX_IO_SERIAL_PORT_H

#include <gxx/io/file.h>
#include <unistd.h>

#include <gxx/util/uartopts.h>

namespace gxx
{
	namespace io
	{
		class serial_port_file : public gxx::io::file_like
		{
            unsigned int baud;
            gxx::serial::parity parity;
            gxx::serial::bytesize bytesize;
            gxx::serial::stopbits stopbits;
            gxx::serial::flowcontrol flowcontrol;


		public:
			serial_port_file() {}
			serial_port_file(const char * path,
			                 unsigned int baud = 9600,
			                 gxx::serial::parity parity = gxx::serial::parity_none,
			                 gxx::serial::bytesize bytesize = gxx::serial::eightbits,
			                 gxx::serial::stopbits stopbits = gxx::serial::stopbits_one,
			                 gxx::serial::flowcontrol flowcontrol = gxx::serial::flowcontrol_none)
                : file_like(), baud(baud), parity(parity), bytesize(bytesize), stopbits(stopbits), flowcontrol(flowcontrol)
			{
                open(path, baud, parity, bytesize, stopbits, flowcontrol);
			}

			int open(const char * path,
			         unsigned int baud = 9600,
			         gxx::serial::parity parity = gxx::serial::parity_none,
			         gxx::serial::bytesize bytesize = gxx::serial::eightbits,
			         gxx::serial::stopbits stopbits = gxx::serial::stopbits_one,
			         gxx::serial::flowcontrol flowcontrol = gxx::serial::flowcontrol_none);

            void reconfigurePort();

            /*int32_t readData(char *data, size_t maxSize) override
            {
                return ::read(fd, data, maxSize);
            }

            int32_t writeData(const char *data, size_t maxSize) override
            {
                return ::write(fd, data, maxSize);
            }*/
		};
	}
}

#endif
