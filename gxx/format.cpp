#include <gxx/format.h>

namespace gxx {

	/*int format_visitor::visit(gxx::argument arg, memory_writer& w, const char* opts) {
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

	int format_visitor::visit(gxx::argument arg, memory_writer& w, const char* opts) {
		return reinterpret_cast<VoidFuncPtr>(arg.func)(arg.ptr, w, opts);
	}
	
	template<>
	int format_arg(const int64_t* num, memory_writer& w, const char* opts) {
		//dprln("Hereint64");
		IntegerSpec spec;
	
		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			switch(*opts) {
				case '<': spec.align(Alignment::Left); continue;
				case '>': spec.align(Alignment::Right); continue;
				case '^': spec.align(Alignment::Center); continue;
				case 'f': spec.fill(*++opts); continue;
				case 'X': spec.charCase(CharCase::Upper);
				case 'x': 
					spec.base(16); 
					if ( spec.prefix() == Prefix::Need ) spec.prefix(Prefix::Hex);  
					continue; 
				case 'p': 
					spec.prefix(Prefix::Need); 
			}
			if (isdigit(*opts)) { 
				spec.width(atou32(opts, 10)); 
				while(isdigit(*opts)) opts++; 
				opts--;
				continue;
			}
		}
	
		w.write_int(*num, spec);	
	}
	
	template<>
	int format_arg(const int32_t* i, memory_writer& w, const char* opts) {
		return format_arg((const int64_t*) i, w, opts);	
	}


	int format_arg(const uint64_t* i, memory_writer&, const char* opts) {
		//dprln("Hereuint64");
		abort();
		//dprln(i);	
	}
	
	template<>
	int format_arg(const char* const* str, memory_writer& w, const char* opts) {
		//dprln("Herecstring");
		CharStrSpec spec;
	
		if (opts != nullptr)
		for(; *opts != '}' && *opts != 0; ++opts) {
			switch (*opts) {
				case 'U': spec.charCase(CharCase::Upper); continue;
				case '<': spec.align(Alignment::Left); continue;
				case '>': spec.align(Alignment::Right); continue;
				case '^': spec.align(Alignment::Center); continue;
				case 'f': spec.fill(*++opts); continue;
			}
			if (isdigit(*opts)) { 
				spec.width(atou32(opts, 10)); 
				while(isdigit(*opts)) opts++; 
				opts--;
				continue;
			}
		}
	
		w.write(*str, spec);	
	}
	
	void format_impl(memory_writer& writer, const char* fmt, const gxx::arglist& list) {
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
		gxx::string str;
		str.reserve(128);
		gxx::memory_writer writer(str.data(), str.capacity());
		format_impl(writer, fmt, list);
		return str.set_size(writer.size());
	}

	int format_argument(memory_writer& writer, const char*& fmt, const gxx::arglist& list, uint8_t& argnum) {
		int ret;

		assert(*fmt++ == '{');

		if (isdigit(*fmt)) {
			argnum = atou32(fmt, 10);
		} 

		if (isalpha(*fmt)) {
			//dprln("not implemented");
			//abort();
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
	}
	

}