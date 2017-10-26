#include <gxx/serialize/trent.h>
#include <gxx/iteratible.h>
#include <gxx/debug/dprint.h>
//#include <gxx/print.h>
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
            case trent::type::single_floating:
                m_sflt = other.m_sflt;
				return;   
            case trent::type::double_floating:
                m_dflt = other.m_dflt;
                return;
            case trent::type::integer:
                m_i64 = other.m_i64;
                return;
			case trent::type::noinit:
				return; 
		}	
	}
	
	trent::trent(const std::string& str) {
		init(str);
	}
	
	trent::trent(const char* str) {
		init(str);
	}

	trent::trent(const trent::type& t) {
		init(t);
	}

    trent::trent(float num) {
        init(num);
    }

    trent::trent(double num) {
        init(num);
    }

    trent::trent(long double num) {
        init(num);
    }

    trent::trent(int i) {
        init(i);
    }

    trent::trent(long i) {
        init(i);
    }

    trent::trent(long long i) {
        init(i);
    }

    trent::trent(short i) {
        init(i);
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
            case trent::type::single_floating:
            case trent::type::double_floating:
            case trent::type::integer:
			case trent::type::noinit:
				return; 
		}
	}
	
	void trent::init(const std::string& str) {
		m_type = trent::type::string;
		gxx::constructor(&m_str, str);
	
	}
	
	void trent::init(const char* str) {
		m_type = trent::type::string;
		gxx::constructor(&m_str, str);
	
	}
	
    void trent::init(float num) {
        m_type = trent::type::single_floating;
        m_sflt = num;
	}

    void trent::init(double num) {
        m_type = trent::type::double_floating;
        m_dflt = num;
    }

    void trent::init(long double num) {
        m_type = trent::type::double_floating;
        m_dflt = num;
    }

    void trent::init(short i) {
        m_type = trent::type::integer;
        m_i64 = i;
    }

    void trent::init(int i) {
        m_type = trent::type::integer;
        m_i64 = i;
    }

    void trent::init(long i) {
        m_type = trent::type::integer;
        m_i64 = i;
    }

    void trent::init(long long i) {
        m_type = trent::type::integer;
        m_i64 = i;
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
            case trent::type::single_floating:
            case trent::type::double_floating:
            case trent::type::integer:
				return;
		}
		m_type = trent::type::noinit;
	}
	
    trent& trent::operator[](int i) {
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
	
    const gxx::buffer trent::as_buffer() const {
        if (m_type == trent::type::string) return gxx::buffer(m_str.data(), m_str.size());
        return gxx::buffer();
    }

    trent::dfloat_type trent::as_numer() {
        if (m_type == trent::type::single_floating) return m_sflt;
        if (m_type == trent::type::double_floating) return m_dflt;
        if (m_type == trent::type::integer) return m_i64;
        return 0;

	}

    trent::integer_type trent::as_integer() {
        if (m_type == trent::type::single_floating) return m_sflt;
        if (m_type == trent::type::double_floating) return m_dflt;
        if (m_type == trent::type::integer) return m_i64;
        return 0;
    }
	
    /*double trent::get_numer(const char* str, double def) {
		trent* cur = this;
		for (auto& s : gxx::split_tokenizer(str, '/')) {
			dprln(s);
			if (cur->contains(s)) cur = &cur->m_dict[std::string(s.data(), s.size())];
			else return def;
		}       
        if (cur->get_type() != gxx::trent::type::numer) return def;
		return cur->as_numer();
	}

    double trent::get_numer(const std::string& str, double def) {
        return get_numer(str.c_str(), def);
	}*/

	result<const std::string&> trent::as_string_critical() {
		if (!is_string()) return error("is't string");
		return m_str;
	}

    result<double> trent::as_numer_critical() {
        if (!is_numer()) return error("is't numer");
        return as_numer();
	}

	const double trent::as_numer_default(const double def) {
		if (!is_numer()) return def;
        return as_numer();
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
            case trent::type::single_floating: 	return "Float";
            case trent::type::double_floating: 	return "Double";
            case trent::type::integer: 		return "Integer";
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
            case trent::type::single_floating:
                m_sflt = other.m_sflt;
				return *this;   
            case trent::type::double_floating:
                m_dflt = other.m_dflt;
                return *this;
            case trent::type::integer:
                m_i64 = other.m_i64;
                return *this;
			case trent::type::noinit:
				return *this; 
		}	
	}
	
	trent& trent::operator= (const std::string& str) {
		reset(str);
		return *this;
	}
	
    trent& trent::operator= (double num) {
		reset(num);
		return *this;
	}	

    trent& trent::operator= (short i){
        reset(i);
        return *this;
    }

    trent& trent::operator= (int i){
        reset(i);
        return *this;
    }

    trent& trent::operator= (long i){
        reset(i);
        return *this;
    }

    trent& trent::operator= (long long i){
        reset(i);
        return *this;
    }
	
	int trent::size() {
		switch(m_type) {
            case trent::type::integer:
            case trent::type::single_floating:
            case trent::type::double_floating:
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
