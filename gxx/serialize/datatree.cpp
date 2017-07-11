#include <gxx/serialize/datatree.h>

namespace gxx {

	datatree::~datatree() {
		invalidate();
	}
	
	datatree::datatree() {}
	
	datatree::datatree(const datatree& other) {
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
	
	datatree::datatree(const std::string& str) {
		init(str);
	}
	
	datatree::datatree(const datatree::type& t) {
		init(t);
	}
	
	datatree::datatree(int64_t i64) {
		init(i64);
	}
	
	void datatree::init(datatree::type t) {
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
	
	void datatree::init(const std::string& str) {
		m_type = datatree::type::string;
		gxx::constructor(&m_str, str);
	
	}
	
	void datatree::init(const int64_t& i64) {
		m_type = datatree::type::integer;
		m_i64 = i64;
	}
	
	void datatree::invalidate() {
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
	
	datatree& datatree::operator[](size_t i) {
		if (m_type != datatree::type::array) init(datatree::type::array); 
		if(m_arr.size() <= i) m_arr.resize(i + 1);
		return m_arr[i];
	}
	
	datatree& datatree::operator[](const char* key) {
		if (m_type != datatree::type::dictionary) init(datatree::type::dictionary);
		return m_dict[key];
	}

	datatree& datatree::operator[](const std::string& key) {
		if (m_type != datatree::type::dictionary) init(datatree::type::dictionary);
		return m_dict[key];
	}

	datatree& datatree::operator[](const gxx::buffer& key) {
		if (m_type != datatree::type::dictionary) init(datatree::type::dictionary);
		return m_dict[std::string(key.data(), key.size())];
	}
	
	std::map<std::string, datatree>& datatree::as_dictionary() {
		if (m_type != datatree::type::dictionary) init(datatree::type::dictionary);
		return m_dict;
	}
	
	std::vector<datatree>& datatree::as_vector() {
		if (m_type != datatree::type::array) init(datatree::type::array);
		return m_arr;
	}
	
	std::string& datatree::as_string() {
		if (m_type != datatree::type::string) init(datatree::type::string);
		return m_str;
	}
	
	int64_t& datatree::as_integer() {
		if (m_type != datatree::type::integer) init(datatree::type::integer);
		return m_i64;
	}
	
	datatree::type datatree::get_type() const {
		return m_type;
	}
	
	const char * datatree::type_to_str() {
		switch(m_type) {
			case datatree::type::string: 		return "String";
			case datatree::type::array: 		return "Array";
			case datatree::type::dictionary: 	return "Dictionary";
			case datatree::type::integer: 		return "Integer";
			case datatree::type::noinit: 		return "NoInit";
		}
	}
	
	datatree& datatree::operator= (const datatree& other) {
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
	
	datatree& datatree::operator= (const std::string& str) {
		reset(str);
		return *this;
	}
	
	datatree& datatree::operator= (const int64_t& i64) {
		reset(i64);
		return *this;
	}	
	
	int datatree::size() {
		switch(m_type) {
			case datatree::type::integer:
			case datatree::type::string: return -1;
			case datatree::type::array: return m_arr.size();
			case datatree::type::dictionary: return m_dict.size();
		} 
	}	
}