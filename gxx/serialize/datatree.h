#ifndef GXX_DATATREE_H
#define GXX_DATATREE_H

#include <cstdint>
#include <cassert>
#include <utility>

#include <string>
#include <vector>
#include <map>

#include <gxx/util/ctrdtr.h>

namespace gxx {
	class datatree {
	public:
		enum class type {
			string,
			array,
			dictionary,
			integer,
			noinit,
		};

	protected:
		datatree::type m_type = datatree::type::noinit;

		union {
			int64_t m_i64;
			std::string m_str;
			std::vector<datatree> m_arr;
			std::map<std::string, datatree> m_dict;
		};

	public:
		~datatree() {
			invalidate();
		}

		datatree() {}

		datatree(const datatree& other) {
			m_type = other.m_type;
			switch(m_type) {
				case datatree::type::string: 
					gxx::constructor(&m_str, other.m_str); 
					return;
				case datatree::type::array: 
					gxx::constructor(&m_arr, other.m_arr);
					return; 
				case datatree::type::dictionary: 
					gxx::constructor(&m_dict, other.m_dict);
					return;
				case datatree::type::integer:
					m_i64 = other.m_i64;
					return;
				case datatree::type::noinit:
					return; 
			}	
		}

		datatree(const std::string& str) {
			init(str);
		}

		datatree(const datatree::type& t) {
			init(t);
		}

		datatree(int64_t i64) {
			init(i64);
		}

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(datatree::type t) {
			m_type = t;
			switch(m_type) {
				case datatree::type::string: 
					gxx::constructor(&m_str); 
					return;
				case datatree::type::array: 
					gxx::constructor(&m_arr);
					return; 
				case datatree::type::dictionary: 
					gxx::constructor(&m_dict);
					return;
				case datatree::type::integer:
				case datatree::type::noinit:
					return; 
			}
		}

		void init(const std::string& str) {
			m_type = datatree::type::string;
			gxx::constructor(&m_str, str);

		}
	
		void init(const int64_t& i64) {
			m_type = datatree::type::integer;
			m_i64 = i64;
		}

		void invalidate() {
			switch(m_type) {
				case datatree::type::string: 
					gxx::destructor(&m_str); 
					return;
				case datatree::type::array: 
					gxx::destructor(&m_arr);
					return; 
				case datatree::type::dictionary: 
					gxx::destructor(&m_dict);
					return; 
				case datatree::type::noinit:
				case datatree::type::integer:
					return;
			}
			m_type = datatree::type::noinit;
		}

	public:
		datatree& operator[](size_t i) {
			if (m_type != datatree::type::array) init(datatree::type::array); 
			if(m_arr.size() <= i) m_arr.resize(i + 1);
			return m_arr[i];
		}

		datatree& operator[](const std::string& key) {
			if (m_type != datatree::type::dictionary) init(datatree::type::dictionary);
			return m_dict[key];
		}

		std::map<std::string, datatree>& as_dictionary() {
			if (m_type != datatree::type::dictionary) init(datatree::type::dictionary);
			return m_dict;
		}

		std::vector<datatree>& as_vector() {
			if (m_type != datatree::type::array) init(datatree::type::array);
			return m_arr;
		}

		std::string& as_string() {
			if (m_type != datatree::type::string) init(datatree::type::string);
			return m_str;
		}

		int64_t& as_integer() {
			if (m_type != datatree::type::integer) init(datatree::type::integer);
			return m_i64;
		}
	
		datatree::type get_type() const {
			return m_type;
		}

		const char * type_to_str() {
			switch(m_type) {
				case datatree::type::string: 		return "String";
				case datatree::type::array: 		return "Array";
				case datatree::type::dictionary: 	return "Dictionary";
				case datatree::type::integer: 		return "Integer";
				case datatree::type::noinit: 		return "NoInit";
			}
		}
		
	public:
		datatree& operator= (const datatree& other) {
			invalidate();
			m_type = other.m_type;
			switch(m_type) {
				case datatree::type::string: 
					gxx::constructor(&m_str, other.m_str); 
					return *this;
				case datatree::type::array: 
					gxx::constructor(&m_arr, other.m_arr);
					return *this;
				case datatree::type::dictionary: 
					gxx::constructor(&m_dict, other.m_dict);
					return *this;
				case datatree::type::integer:
					m_i64 = other.m_i64;
					return *this;
				case datatree::type::noinit:
					return *this; 
			}	
		}

		datatree& operator= (const std::string& str) {
			reset(str);
			return *this;
		}
	
		datatree& operator= (const int64_t& i64) {
			reset(i64);
			return *this;
		}	

		int size() {
			switch(m_type) {
				case datatree::type::integer:
				case datatree::type::string: return -1;
				case datatree::type::array: return m_arr.size();
				case datatree::type::dictionary: return m_dict.size();
			} 
		}
	};

}

#endif