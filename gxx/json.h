#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <inttypes.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <assert.h>

#include <gxx/utility.h>

namespace gxx {

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
			new (&m_str) std::string(str);

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
		}

	public:
		json& operator[](size_t i) {
			if (m_type != Type::Array) reset(Type::Array); 
			if(m_arr.size() <= i) m_arr.resize(i + 1);
			return m_arr[i];
		}
	
		json& operator[](std::string key) {
			if (m_type != Type::Dictionary) reset(Type::Dictionary);
			return m_dict[key];
		}

		std::map<std::string, json>& as_dictionary() {
			assert(m_type == Type::Dictionary);
			return m_dict;
		}

		std::vector<json>& as_vector() {
			assert(m_type == Type::Array);
			return m_arr;
		}

		std::string& as_string() {
			assert(m_type == Type::String);
			return m_str;
		}

		int64_t& as_integer() {
			assert(m_type == Type::Integer);
			return m_i64;
		}

		Type type() {
			return m_type;
		}
		
	public:
		~json() {
			invalidate();
		}

		json() {}

		json(const std::string& str) {
			init(str);
		}

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

		json& operator= (const std::string& str) {
			reset(str);
			return *this;
		}
	
		json& operator= (const int64_t& i64) {
			reset(i64);
			return *this;
		}

	public:
		void printTo(std::ostream& strm) {
			bool sep = false;
			switch(m_type) {
				case Type::Integer: 
					strm << m_i64;
					return;
				case Type::String: 
					strm << "'" << m_str << "'";
					return;
				case Type::Array: 
					strm << '[';
					for(auto& v : m_arr) {
						if (sep) strm << ',';
						v.printTo(strm);
						sep = true;
					}
					strm << ']';
					return; 
				case Type::Dictionary: 
					strm << '{';
					for(auto& p : m_dict) {
						if (sep) strm << ',';
						strm << p.first << ':';
						p.second.printTo(strm);
						sep = true;
					}
					strm << '}';
					return; 
				case Type::NoInit:
					strm << "nil";
					return;
			}
		}

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
		}
	};
}

std::ostream& operator<<(std::ostream& strm, gxx::json& j) {
	j.printTo(strm);
	return strm;
}

#endif