#ifndef GXX_JSON_PARSER_H
#define GXX_JSON_PARSER_H

//#include <gxx/io/text_readeis.h>
#include <gxx/result.h>
#include <gxx/serialize/json.h>
using namespace gxx::result_type;

namespace gxx {
	class json_parser {
	public:
		static result<json> parse(std::istream& is) {
			is >> std::skipws;

			char c;
			is >> c;
			is.unget();
			
			if (isdigit(c)) return parse_number(is);
			if (c == '"') return parse_string(is);
			if (c == '[') return parse_array(is);
			if (c == '{') return parse_dictionary(is);

			return json();
		}

		static json parse_number(std::istream& is) {
			int num;
			is >> num;
			return json(num);
		}

		static result<json> parse_string(std::istream& is) {
			std::string str;

			is.ignore();
			std::getline(is, str, '"');
			json ret(str);
			//is.ignore();

			return ret;
		}
		
		static result<json> parse_array(std::istream& is) {
			//dprln("parse_array");
			char c;
			json js(json::type::array);
			
			int counter = 0;
			while(true) {
				is >> c;
				is.unget();
				
				if (c == ']') {
					is.ignore();
					return js;
				}
					
				if (c == ',' || c == '[') {
					is.ignore();
					//is.ignore_while(isspace);
					
					if (is.peek() == ']') {
						is.ignore();
						return js;
					}
					
					js.as_vector().push_back(tryS(parse(is)));
				}
				else return error("wrong array syntax");;

				counter++;
			}
		}

		static result<json> parse_dictionary(std::istream& is) {
			//dprln("parse_dictionary");
			char c;
			json js(json::type::dictionary);
			
			while(true) {
				is >> c;
				is.unget();
				
				if (c == '}') {
					is.ignore();
					return js;
				}				
				
				if (c == ',' || c == '{') {
					is.ignore();

					is >> c;
					is.unget();

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
					is >> c;
					is.unget();

					if ( is.peek() != ':' ) return error("wrong dicionary syntax: not find colomn");
					is.ignore();

					is >> c;
					is.unget();

					//dprf("add to dictionary {}", key);
					js.as_dictionary().insert(std::make_pair(key, tryS(parse(is))));
					//is.ignore_while(isspace);
				}
				else return error("json::internal:dict_parse");
			}
		}
	};
}

#endif