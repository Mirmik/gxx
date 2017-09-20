#include <gxx/fmt/format.h>
#include <gxx/io/ostream.h>

template<> size_t gxx::fmt::format_visitor::visit_implementation<char*>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	char* str = (char*)ptr;
	if (opts.empty()) return out.print(str);
	else return out.print(str, gxx::fmt::spec_cstring(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<std::string>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	std::string& str = *(std::string*)ptr;
	if (opts.empty()) return out.print(str);
	else return out.print(str.c_str(), gxx::fmt::spec_cstring(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<short>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	short& i = *(short*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<int>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	int& i = *(int*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<long>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	long& i = *(long*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<long long>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	long long& i = *(long long*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<unsigned short>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	unsigned short& i = *(unsigned short*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<unsigned int>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	unsigned int& i = *(unsigned int*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<unsigned long>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	unsigned long& i = *(unsigned long*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<unsigned long long>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	unsigned long long& i = *(unsigned long long*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print((long long) i, gxx::fmt::spec_integer(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<char>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	char& i = *(char*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print(i, gxx::fmt::spec_cstring(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<signed char>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	signed char& i = *(signed char*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print(i, gxx::fmt::spec_cstring(opts));
}

template<> size_t gxx::fmt::format_visitor::visit_implementation<unsigned char>(void* ptr, gxx::io::ostream& out, gxx::buffer opts) {
	unsigned char& i = *(unsigned char*)ptr;
	if (opts.empty()) return out.print(i);
	else return out.print(i, gxx::fmt::spec_cstring(opts));
}