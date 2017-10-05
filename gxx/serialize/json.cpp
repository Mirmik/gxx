#include <gxx/serialize/json.h>

#include <istream>
#include <limits.h>

using namespace gxx::result_type;

namespace gxx {
namespace detail {
		char getnext(std::istream& is) {
			char c;
			char next;
			__try__:

			is >> c;
			if (c == '/') {
				next = is.get();
				switch (next) {
					case '*': 
						while(true) {
							is >> c;
							if (c == '*') if (is.peek() == '/') { 
								is.ignore();
								goto __try__;
							} 
						}
					case '/': 
						is.ignore(INT_MAX, '\n');						
						goto __try__;
					default:
						is.unget(); 
						break;
				}
			}
			is.unget();
			return c;
		}
	}	

	result<trent> json::parse(std::istream& is) {
		is >> std::skipws;

		char c = detail::getnext(is);
		
		if (isdigit(c) || c == '-') return parse_number(is);
		if (c == '"') return parse_string(is);
		if (c == '[') return parse_array(is);
		if (c == '{') return parse_dictionary(is);

		return trent();
	}

	trent json::parse_number(std::istream& is) {
		double num;
		is >> num;
		return trent(num);
	}

	result<trent> json::parse_string(std::istream& is) {
		std::string str;

		is.ignore();
		std::getline(is, str, '"');
		trent ret(str);
		
		return ret;
	}
	
	result<trent> json::parse_array(std::istream& is) {
		char c;
		trent js(trent::type::array);
		
		int counter = 0;
		while(true) {
			c = detail::getnext(is);
			
			if (c == ']') {
				is.ignore();
				return js;
			}
				
			if (c == ',' || c == '[') {
				is.ignore();
				
				c = detail::getnext(is);
				
				if (c == ']') {
					is.ignore();
					return js;
				}
				
				js.as_vector().push_back(tryS(parse(is)));
			}
			else return error("wrong array syntax");;

			counter++;
		}
	}

	result<trent> json::parse_dictionary(std::istream& is) {
		char c;
		trent js(trent::type::dictionary);
		
		while(true) {
			c = detail::getnext(is);
			
			if (c == '}') {
				is.ignore();
				return js;
			}				
			
			if (c == ',' || c == '{') {
				is.ignore();

				c = detail::getnext(is);

				if (c == '}') {
					is.ignore();
					return js;
				}				

				if ( c != '"' ) return error("wrong dicionary syntax: not find \"");
				is.ignore();
				
				std::string key;
				std::getline(is, key, '"');

				c = detail::getnext(is);

				if ( c != ':' ) return error("wrong dicionary syntax: not find colomn");
				is.ignore();

				c = detail::getnext(is);

				js.as_dictionary().insert(std::make_pair(key, tryS(parse(is))));
			}
			else return error("trent::internal:dict_parse");
		}
	}

	void json::print_to(const trent& tr, std::ostream& os) {
		bool sep = false;
		switch(tr.get_type()) {
			case trent::type::number: 
				os << tr.unsafe_number();
				return;
			case trent::type::string: 
				os << '"'; 
				os << tr.unsafe_string();
				os << '"';
				return;
			case trent::type::array: 
				os << '[';
				for(auto& v : tr.unsafe_array()) {
					if (sep) os << ',';
					json::print_to(v, os);
					sep = true;
				}
				os << ']';
				return; 
			case trent::type::dictionary: 
				os << '{';
				for(auto& p : tr.unsafe_dictionary()) {
					if (sep) os << ',';
					os << '"';
					os << p.first;
					os << '"';
					os << ':';
					json::print_to(p.second, os);
					sep = true;
				}
				os << '}';
				return; 
			case trent::type::noinit:
				os << "nil";
				return;
		}
	}

	void json::pretty_print_to(const trent& tr, std::ostream& os, int tab) {
		bool sep = false;
		bool havedict;

		switch(tr.get_type()) {
			case trent::type::number: 
				os << std::fixed << tr.unsafe_number();
				break;
			
			case trent::type::string: 
				os << '"' << tr.unsafe_string() << '"';
				break;
			
			case trent::type::array: 
				havedict = false;
				for (const auto& m : tr.unsafe_array()) {
					if (m.get_type() == trent::trent::type::dictionary) {
						havedict = true; break;
					}
				}

				os << '[';

				if (havedict) for(auto& v : tr.unsafe_array()) {
					if (sep) os << ", ";
					json::pretty_print_to(v, os, tab+1);
					sep = true;
				}
				else { 
					for(auto& v : tr.unsafe_array()) {
						if (sep) os.put(',');
						os << std::endl;
						for(int i = 0; i < tab + 1; i++) os.put('\t');
						json::pretty_print_to(v, os, tab+1);
						sep = true;
					}
					os << std::endl;
					for(int i = 0; i < tab; i++) os.put('\t');	
				}
				os.put(']');
				break;

			case trent::type::dictionary: 
				os.put('{');
				for(auto& p : tr.unsafe_dictionary()) {
					if (sep) os << ',';
					os.put('\n');
					for(int i = 0; i < tab + 1; i++) os.put('\t');
					os << '"' << p.first << '"';
					os.write(": ", 2);
					json::pretty_print_to(p.second, os, tab+1);
					sep = true;
				}
				os.put('\n');
				for(int i = 0; i < tab; i++) os.put('\t');
				os.put('}');
				break; 
			case trent::type::noinit:
				os.write("nil", 3);
				break;
		}
		if (tab == 0) os << std::endl;
	}
}
