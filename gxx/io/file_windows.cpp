#include <gxx/io/file.h>
#include <gxx/io/serial_port.h>
#include <fcntl.h>
#include <unistd.h>
#include <winsock2.h>

#include <gxx/panic.h>

#include <gxx/print/stdprint.h>

using namespace gxx::serial;

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0)
        return std::string(); //No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);

    return message;
}

namespace gxx
{
	namespace io
	{

		file::file() {}
		file::file(const char* path, uint8_t mode) { open(path, mode); }
		file::file(int m_fd) : file_like(m_fd) {}

		bool file::open(const char* path, uint8_t mode)
		{
			//uint16_t flags = O_CREAT | O_NOCTTY;
			uint16_t flags = O_CREAT;
			if (mode == gxx::io::NotOpen) return false;
			if (mode & gxx::io::ReadWrite) flags |= O_RDWR;
			if (mode & gxx::io::ReadOnly) flags |= O_RDONLY;
			if (mode & gxx::io::WriteOnly) flags |= O_WRONLY;
			if (mode & gxx::io::Append) flags |= O_APPEND;
			if (mode & gxx::io::Truncate) flags |= O_TRUNC;
			fd = ::open(path, flags, 0666);
			return true;
		}

		int file_like::close()
		{
			return ::close(fd);
		}

		int32_t file_like::readData(char *data, size_t maxSize)
		{
			DWORD really;
            if (!ReadFile((HANDLE)fd, data, maxSize, &really, NULL))
            {
                gxx::println("Error while reading from the serial port: ", GetLastErrorAsString());
                PANIC_TRACED();
            }
			return really;
		}

		int32_t file_like::writeData(const char *data, size_t maxSize)
		{
			DWORD really;
            if (!WriteFile((HANDLE)fd, data, maxSize, &really, NULL)) {
                gxx::println("Error while writing to the serial port: ", GetLastErrorAsString());
                PANIC_TRACED();
            }
			return really;
		}

		int file_like::nonblock(bool en)
		{
			unsigned long flags = en ? 0 : 1;
			return ioctlsocket(fd, FIONBIO, &flags);
		}

		bool file_like::is_open()
		{
            return _is_open;
		}

		int serial_port_file::open(const char * path,
		                           unsigned int baud,
		                           gxx::serial::parity parity,
		                           gxx::serial::bytesize bytesize,
		                           gxx::serial::stopbits stopbits,
		                           gxx::serial::flowcontrol flowcontrol)
		{
			this->baud = baud;
			this->parity = parity;
			this->bytesize = bytesize;
			this->stopbits = stopbits;
			this->flowcontrol = flowcontrol;


			//LPCWSTR lp_port = _path.c_str();
			fd = (uintptr_t)CreateFileA(path,
			                            GENERIC_READ | GENERIC_WRITE,
			                            0,
			                            0,
			                            OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL,
			                            0);

			if ((HANDLE)fd == INVALID_HANDLE_VALUE) {
				DWORD create_file_err = GetLastError();
				switch (create_file_err) {
					case ERROR_FILE_NOT_FOUND:
						// Use this->getPort to convert to a std::string
						//ss << "Specified port, " << this->getPort() << ", does not exist.";
						//THROW (IOException, ss.str().c_str());
						//gxx::println(ss.c_str());
                        gxx::println(GetLastErrorAsString());
						PANIC_TRACED();
					default:
						//ss << "Unknown error opening the serial port: " << create_file_err;
						//THROW (IOException, ss.str().c_str());
                        gxx::println(GetLastErrorAsString());
						PANIC_TRACED();
				}
			}

			DCB dcbSerialParams = {0};

			// setup baud rate
			switch (baud) {
#ifdef CBR_0
				case 0: dcbSerialParams.BaudRate = CBR_0; break;
#endif
#ifdef CBR_50
				case 50: dcbSerialParams.BaudRate = CBR_50; break;
#endif
#ifdef CBR_75
				case 75: dcbSerialParams.BaudRate = CBR_75; break;
#endif
#ifdef CBR_110
				case 110: dcbSerialParams.BaudRate = CBR_110; break;
#endif
#ifdef CBR_134
				case 134: dcbSerialParams.BaudRate = CBR_134; break;
#endif
#ifdef CBR_150
				case 150: dcbSerialParams.BaudRate = CBR_150; break;
#endif
#ifdef CBR_200
				case 200: dcbSerialParams.BaudRate = CBR_200; break;
#endif
#ifdef CBR_300
				case 300: dcbSerialParams.BaudRate = CBR_300; break;
#endif
#ifdef CBR_600
				case 600: dcbSerialParams.BaudRate = CBR_600; break;
#endif
#ifdef CBR_1200
				case 1200: dcbSerialParams.BaudRate = CBR_1200; break;
#endif
#ifdef CBR_1800
				case 1800: dcbSerialParams.BaudRate = CBR_1800; break;
#endif
#ifdef CBR_2400
				case 2400: dcbSerialParams.BaudRate = CBR_2400; break;
#endif
#ifdef CBR_4800
				case 4800: dcbSerialParams.BaudRate = CBR_4800; break;
#endif
#ifdef CBR_7200
				case 7200: dcbSerialParams.BaudRate = CBR_7200; break;
#endif
#ifdef CBR_9600
				case 9600: dcbSerialParams.BaudRate = CBR_9600; break;
#endif
#ifdef CBR_14400
				case 14400: dcbSerialParams.BaudRate = CBR_14400; break;
#endif
#ifdef CBR_19200
				case 19200: dcbSerialParams.BaudRate = CBR_19200; break;
#endif
#ifdef CBR_28800
				case 28800: dcbSerialParams.BaudRate = CBR_28800; break;
#endif
#ifdef CBR_57600
				case 57600: dcbSerialParams.BaudRate = CBR_57600; break;
#endif
#ifdef CBR_76800
				case 76800: dcbSerialParams.BaudRate = CBR_76800; break;
#endif
#ifdef CBR_38400
				case 38400: dcbSerialParams.BaudRate = CBR_38400; break;
#endif
#ifdef CBR_115200
				case 115200: dcbSerialParams.BaudRate = CBR_115200; break;
#endif
#ifdef CBR_128000
				case 128000: dcbSerialParams.BaudRate = CBR_128000; break;
#endif
#ifdef CBR_153600
				case 153600: dcbSerialParams.BaudRate = CBR_153600; break;
#endif
#ifdef CBR_230400
				case 230400: dcbSerialParams.BaudRate = CBR_230400; break;
#endif
#ifdef CBR_256000
				case 256000: dcbSerialParams.BaudRate = CBR_256000; break;
#endif
#ifdef CBR_460800
				case 460800: dcbSerialParams.BaudRate = CBR_460800; break;
#endif
#ifdef CBR_921600
				case 921600: dcbSerialParams.BaudRate = CBR_921600; break;
#endif
				default:
					// Try to blindly assign it
					dcbSerialParams.BaudRate = baud;
			}

			// setup char len
			if (bytesize == eightbits)
				dcbSerialParams.ByteSize = 8;
			else if (bytesize == sevenbits)
				dcbSerialParams.ByteSize = 7;
			else if (bytesize == sixbits)
				dcbSerialParams.ByteSize = 6;
			else if (bytesize == fivebits)
				dcbSerialParams.ByteSize = 5;
			else
				PANIC_TRACED();
			//throw invalid_argument ("invalid char len");

			// setup stopbits
			if (stopbits == stopbits_one)
				dcbSerialParams.StopBits = ONESTOPBIT;
			else if (stopbits == stopbits_one_point_five)
				dcbSerialParams.StopBits = ONE5STOPBITS;
			else if (stopbits == stopbits_two)
				dcbSerialParams.StopBits = TWOSTOPBITS;
			else
				// throw invalid_argument ("invalid stop bit");
				PANIC_TRACED();

			// setup parity
			if (parity == parity_none) {
				dcbSerialParams.Parity = NOPARITY;
			} else if (parity == parity_even) {
				dcbSerialParams.Parity = EVENPARITY;
			} else if (parity == parity_odd) {
				dcbSerialParams.Parity = ODDPARITY;
			} else if (parity == parity_mark) {
				dcbSerialParams.Parity = MARKPARITY;
			} else if (parity == parity_space) {
				dcbSerialParams.Parity = SPACEPARITY;
			} else {
				//throw invalid_argument ("invalid parity");
				PANIC_TRACED();
			}

			// setup flowcontrol
			if (flowcontrol == flowcontrol_none) {
				dcbSerialParams.fOutxCtsFlow = false;
				dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
				dcbSerialParams.fOutX = false;
				dcbSerialParams.fInX = false;
			}
			if (flowcontrol == flowcontrol_software) {
				dcbSerialParams.fOutxCtsFlow = false;
				dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
				dcbSerialParams.fOutX = true;
				dcbSerialParams.fInX = true;
			}
			if (flowcontrol == flowcontrol_hardware) {
				dcbSerialParams.fOutxCtsFlow = true;
				dcbSerialParams.fRtsControl = RTS_CONTROL_HANDSHAKE;
				dcbSerialParams.fOutX = false;
				dcbSerialParams.fInX = false;
			}

			// activate settings
			if (!SetCommState((HANDLE)fd, &dcbSerialParams)) {
				//CloseHandle(fd);
				//THROW (IOException, "Error setting serial port settings.");
				PANIC_TRACED();
			}

			COMMTIMEOUTS timeouts;

            timeouts.ReadIntervalTimeout = 0;
            timeouts.ReadTotalTimeoutMultiplier = 2;
            timeouts.ReadTotalTimeoutConstant = 10;
            timeouts.WriteTotalTimeoutMultiplier = 2;
            timeouts.WriteTotalTimeoutConstant = 10;

            if (!SetCommTimeouts((HANDLE)fd, &timeouts)) {
                PANIC_TRACED();
            }

            _is_open = true;
		}
	}
}
