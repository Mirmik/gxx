#include <gxx/serialize/datatree.h>
#include <gxx/iteratible.h>
#include <gxx/debug/dprint.h>
#include <gxx/format.h>
#include <algorithm>

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
	
	int64_t datatree::get_integer(const char* str, int64_t def) {
		datatree* cur = this;
		for (auto& s : gxx::split_tokenizer(str, '/')) {
			dprln(s);
			if (cur->contains(s)) cur = &cur->m_dict[std::string(s.data(), s.size())];
			else return def;
		}       
		if (cur->get_type() != gxx::datatree::type::integer) return def;
		return cur->as_integer();
	}

	int64_t datatree::get_integer(const std::string& str, int64_t def) {
		return get_integer(str.c_str(), def);
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

	strlst datatree::check_dict(strlst lst, check_type ct) {
		if (!is_dictionary()) return strlst();


		strlst retlist;

		auto _keys = gxx::keys_of_map(m_dict);
		strlst keys(_keys.begin(), _keys.end());
		
		//std::sort(lst.begin(), lst.end());
		//std::sort(keys.begin(), keys.end());
		lst.sort();
		keys.sort();

		dprln("lst");
		for (auto s : lst) dprln("\t{}", s);

		dprln("keys");
		for (auto s : keys) dprln("\t{}", s);
		
		switch (ct) {
			case check_subset:
				std::set_difference(
					lst.begin(), lst.end(), 
					keys.begin(), keys.end(),
					std::inserter(retlist, retlist.begin()), 
					[](const std::string& a, const std::string& b) {
						dpr("\t\t");dprln(a);
						dpr("\t\t");dprln(b);
						return a < b;
					});
				break;
		}

		dprln("result");
		for (auto s : retlist) dprln("\t{}", s);

		return retlist;

	}
}