#ifndef GXX_IO_OSTREAM_H
#define GXX_IO_OSTREAM_H

#include <string.h>
#include <string>
#include <map>
#include <vector>
#include <array>

#include <gxx/fmt/format.h>
#include <gxx/util/numconvert.h>

#include <gxx/io/printable.h>

namespace gxx {
	namespace io {
		class ostream {
		public:
			virtual int write(const char* str, size_t sz) {
				return writeData(str, sz);
			}

			virtual int putchar(char c) {
				return writeData(&c,1);
			}

			/*int format_argument(const char*& fmt, const gxx::visitable_arglist& list, uint8_t argnum) {
				int ret;		
				char* pend;
				assert(*fmt++ == '{');
		
				const visitable_argument* varg = nullptr;
		
				if (isalpha(*fmt)) {
					const char* count_ptr = fmt;
					int len = 0;
					while(isalpha(*count_ptr++)) len++;
					varg = &list[gxx::buffer(fmt, len)];
				} else if (isdigit(*fmt)) {
					varg = &list[atou32(fmt, 10, &pend)];
				} else {
					varg = &list[argnum];
				}
		
				while(*fmt != '}' && *fmt != ':' && *fmt != 0) fmt++;
				switch(*fmt) {
					case '}': 
						ret = gxx::fmt::format_visitor::visit(*varg, *this, gxx::buffer());
						break;
					case ':': 
						++fmt;
						ret = gxx::fmt::format_visitor::visit(*varg, *this, gxx::buffer(fmt, strchr(fmt, '}') - fmt));
						break;
					case 0	: 
						return -1;
					default: 
						dprln("format internal error");
						abort();
				}
				while(*fmt != '}' && *fmt != 0) fmt++;
				fmt++;
				return ret;
			}

			int format_args(const char* fmt, const visitable_arglist& args) {
				uint8_t argnum = 0;
				const char* fmtptr = fmt;
				size_t ret = 0;

				while(*fmtptr != 0) {
					if (*fmtptr == '{') {
						ret += format_argument(fmtptr, args, argnum);
						argnum++;
					} else {
						auto strttxt = fmtptr;
						while (*fmtptr != 0 && *fmtptr != '{') fmtptr++;
						ret += writeData(strttxt, fmtptr - strttxt);
					}
				}
				return ret;
			}
			
			template<typename ... Args>
			int fmtprint(const char* fmt, Args&& ... args) {
				visitable_argument buffer[sizeof ... (Args)];
				return format_args(fmt, gxx::make_visitable_arglist<gxx::fmt::format_visitor>(buffer, std::forward<Args>(args) ...));
			}

			template<typename ... Args>
			int fmtprintln(Args ... args) {
				int ret = format(args ...);
				return ret + write("\r\n", 2);
			}				

			
			int print(const char* str, const fmt::spec_text& spec) {
				int len = strlen(str);
				if (spec.width != 0) {
					int diff = spec.width - len;
					if (diff <= 0) len = spec.width;
					else {
						if (spec.allign == 1) {
							fill(diff, ' ');
						}
						else {
							write(str, len);
							fill(diff, ' ');
							return len + diff;
						}
					}
				}
				return write(str, len);
			}

			int fill(char s, int n) {
				for (int i = 0; i < n; i++) {
					putchar(s);
				}
			}

			int print(bool obj) {
				return print(obj ? "true" : "false");
			}
			*/
			int print(const short i) { return print((long long) i); }
			int print(const int i) { return print((long long) i); }
			int print(const long i) { return print((long long) i); }
			int print(const long long i) { 
				char buf[48];
				i64toa(i, buf, 10);
				return print(buf);  
			}

			int print(const unsigned short i) { return print((unsigned long long) i); }
			int print(const unsigned int i) { return print((unsigned long long) i); }
			int print(const unsigned long i) { return print((unsigned long long) i); }
			int print(const unsigned long long i) { 
				char buf[48];
				u64toa(i, buf, 10);
				return print(buf);  
			}

			int print(double d) {
				char buf[48];
				ftoa(d, buf);
				return print(buf); 
			}
			
			int print(float f) {
				char buf[48];
				ftoa(f, buf);
				return print(buf); 
			}
			
			int print(const char* str) {
				return write(str, strlen(str));
			}

			int print(gxx::buffer buf) {
				return write(buf.data(), buf.size());
			}

			int print(const std::string str) {
				return write(str.data(), str.size());
			}

			int print(const gxx::io::printable& obj) {
				obj.printTo(*this);
			}

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

			/*
			template <typename T>
			int print(const std::vector<T>& vec) {
				putchar('[');
				for (int i = 0; i < vec.size() - 1; ++i) {
					print(vec[i]);
					putchar(',');
				}
				print(vec[vec.size() - 1]);
				putchar(']');
			}

			template <typename T, size_t N>
			int print(const std::array<T,N>& vec) {
				putchar('[');
				for (int i = 0; i < N - 1; ++i) {
					print(vec[i]);
					putchar(',');
				}
				print(vec[N - 1]);
				putchar(']');
			}

			template <typename K, typename T>
			int print(const std::map<K,T>& dict) {
				putchar('{');
				if (dict.size() != 0) {
					auto it = dict.begin();
					auto end = dict.end();

					print((*it).first); putchar(':'); print((*it).second);
					it++;
					while(it != end) {
						putchar(',');
						print((*it).first); putchar(':'); print((*it).second);	
						it++;
					}
				} 
				putchar('}');
			}
*/
			template<typename Arg>
			int println(Arg&& arg) {
				int ret = print(std::forward<Arg>(arg));
				return ret + write("\r\n", 2);
			}

			int println() {
				return write("\r\n", 2);
			}
		
		protected: 
			virtual int writeData(const char* str, size_t sz) = 0;
		
		};
	}
}

#endif
