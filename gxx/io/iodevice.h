#ifndef GXX_IODEVICE_H
#define GXX_IODEVICE_H

namespace gxx {
	class IODevice {
		IODevice(){};

	public:
		enum OpenMode {
			NotOpen = 0x00,
			ReadOnly = 0x01,
			WriteOnly = 0x02,
			ReadWrite = ReadOnly | WriteOnly,
			Append = 0x04,
			Truncate = 0x08
		}

		virtual bool open(OpenMode mode);
		virtual void close();

	protected:
		virtual int32_t readData(char *data, size_t maxSize) = 0;
		virtual int32_t writeData(const char *data, size_t maxSize) = 0;
	
		virtual int32_t readLineData(char *data, qint64 maxSize) {
			abort_dprln("Not Implemented");
		}
	};
}

#endif