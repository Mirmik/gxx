#ifndef GXX_IO_OSTREAM_H
#define GXX_IO_OSTREAM_H

#include <stdlib.h>
#include <string.h>
#include <gxx/buffer.h>
#include <gxx/util/numconvert.h>
#include <gxx/util/hexascii.h>

#include <gxx/debug/dprint.h>

#include <gxx/io/spec.h>

namespace gxx
{
	namespace io
	{
		class printable;

		class ostream
		{
		public:
			virtual ssize_t write(const char* str, size_t sz)
			{
				return writeData(str, sz);
			}

			virtual ssize_t putchar(char c)
			{
				return writeData(&c, 1);
			}

			ssize_t fill(char c, size_t len)
			{
				while (len--)
				{
					putchar(c);
				}

				return len;
			}

			ssize_t printhex(char c)
			{
				putchar(half2hex((uint8_t)((c & 0xF0) >> 4)));
				putchar(half2hex((uint8_t)(c & 0x0F)));
				return 2;
			}

			ssize_t print_hexdata(char* data, size_t size)
			{
				size_t sz = size;

				while (sz--)
				{
					printhex(*data++);
				}

				return (int)(size << 1);
			}

			template<typename T>
			ssize_t printhex(T c)
			{
				return print_hexdata((char*)&c, sizeof(c));
			}

			ssize_t print(bool obj)
			{
				return print(obj ? "true" : "false");
			}

			ssize_t print(const short i) { return print((long long) i); }
			ssize_t print(const int i) { return print((long long) i); }
			ssize_t print(const long i) { return print((long long) i); }
			ssize_t print(const long long i)
			{
				char buf[48];
				i64toa(i, buf, 10);
				return print(buf);
			}

			ssize_t print(const unsigned short i) { return print((unsigned long long) i); }
			ssize_t print(const unsigned int i) { return print((unsigned long long) i); }
			ssize_t print(const unsigned long i) { return print((unsigned long long) i); }
			ssize_t print(const unsigned long long i)
			{
				char buf[48];
				u64toa(i, buf, 10);
				return print(buf);
			}

			ssize_t print(const long double d)
			{
				char buf[48];
				ftoa((float)d, buf, 5);
				return print(buf);
			}

			ssize_t print(const double d)
			{
				char buf[48];
				ftoa(d, buf, 5);
				return print(buf);
			}

			ssize_t print(const float f)
			{
				char buf[48];
				ftoa(f, buf, 5);
				return print(buf);
			}

			ssize_t print(const char* str)
			{
				return write(str, strlen(str));
			}

			ssize_t print(const void* ptr)
			{
				char buf[48];
				u64toa((uintptr_t)ptr, buf, 16);
				size_t len = strlen(buf);
				ssize_t ret = fill('0', sizeof(void*) * 2 - len);
				return ret + print(buf);
			}

			ssize_t print(gxx::buffer buf)
			{
				return write(buf.data(), buf.size());
			}

			/*int print(const std::string str) {
				return write(str.data(), str.size());
			}*/

			ssize_t print(const gxx::io::printable& obj);

			/*int print(long long i, const fmt::spec_integer& spec) {
				char buf[48];
				i64toa(i, buf, 10);
				return print(buf, spec);
			}

			int print(unsigned long long u, const fmt::spec_integer& spec) {
				return print("print uinteger with spec");
			}

			int print(char str, const fmt::spec_cstring& spec) {
				return print("print char with spec");
			}

			int print(double str, const fmt::spec_float& spec) {
				return print("print double with spec");
			}*/

			template<typename Arg>
			ssize_t println(const Arg& arg)
			{
				int ret = print(arg);
				return ret + write("\r\n", 2);
			}

			ssize_t println()
			{
				return write("\r\n", 2);
			}

			ssize_t format_print(int num, gxx::buffer opts);
			ssize_t format_print(int num, const gxx::io::integer_spec& spec);

			ssize_t format_print(const char* str, gxx::buffer opts);
			ssize_t format_print(const char* str, const gxx::io::basic_spec& spec);

			ssize_t format_print(const char* str, size_t len, gxx::buffer opts);
			ssize_t format_print(const char* str, size_t len, const gxx::io::basic_spec& spec);



			template <typename T>
			ssize_t bwrite(T obj)
			{
				return write((char*)&obj, sizeof(T));
			}

		protected:
			virtual ssize_t writeData(const char* str, size_t sz) = 0;
		};

		class printable
		{
		public:
			virtual int printTo(gxx::io::ostream& o) const = 0;
			virtual int fmtPrintTo(gxx::io::ostream& o, gxx::buffer opts) const
			{
				(void) opts;
				return printTo(o);
			}
		};
	}
}

inline ssize_t gxx::io::ostream::print(const gxx::io::printable& obj)
{
	return obj.printTo(*this);
}

#endif
