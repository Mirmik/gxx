#include <gxx/serialize/datatree.h>
#include <gxx/iteratible.h>
#include <gxx/debug/dprint.h>
#include <gxx/format.h>
#include <algorithm>

using namespace gxx::result_type;

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
			case datatree::type::number:
				m_num = other.m_num;
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
	
	datatree::datatree(double num) {
		init(num);
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
			case datatree::type::number:
			case datatree::type::noinit:
				return; 
		}
	}
	
	void datatree::init(const std::string& str) {
		m_type = datatree::type::string;
		gxx::constructor(&m_str, str);
	
	}
	
	void datatree::init(const double& num) {
		m_type = datatree::type::number;
		m_num = num;
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
			case datatree::type::number:
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
	
    std::vector<datatree>& datatree::as_array() {
		if (m_type != datatree::type::array) init(datatree::type::array);
		return m_arr;
	}
    std::vector<datatree>& datatree::as_vector() { return as_array(); }

    result<std::vector<datatree>&> datatree::as_array_critical() {
        if (!is_array()) return error("is't array");
        return m_arr;
    }
    result<std::vector<datatree>&> datatree::as_vector_critical() { return as_array_critical(); }

	const std::string& datatree::as_string() {
		if (m_type != datatree::type::string) init(datatree::type::string);
		return m_str;
	}
	
	const double& datatree::as_numer() {
		if (m_type != datatree::type::number) init(datatree::type::number);
		return m_num;
	}
	
	/*double datatree::get_number(const char* str, double def) {
		datatree* cur = this;
		for (auto& s : gxx::split_tokenizer(str, '/')) {
			dprln(s);
			if (cur->contains(s)) cur = &cur->m_dict[std::string(s.data(), s.size())];
			else return def;
		}       
		if (cur->get_type() != gxx::datatree::type::number) return def;
		return cur->as_numer();
	}

	double datatree::get_number(const std::string& str, double def) {
		return get_number(str.c_str(), def);
	}*/

	result<const std::string&> datatree::as_string_critical() {
		if (!is_string()) return error("is't string");
		return m_str;
	}

	result<const double&> datatree::as_numer_critical() {
		if (!is_numer()) return error("is't number");
		return m_num;
	}

	const double datatree::as_numer_default(const double def) {
		if (!is_numer()) return def;
		return m_num;
	}

	const std::string& datatree::as_string_default(const std::string& def) {
		if (!is_string()) return def;
		return m_str;
	}

	bool datatree::contains(gxx::buffer buf) {
		if (m_type != type::dictionary) {
			return false;
		}

		for(const auto& p : m_dict) {
			if (buf == gxx::buffer(p.first)) { 
				return true;
			}
		}

		return false;
	}

	datatree::type datatree::get_type() const {
		return m_type;
	}
	
	const char * datatree::type_to_str() {
		switch(m_type) {
			case datatree::type::string: 		return "String";
			case datatree::type::array: 		return "Array";
			case datatree::type::dictionary: 	return "Dictionary";
			case datatree::type::number: 		return "number";
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
			case datatree::type::number:
				m_num = other.m_num;
				return *this;
			case datatree::type::noinit:
				return *this; 
		}	
	}
	
	datatree& datatree::operator= (const std::string& str) {
		reset(str);
		return *this;
	}
	
	datatree& datatree::operator= (const double& num) {
		reset(num);
		return *this;
	}	
	
	int datatree::size() {
		switch(m_type) {
			case datatree::type::number:
			case datatree::type::string: return -1;
			case datatree::type::array: return m_arr.size();
			case datatree::type::dictionary: return m_dict.size();
		} 
	}	

    strlst datatree::check_dict(strlst lst, check_type ct) {
		if (!is_dictionary()) return strlst();


		strlst retlist;

		auto _keys = gxx::keys_of_map(m_dict);
		//dprln("HERE");
		strlst keys(_keys.begin(), _keys.end());
		
		//dprln("HERE");
		//std::sort(lst.begin(), lst.end());
		//std::sort(keys.begin(), keys.end());
		lst.sort();
		keys.sort();

		switch (ct) {
			case check_superset:
				std::set_difference(
					keys.begin(), keys.end(),
					lst.begin(), lst.end(), 
					std::inserter(retlist, retlist.begin())
				);
				break;

			case check_subset:
				std::set_difference(
					lst.begin(), lst.end(), 
					keys.begin(), keys.end(),
					std::inserter(retlist, retlist.begin())
				);

			case check_equal:
				std::set_symmetric_difference(
					keys.begin(), keys.end(),
					lst.begin(), lst.end(), 
					std::inserter(retlist, retlist.begin())
				);
				break;
		}

		return retlist;

	}

    std::pair<strlst, strlst> datatree::check_dict_symmetric(strlst lst) {
		std::pair<strlst, strlst> ret;
		if (!is_dictionary()) return ret;

		auto _keys = gxx::keys_of_map(m_dict);
		strlst keys(_keys.begin(), _keys.end());
		
		lst.sort();
		keys.sort();

		std::set_difference(
			keys.begin(), keys.end(),
			lst.begin(), lst.end(), 
			std::inserter(ret.first, ret.first.begin())
		);
		
		std::set_difference(
			lst.begin(), lst.end(), 
			keys.begin(), keys.end(),
			std::inserter(ret.second, ret.second.begin())
		);
		
		return ret;
	}
}
