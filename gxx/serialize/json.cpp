#include <gxx/serialize/json_parser.h>
#include <limits.h>

using namespace gxx::result_type;

namespace gxx {
namespace detail {
		char getnext(std::istream& is) {
			char c;
			char next;
			__try__:

			is >> c;
			//is.unget();

			if (c == '/') {
				//next = is.peek(); 
				next = is.get();
				switch (next) {
					case '*': 
						//is.ignore();
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

	result<json> json_parser::parse(std::istream& is) {
		is >> std::skipws;

		char c = detail::getnext(is);
		
		if (isdigit(c) || c == '-') return parse_number(is);
		if (c == '"') return parse_string(is);
		if (c == '[') return parse_array(is);
		if (c == '{') return parse_dictionary(is);

		return json();
	}

	json json_parser::parse_number(std::istream& is) {
		int num;
		is >> num;
		return json(num);
	}

	result<json> json_parser::parse_string(std::istream& is) {
		std::string str;

		is.ignore();
		std::getline(is, str, '"');
		json ret(str);
		//is.ignore();

		return ret;
	}
	
	result<json> json_parser::parse_array(std::istream& is) {
		//dprln("parse_array");
		char c;
		json js(json::type::array);
		
		int counter = 0;
		while(true) {
			c = detail::getnext(is);
			
			//dprln(c);

			if (c == ']') {
				is.ignore();
				return js;
			}
				
			if (c == ',' || c == '[') {
				is.ignore();
				//is.ignore_while(isspace);
				
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

	result<json> json_parser::parse_dictionary(std::istream& is) {
		//dprln("parse_dictionary");
		char c;
		json js(json::type::dictionary);
		
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

				//dprln(key);
				//is.ignore();
				c = detail::getnext(is);

				if ( c != ':' ) return error("wrong dicionary syntax: not find colomn");
				is.ignore();

				c = detail::getnext(is);

				//dprf("add to dictionary {}", key);
				js.as_dictionary().insert(std::make_pair(key, tryS(parse(is))));
				//is.ignore_while(isspace);
			}
			else return error("json::internal:dict_parse");
		}
	}

	void json::printTo(std::ostream& os) {
		bool sep = false;
		switch(m_type) {
			case datatree::type::integer: 
				os << m_i64;
				return;
			case datatree::type::string: 
				os << '"'; 
				os << m_str;
				os << '"';
				return;
			case datatree::type::array: 
				os << '[';
				for(auto& v : m_arr) {
					if (sep) os << ',';
					(*reinterpret_cast<json*>(&v)).printTo(os);
					sep = true;
				}
				os << ']';
				return; 
			case datatree::type::dictionary: 
				os << '{';
				for(auto& p : m_dict) {
					if (sep) os << ',';
					os << '"';
					os << p.first;
					os << '"';
					os << ':';
					(*reinterpret_cast<json*>(&p.second)).printTo(os);
					sep = true;
				}
				os << '}';
				return; 
			case datatree::type::noinit:
				os << "nil";
				return;
		}
	}

	void json::prettyPrintTo(std::ostream& os, int tab) {
		bool sep = false;
		bool havedict;

		switch(m_type) {
			case datatree::type::integer: 
				os << m_i64;
				break;
			
			case datatree::type::string: 
				os << '"' << m_str << '"';
				break;
			
			case datatree::type::array: 
				havedict = false;
				for (const auto& m : m_arr) {
					if (m.get_type() == datatree::datatree::type::dictionary) {
						havedict = true; break;
					}
				}

				os << '[';

				if (havedict) for(auto& v : m_arr) {
					if (sep) os << ", ";
					(*reinterpret_cast<json*>(&v)).prettyPrintTo(os, tab+1);
					sep = true;
				}
				else { 
					for(auto& v : m_arr) {
						if (sep) os.put(',');
						os << std::endl;
						for(int i = 0; i < tab + 1; i++) os.put('\t');
						(*reinterpret_cast<json*>(&v)).prettyPrintTo(os, tab+1);
						sep = true;
					}
					os << std::endl;
					for(int i = 0; i < tab; i++) os.put('\t');	
				}
				os.put(']');
				break;

			case datatree::type::dictionary: 
				os.put('{');
				for(auto& p : m_dict) {
					if (sep) os << ',';
					os.put('\n');
					for(int i = 0; i < tab + 1; i++) os.put('\t');
					os << '"' << p.first << '"';
					os.write(": ", 2);
					(*reinterpret_cast<json*>(&p.second)).prettyPrintTo(os, tab+1);
					sep = true;
				}
				os.put('\n');
				for(int i = 0; i < tab; i++) os.put('\t');
				os.put('}');
				break; 
			case datatree::type::noinit:
				os.write("nil", 3);
				break;
		}
		if (tab == 0) os << std::endl;
	}
}
