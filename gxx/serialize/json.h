#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <ostream>
#include <gxx/serialize/datatree.h>

namespace gxx {
//	using namespace result_datatree::type;

	class json : public datatree {
	public:
		template<typename ... Args> 
		json(Args ... args) : datatree(std::forward<Args>(args) ...) {}

		public:
		void printTo(std::ostream& os) {
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

		void prettyPrintTo(std::ostream& os, int tab = 0) {
			bool sep = false;
			bool havedict;

			switch(m_type) {
				case datatree::type::integer: 
					os << m_i64;
					return;
				case datatree::type::string: 
					os << '"' << m_str << '"';
					return;
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
					return; 
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
					return; 
				case datatree::type::noinit:
					os.write("nil", 3);
					return;
			}
		}
	};
}

#endif