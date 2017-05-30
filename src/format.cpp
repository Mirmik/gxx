#include <gxx/format.h>

namespace gxx {

	static int format_visitor::visit(gxx::argument arg, memory_writer& w, const char* opts) {
		dprln(arg.type_to_string());
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
	}
	
	static int format_visitor::visit_int64(const int64_t& num, memory_writer& w, const char* opts) {
		dprln("Hereint64");
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
	
		w.write_int(num, spec);	
	}
	
	static int format_visitor::visit_uint64(const uint64_t& i, memory_writer&, const char* opts) {
		dprln("Hereuint64");
		abort();
		//dprln(i);	
	}
	
	static int format_visitor::visit_cstring(const char*& str, memory_writer& w, const char* opts) {
		dprln("Herecstring");
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
	
		w.write(str, spec);	
	}
	
	static int format_visitor::visit_custom(const gxx::argument::custom_value& c, memory_writer& w, const char* opts) {
		reinterpret_cast<VoidFuncPtr>(c.func)(c.ptr, w, opts);
	}

}