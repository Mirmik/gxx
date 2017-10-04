#include <gxx/serialize/trent.h>
#include <gxx/iteratible.h>
#include <gxx/debug/dprint.h>
#include <gxx/format.h>
#include <algorithm>

using namespace gxx::result_type;

namespace gxx {

	trent::~trent() {
		invalidate();
	}
	
	trent::trent() {}
	
	trent::trent(const trent& other) {
		m_type = other.m_type;
		switch(m_type) {
			case trent::type::string: 
				gxx::constructor(&m_str, other.m_str); 
				return;
			case trent::type::array: 
				gxx::constructor(&m_arr, other.m_arr);
				return; 
			case trent::type::dictionary: 
				gxx::constructor(&m_dict, other.m_dict);
				return;
			case trent::type::number:
				m_num = other.m_num;
				return;
			case trent::type::noinit:
				return; 
		}	
	}
	
	trent::trent(const std::string& str) {
		init(str);
	}
	
	trent::trent(const trent::type& t) {
		init(t);
	}
	
	trent::trent(double num) {
		init(num);
	}
	
	void trent::init(trent::type t) {
		m_type = t;
		switch(m_type) {
			case trent::type::string: 
				gxx::constructor(&m_str); 
				return;
			case trent::type::array: 
				gxx::constructor(&m_arr);
				return; 
			case trent::type::dictionary: 
				gxx::constructor(&m_dict);
				return;
			case trent::type::number:
			case trent::type::noinit:
				return; 
		}
	}
	
	void trent::init(const std::string& str) {
		m_type = trent::type::string;
		gxx::constructor(&m_str, str);
	
	}
	
	void trent::init(const double& num) {
		m_type = trent::type::number;
		m_num = num;
	}
	
	void trent::invalidate() {
		switch(m_type) {
			case trent::type::string: 
				gxx::destructor(&m_str); 
				return;
			case trent::type::array: 
				gxx::destructor(&m_arr);
				return; 
			case trent::type::dictionary: 
				gxx::destructor(&m_dict);
				return; 
			case trent::type::noinit:
			case trent::type::number:
				return;
		}
		m_type = trent::type::noinit;
	}
	
	trent& trent::operator[](size_t i) {
		if (m_type != trent::type::array) init(trent::type::array); 
		if(m_arr.size() <= i) m_arr.resize(i + 1);
		return m_arr[i];
	}
	
	trent& trent::operator[](const char* key) {
		if (m_type != trent::type::dictionary) init(trent::type::dictionary);
		return m_dict[key];
	}

	trent& trent::operator[](const std::string& key) {
		if (m_type != trent::type::dictionary) init(trent::type::dictionary);
		return m_dict[key];
	}

	trent& trent::operator[](const gxx::buffer& key) {
		if (m_type != trent::type::dictionary) init(trent::type::dictionary);
		return m_dict[std::string(key.data(), key.size())];
	}
	
	std::map<std::string, trent>& trent::as_dictionary() {
		if (m_type != trent::type::dictionary) init(trent::type::dictionary);
		return m_dict;
	}
	
    std::vector<trent>& trent::as_array() {
		if (m_type != trent::type::array) init(trent::type::array);
		return m_arr;
	}
    std::vector<trent>& trent::as_vector() { return as_array(); }

    result<std::vector<trent>&> trent::as_array_critical() {
        if (!is_array()) return error("is't array");
        return m_arr;
    }
    result<std::vector<trent>&> trent::as_vector_critical() { return as_array_critical(); }

	const std::string& trent::as_string() {
		if (m_type != trent::type::string) init(trent::type::string);
		return m_str;
	}
	
	const double& trent::as_numer() {
		if (m_type != trent::type::number) init(trent::type::number);
		return m_num;
	}
	
	/*double trent::get_number(const char* str, double def) {
		trent* cur = this;
		for (auto& s : gxx::split_tokenizer(str, '/')) {
			dprln(s);
			if (cur->contains(s)) cur = &cur->m_dict[std::string(s.data(), s.size())];
			else return def;
		}       
		if (cur->get_type() != gxx::trent::type::number) return def;
		return cur->as_numer();
	}

	double trent::get_number(const std::string& str, double def) {
		return get_number(str.c_str(), def);
	}*/

	result<const std::string&> trent::as_string_critical() {
		if (!is_string()) return error("is't string");
		return m_str;
	}

	result<const double&> trent::as_numer_critical() {
		if (!is_numer()) return error("is't number");
		return m_num;
	}

	const double trent::as_numer_default(const double def) {
		if (!is_numer()) return def;
		return m_num;
	}

	const std::string& trent::as_string_default(const std::string& def) {
		if (!is_string()) return def;
		return m_str;
	}

	bool trent::contains(gxx::buffer buf) {
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

	trent::type trent::get_type() const {
		return m_type;
	}
	
	const char * trent::type_to_str() {
		switch(m_type) {
			case trent::type::string: 		return "String";
			case trent::type::array: 		return "Array";
			case trent::type::dictionary: 	return "Dictionary";
			case trent::type::number: 		return "number";
			case trent::type::noinit: 		return "NoInit";
		}
	}
	
	trent& trent::operator= (const trent& other) {
		invalidate();
		m_type = other.m_type;
		switch(m_type) {
			case trent::type::string: 
				gxx::constructor(&m_str, other.m_str); 
				return *this;
			case trent::type::array: 
				gxx::constructor(&m_arr, other.m_arr);
				return *this;
			case trent::type::dictionary: 
				gxx::constructor(&m_dict, other.m_dict);
				return *this;
			case trent::type::number:
				m_num = other.m_num;
				return *this;
			case trent::type::noinit:
				return *this; 
		}	
	}
	
	trent& trent::operator= (const std::string& str) {
		reset(str);
		return *this;
	}
	
	trent& trent::operator= (const double& num) {
		reset(num);
		return *this;
	}	
	
	int trent::size() {
		switch(m_type) {
			case trent::type::number:
			case trent::type::string: return -1;
			case trent::type::array: return m_arr.size();
			case trent::type::dictionary: return m_dict.size();
		} 
	}	

    strlst trent::check_dict(strlst lst, check_type ct) {
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

    std::pair<strlst, strlst> trent::check_dict_symmetric(strlst lst) {
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
