#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <cstdint>
#include <cassert>
#include <utility>

#include <string>
#include <vector>
#include <map>

#include <gxx/util/ctrdtr.h>
#include <gxx/result.h>
#include <gxx/format.h>

//#include <gxx/io/text_writer.h>
//#include <gxx/io/stdstream.h>

namespace gxx {
	using namespace result_type;


	class json {
	public:
		enum class Type {
			String,
			Array,
			Dictionary,
			Integer,
			NoInit,
		};

	private:
		Type m_type = Type::NoInit;

		union {
			int64_t m_i64;
			std::string m_str;
			std::vector<json> m_arr;
			std::map<std::string, json> m_dict;
		};

	public:
		~json() {
			invalidate();
		}

		json() {}

		json(const json& other) {
			m_type = other.m_type;
			switch(m_type) {
				case Type::String: 
					gxx::constructor(&m_str, other.m_str); 
					return;
				case Type::Array: 
					gxx::constructor(&m_arr, other.m_arr);
					return; 
				case Type::Dictionary: 
					gxx::constructor(&m_dict, other.m_dict);
					return;
				case Type::Integer:
					m_i64 = other.m_i64;
					return;
				case Type::NoInit:
					return; 
			}	
		}

		json(const std::string& str) {
			init(str);
		}

		json(const Type& type) {
			init(type);
		}

		json(int64_t i64) {
			init(i64);
		}

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(Type type) {
			m_type = type;
			switch(type) {
				case Type::String: 
					gxx::constructor(&m_str); 
					return;
				case Type::Array: 
					gxx::constructor(&m_arr);
					return; 
				case Type::Dictionary: 
					gxx::constructor(&m_dict);
					return;
				case Type::Integer:
				case Type::NoInit:
					return; 
			}
		}

		void init(const std::string& str) {
			m_type = Type::String;
			gxx::constructor(&m_str, str);

		}
	
		void init(const int64_t& i64) {
			m_type = Type::Integer;
			m_i64 = i64;
		}

		void invalidate() {
			switch(m_type) {
				case Type::String: 
					gxx::destructor(&m_str); 
					return;
				case Type::Array: 
					gxx::destructor(&m_arr);
					return; 
				case Type::Dictionary: 
					gxx::destructor(&m_dict);
					return; 
				case Type::NoInit:
				case Type::Integer:
					return;
			}
			m_type = Type::NoInit;
		}

	public:
		result<json&> operator[](size_t i) {
			if (m_type != Type::Array) return error("isn`t array"); 
			if(m_arr.size() <= i) m_arr.resize(i + 1);
			return m_arr[i];
		}

		result<json&> operator[](const std::string& key) {
			if (m_type != Type::Dictionary) return error("isn`t dictionary");
			return m_dict[key];
		}

		/*result<bool> contains(std::string key) {
			if (m_type != Type::Dictionary) return error("isn`t dictionary");
			return m_dict.contain(key);
		}*/
/*
		result<std::map<std::string, json>&> as_dictionary() {
			if (m_type != Type::Dictionary) return error("isn`t dictionary");
			return m_dict;
		}

		result<gxx::vector<json>&> as_vector() {
			if (m_type != Type::Array) return error("isn`t vector");
			return m_arr;
		}

		result<std::string&> as_string() {
			if (m_type != Type::String) return error("isn`t string");
			return m_str;
		}

		result<int64_t&> as_integer() {
			if (m_type != Type::Integer) return error("isn`t integer");
			return m_i64;
		}
	
		Type type() {
			return m_type;
		}

		const char * type_to_str() {
			switch(m_type) {
				case Type::String: 		return "String";
				case Type::Array: 		return "Array";
				case Type::Dictionary: 	return "Dictionary";
				case Type::Integer: 	return "Integer";
				case Type::NoInit: 		return "NoInit";
			}
		}
		
	public:
		json& operator= (const json& other) {
			invalidate();
			m_type = other.m_type;
			switch(m_type) {
				case Type::String: 
					gxx::constructor(&m_str, other.m_str); 
					return *this;
				case Type::Array: 
					gxx::constructor(&m_arr, other.m_arr);
					return *this;
				case Type::Dictionary: 
					gxx::constructor(&m_dict, other.m_dict);
					return *this;
				case Type::Integer:
					m_i64 = other.m_i64;
					return *this;
				case Type::NoInit:
					return *this; 
			}	
		}

		json& operator= (const std::string& str) {
			reset(str);
			return *this;
		}
	
		json& operator= (const int64_t& i64) {
			reset(i64);
			return *this;
		}	

		int size() {
			switch(m_type) {
				case Type::Integer:
				case Type::String: return -1;
				case Type::Array: return m_arr.size();
				case Type::Dictionary: return m_dict.size();
			} 
		}
/*
		void drop_whitespaces(std::istream& is) {
			while (isspace(is.peek())) {
				is.ignore();
			}
		}

		//std::string parse_key(std::istream& is) {
		//	char c = ' ';
		//	while (c == ' ') { is >> c;	}
		//	return std::getline(is, 256, ':');
		//}

		int parse_number(std::istream& is) {
			m_type = Type::Integer;
			is >> m_i64;
			return 0;
		}

		int parse_string(std::istream& is) {
			is.ignore();
			std::string str;
			std::getline(is, str, '\'');
			init(str);

			return 0;
		}

		int parse_array(std::istream& is) {
			char c;
			
			init(Type::Array);
			int counter = 0;
			while(true) {
				drop_whitespaces(is);
				c = is.peek();
				
				if (c == ']') {
					is.ignore();
					return 0;
				}
					
				if (c == ',' || c == '[') {
					is.ignore();
					drop_whitespaces(is);
					
					if (is.peek() == ']') {
						is.ignore();
						return 0;
					}
					
					m_arr.push_back(json());
					m_arr[counter].parse(is);
				}
				else return -1;

				counter++;
			}
		}

		int parse_dictionary(std::istream& is) {
			char c;
			
			init(Type::Dictionary);
			//int counter = 0;
			while(true) {
				drop_whitespaces(is);
				c = is.peek();
				
				if (c == '}') {
					is.ignore();
					return 0;
				}	

				if (c == ',' || c == '{') {
					is.ignore();
					drop_whitespaces(is);

					if (is.peek() == '}') {
						is.ignore();
						return 0;
					}				

					std::string key;
					while(true) {
						c = is.peek();
						if( 
							c != ' ' && 
							c != '\t' && 
							c != '\n' && 
							c != ':' && 
							c != 0
						) 
						{
							is >> c;
							key += c;
						}
						else break;
					}
					drop_whitespaces(is);
					if (is.peek() != ':') return -1;
					is.ignore();
					m_dict.insert(std::make_pair(key,json()));
					
					drop_whitespaces(is);
					m_dict[key].parse(is);
				}
				else return -1;

				//counter++;
			}
		}

		int parse(std::istream& is) {
			drop_whitespaces(is);

			char c = is.peek();
			
			if (isdigit(c)) return parse_number(is);
			if (c == '\'') return parse_string(is);
			if (c == '[') return parse_array(is);
			if (c == '{') return parse_dictionary(is);
			

			//if (c == '{') {
			//	m_type = Type::Dictionary;
		//		std::string&& key = parse_key(is);

			//} 
			return 0;
		}*/

/*		public:
		void printTo(const gxx::text_writer& w) {
			bool sep = false;
			switch(m_type) {
				case Type::Integer: 
					w.write_int(m_i64);
					return;
				case Type::String: 
					w.putchar('\''); 
					w.write_str(m_str);
					w.putchar('\'');
					return;
				case Type::Array: 
					w.putchar('[');
					for(auto& v : m_arr) {
						if (sep) w.putchar(',');
						v.printTo(w);
						sep = true;
					}
					w.putchar(']');
					return; 
				case Type::Dictionary: 
					w.putchar('{');
					for(auto& p : m_dict) {
						if (sep) w.putchar(',');
						w.putchar('"');
						w.write_str(p.first);
						w.putchar('"');
						w.putchar(':');
						p.second.printTo(w);
						sep = true;
					}
					w.putchar('}');
					return; 
				case Type::NoInit:
					w.write_cstr("nil");
					return;
			}
		}

		void prettyPrintTo(const gxx::text_writer& w, int tab = 0) {
			//for(int ttab = tab; ttab != 0; ttab--) w.putchar('\t');
			bool sep = false;
			switch(m_type) {
				case Type::Integer: 
					w.write_int(m_i64);
					return;
				case Type::String: 
					w.putchar('\''); 
					w.write_str(m_str);
					w.putchar('\'');
					return;
				case Type::Array: 
					w.putchar('[');
					for(auto& v : m_arr) {
						if (sep) w.putchar(',');
						v.prettyPrintTo(w, tab+1);
						sep = true;
					}
					w.putchar(']');
					return; 
				case Type::Dictionary: 
					w.putchar('{');
					for(auto& p : m_dict) {
						if (sep) w.putchar(',');
						w.putchar('\n');
						w.write_fill('\t',tab+1);
						w.putchar('"');
						w.write_str(p.first);
						w.putchar('"');
						w.write(": ", 2);
						p.second.prettyPrintTo(w, tab+1);
						sep = true;
					}
					w.putchar('\n');
					w.write_fill('\t',tab);
					w.putchar('}');
					return; 
				case Type::NoInit:
					w.write_cstr("nil");
					return;
			}
		}*/
	};
}
/*
std::ostream& operator<<(std::ostream& w, gxx::json& j) {
	j.printTo(w);
	return w;
}
*/
#endif