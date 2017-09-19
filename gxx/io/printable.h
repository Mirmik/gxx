#ifndef GXX_IO_PRINTABLE_H
#define GXX_IO_PRINTABLE_H

//#include <gxx/io/ostream.h>
#include <gxx/buffer.h>
#include <gxx/debug/dprint.h>

namespace gxx {
	namespace io {
		class ostream;

		class printable {
		public:
			virtual size_t printTo(gxx::io::ostream& o) const = 0;
			virtual size_t formattedPrintTo(gxx::io::ostream& o, gxx::buffer& opts);
		};

		class printable_cstring : public printable { const char* i; public: printable_cstring(const char* i) : i(i) {}; size_t printTo(gxx::io::ostream& o) const override; };

		class printable_int8 : public printable { int8_t i; public: printable_int8(int8_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };
		class printable_int16 : public printable { int16_t i; public: printable_int16(int16_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };
		class printable_int32 : public printable { int32_t i; public: printable_int32(int32_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };
		class printable_int64 : public printable { int64_t i; public: printable_int64(int64_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };

		class printable_uint8 : public printable { uint8_t i; public: printable_uint8(uint8_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };
		class printable_uint16 : public printable { uint16_t i; public: printable_uint16(uint16_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };
		class printable_uint32 : public printable { uint32_t i; public: printable_uint32(uint32_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };
		class printable_uint64 : public printable { uint64_t i; public: printable_uint64(uint64_t i) : i(i) { dprln(i); }; size_t printTo(gxx::io::ostream& o) const override; };

		template<typename T> const printable& as_printable(const T& obj) { return obj; }

		static printable_int8 as_printable(const int8_t& obj) { return printable_int8(obj); }
		static printable_int16 as_printable(const int16_t& obj) { return printable_int16(obj); }
		static printable_int32 as_printable(const int32_t& obj) { return printable_int32(obj); }
		static printable_int64 as_printable(const int64_t& obj) { return printable_int64(obj); }

		static printable_uint8 as_printable(const uint8_t& obj) { return printable_uint8(obj); }
		static printable_uint16 as_printable(const uint16_t& obj) { return printable_uint16(obj); }
		static printable_uint32 as_printable(const uint32_t& obj) { return printable_uint32(obj); }
		static printable_uint64 as_printable(const uint64_t& obj) { return printable_uint64(obj); }

		static printable_cstring as_printable(const char*& obj) { return printable_cstring(obj); }
	}
}

#endif