#ifndef GXX_FMT_FORMAT_H
#define GXX_FMT_FORMAT_H

#include <gxx/arglist.h>
#include <gxx/util/print.h>
#include <gxx/util/numconvert.h>

namespace gxx {
	namespace io { class ostream; }
	namespace fmt {
		struct format_visitor {
			using ftype = size_t(*)(void*, gxx::io::ostream&, gxx::buffer opts);												
		
			//template<typename Object> static size_t visit_implementation(void* obj, gxx::io::ostream& o, gxx::buffer opts) {
			//	return reinterpret_cast<Object*>(obj)->fmtPrintTo(o, opts);
			//}
		
			template<typename Object>
			static void* get_visit() {
				return reinterpret_cast<void*>(&print_functions<Object>::format_print);
			}

			template<typename ... Args>												
			static inline constexpr auto visit(gxx::visitable_argument varg, Args&& ... args) {		
				ftype fptr = (ftype) varg.visit;									
				return fptr(varg.ptr, std::forward<Args>(args) ...);				
			}																		
		};
		
		/*template<> size_t format_visitor::visit_implementation<char>(void* ptr, gxx::io::ostream&, gxx::buffer);
		
		template<> size_t format_visitor::visit_implementation<signed char>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<short>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<int>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<long>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<long long>(void* ptr, gxx::io::ostream&, gxx::buffer);
		
		template<> size_t format_visitor::visit_implementation<unsigned char>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<unsigned short>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<unsigned int>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<unsigned long>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<unsigned long long>(void* ptr, gxx::io::ostream&, gxx::buffer);

		template<> size_t format_visitor::visit_implementation<float>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<double>(void* ptr, gxx::io::ostream&, gxx::buffer);

		template<> size_t format_visitor::visit_implementation<char*>(void* ptr, gxx::io::ostream&, gxx::buffer);
		template<> size_t format_visitor::visit_implementation<std::string>(void* ptr, gxx::io::ostream&, gxx::buffer);*/
	
		struct spec_text {
			unsigned char width = 0;
			signed char allign = 0;

			spec_text(gxx::buffer buf) {
				char* end = buf.data() + buf.size();
				for (char* ptr = buf.data(); ptr != end; ++ptr) {
					//dprln("here");
					char c = *ptr;
					if (isdigit(c)) {
						char* end;
						width = atou32(ptr, 10, &end);
						while(isdigit(*ptr)) ++ptr; --ptr;
						continue;
					}
					switch(c) {
						case '>': allign = 1; continue; 
					}
				}
			}
		};

		struct spec_cstring : public spec_text {
		public:
			spec_cstring(gxx::buffer buf) : spec_text(buf) {}
		};

		struct spec_integer : public spec_text {
		public:
			spec_integer(gxx::buffer buf) : spec_text(buf) {}
		};

		struct spec_float : public spec_text {
		public:
			spec_float(gxx::buffer buf) : spec_text(buf) {}
		};
	}
}


#endif