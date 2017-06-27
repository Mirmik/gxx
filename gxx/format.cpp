#include <gxx/util/format.h>
#include <gxx/io/format_writer.h>

namespace gxx {

	gxx::string format_args(const char* fmt, const arglist& args) {
		gxx::string retstr;
		retstr.reserve(2*strlen(fmt));
		gxx::io::format_string_writer writer(retstr);
		writer.print_impl(fmt, args);
		return retstr;
	}

	/*int format_visitor::visit(gxx::argument arg, io::format_writer& w, const char* opts) {
		//dprln(arg.type_to_string());
		switch (arg.type) {
			case gxx::argument::Type::SInt8:  return 	visit_int64 (arg.i8,  w, opts);
			case gxx::argument::Type::SInt16: return 	visit_int64 (arg.i16, w, opts);
			case gxx::argument::Type::SInt32: return 	visit_int64 (arg.i32, w, opts);
			case gxx::argument::Type::SInt64: return 	visit_int64 (arg.i64, w, opts);
			case gxx::argument::Type::UInt8:  return 	visit_uint64(arg.u8,  w, opts);
			case gxx::argument::Type::UInt16: return 	visit_uint64(arg.u16, w, opts);
			case gxx::argument::Type::UInt32: return 	visit_uint64(arg.u32, w, opts);
			case gxx::argument::Type::UInt64: return 	visit_uint64(arg.u64, w, opts);
			case gxx::argument::Type::CharPtr: return 	visit_cstring(arg.str, w, opts);
			case gxx::argument::Type::CustomType: return 	visit_custom(arg.custom, w, opts);
		}
	}*/

	int format_visitor::visit(gxx::argument arg, io::format_writer& w, const char* opts) {
		return reinterpret_cast<VoidFuncPtr>(arg.func)(arg.ptr, w, opts);
	}

	
	
	template<>
	int format_arg(const int64_t& num, io::format_writer& w, const char* opts) {
		io::IntegerSpec spec;
	
		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			switch(*opts) {
				case '<': spec.align(io::Alignment::Left); continue;
				case '>': spec.align(io::Alignment::Right); continue;
				case '^': spec.align(io::Alignment::Center); continue;
				case 'f': spec.fill(*++opts); continue;
				case 'X': spec.charCase(io::CharCase::Upper);
				case 'x': 
					spec.base(16); 
					if ( spec.prefix() == io::Prefix::Need ) spec.prefix(io::Prefix::Hex);  
					continue; 
				case 'p': 
					spec.prefix(io::Prefix::Need); 
			}
			if (isdigit(*opts)) { 
				spec.width(atou32(opts, 10)); 
				while(isdigit(*opts)) opts++; 
				opts--;
				continue;
			}
		}
	
		return w.write_int_spec(num, spec);	
	}
	
	template<>
	int format_arg(const int32_t& i, io::format_writer& w, const char* opts) {
		const int64_t i64 = i;
		return format_arg(i64, w, opts);	
	}


	template<>
	int format_arg(const uint64_t& u, io::format_writer& w, const char* opts) {
		const int64_t i = u;
		return format_arg(i, w, opts);
	}


	template<>
	int format_arg(const uint32_t& u, io::format_writer& w, const char* opts) {
		const int64_t i = u;
		return format_arg(i, w, opts);
	}

	template<>
	int format_arg(const uint16_t& u, io::format_writer& w, const char* opts) {
		const int64_t i = u;
		return format_arg(i, w, opts);
	}

	template<>
	int format_arg(const uint8_t& u, io::format_writer& w, const char* opts) {
		const int64_t i = u;
		return format_arg(i, w, opts);
	}

	int format_arg_str(const char* const& str, size_t len, io::format_writer& w, const char* opts) {
		//dprln("Herecstring");
		io::CharStrSpec spec;
	
		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			switch (*opts) {
				case 'U': spec.charCase(io::CharCase::Upper); continue;
				case '<': spec.align(io::Alignment::Left); continue;
				case '>': spec.align(io::Alignment::Right); continue;
				case '^': spec.align(io::Alignment::Center); continue;
				case 'f': spec.fill(*++opts); continue;
			}
			if (isdigit(*opts)) { 
				spec.width(atou32(opts, 10)); 
				while(isdigit(*opts)) opts++; 
				opts--;
				continue;
			}
		}
	
		return w.write_spec(str, len, spec);	
	}

	template<>
	int format_arg(const char* const& str, io::format_writer& w, const char* opts) {
		return format_arg_str(str, strlen(str), w, opts);
	}
/*	
	template<>
	int format_arg(const gxx::string& str, io::format_writer& w, const char* opts) {
		return format_arg_str(str.data(), str.size(), w, opts);
	}

	void format_impl(io::format_writer& writer, const char* fmt, const gxx::arglist& list) {
		uint8_t argnum = 0;
		const char* fmtptr = fmt;
	
		while(*fmtptr != 0) {
			if (*fmtptr == '{') {
				format_argument(writer, fmtptr, list, argnum);
				argnum++;
			} else {
				if (writer.putchar(*fmtptr++) == 0) break;
			}
		}
	}

	string format_impl(const char* fmt, const gxx::arglist& list) {
		int len = strlen(fmt) * 2 + 50;
		char* msg = (char*)alloca(len);
		gxx::memory_stream strm(msg, len);
		gxx::io::format_writer writer(strm);
		format_impl(writer, fmt, list);
		return gxx::string(msg, strm.size());
	}

	int format_argument(io::format_writer& writer, const char*& fmt, const gxx::arglist& list, uint8_t& argnum) {
		int ret;

		assert(*fmt++ == '{');

		if (isdigit(*fmt)) {
			argnum = atou32(fmt, 10);
		} 

		if (isalpha(*fmt)) {
			//dprln("not implemented");
			//abort();
			//dprln(fmt);
			const char* count_ptr = fmt;
			int len = 0;
			while(isalpha(*count_ptr++)) len++;
			argnum = list.find_name(fmt,len);
			if (argnum == 0xFF) {
				dprln("name error");
				abort();
			}
		} 

		while(*fmt != '}' && *fmt != ':' && *fmt != 0) fmt++;
		switch(*fmt) {
			case '}': 
				ret = format_visitor::visit(list[argnum], writer, nullptr);
				break;
			case ':': 
				ret = format_visitor::visit(list[argnum], writer, ++fmt);
				break;
			case 0	: 
				return -1;
			default: 
				//printf("format internal error");
				abort();
		}
		while(*fmt != '}' && *fmt != 0) fmt++;
		fmt++;
		return ret;
	}*/
	

}