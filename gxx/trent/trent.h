#ifndef GXX_DATATREE_H
#define GXX_DATATREE_H

#include <cstdint>
#include <cassert>
#include <utility>

#include <string>
#include <vector>
#include <map>

#include <gxx/result.h>
#include <gxx/util/string.h>
#include <gxx/util/ctrdtr.h>
#include <gxx/buffer.h>
#include <gxx/print.h>

using namespace gxx::result_type;

namespace gxx {
	class trent {
	public:
		enum class type {
			string,
                        list,
                        dict,
                        numer,
                        nil,
		};

		using check_type = uint8_t;

		static constexpr check_type check_subset = 0;
		static constexpr check_type check_superset = 1;
		static constexpr check_type check_equal = 2;

                using numer_type = long double;
                using list_type = std::vector<trent>;
                using dict_type = std::map<std::string, trent>;
                using string_type = std::string;

	protected:
                trent::type m_type = trent::type::nil;

                union {
                        numer_type m_num;
                        list_type m_arr;
                        dict_type m_dict;
                        string_type m_str;
		};

	public:
		~trent();
		trent();
		trent(const trent& other);
		trent(const trent::type& t);

		trent(const char* str);
		trent(const std::string& str);

                /*trent(short i);
		trent(int i);
		trent(long i);
		trent(long long i);

		trent(float num);
                trent(double num);*/
                trent(numer_type num);

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(trent::type t);
		void init(const std::string& str);
		void init(const char* str);

                /*void init(float i);
		void init(double i);
		void init(long double i);

		void init(short i);
		void init(int i);
		void init(long i);
		void init(long long i);

		void init(unsigned short i);
		void init(unsigned int i);
                void init(unsigned long i);*/
                void init(numer_type i);

                void init_list(size_t reserve);
		void invalidate();

	public:
		trent& operator[](int i);
		trent& operator[](const char* key);
		trent& operator[](const std::string& key);
		const trent& operator[](const std::string& key) const;
		trent& operator[](const gxx::buffer& key);

		trent& at(int i);
		trent& at(const char* key);
		trent& at(const std::string& key);
		trent& at(const gxx::buffer& key);

		const trent& at(int i) const;
		const trent& at(const char* key) const;
		const trent& at(const std::string& key) const;
		const trent& at(const gxx::buffer& key) const;

		bool have(const std::string& key) const; 

                std::map<std::string, trent>& as_dict();
                const std::map<std::string, trent>& as_dict() const;
                result<std::map<std::string, trent>&> as_dict_critical();
                result<const std::map<std::string, trent>&> as_dict_critical() const;
		
                std::vector<trent>& as_list();
                const std::vector<trent>& as_list() const;

                result<std::vector<trent>&> as_list_critical();
                result<const std::vector<trent>&> as_list_critical() const;
		
		numer_type as_numer() const;
                numer_type as_numer_default(numer_type i) const;
                result<numer_type> as_numer_critical() const;

                string_type& as_string();
                const string_type& as_string() const;
		const gxx::buffer as_buffer() const;
                string_type& as_string_default(string_type& str);
                result<string_type&> as_string_critical();
                result<const string_type&> as_string_critical() const;
		
		
		//double get_numer(const char*, double def);
		//double get_numer(const std::string&, double def);

		//result<double> get_numer_critical(const std::string&);

                REFERENCE_GETTER(unsafe_numer, m_num);
		REFERENCE_GETTER(unsafe_string, m_str);
                REFERENCE_GETTER(unsafe_list, m_arr);
                REFERENCE_GETTER(unsafe_dict, m_dict);

                CONSTREF_GETTER(unsafe_numer_const, m_num);
		CONSTREF_GETTER(unsafe_string_const, m_str);
                CONSTREF_GETTER(unsafe_list_const, m_arr);
                CONSTREF_GETTER(unsafe_dict_const, m_dict);


		trent::type get_type() const;
		const char * type_to_str() const;

                bool is_nil() const 		{ return m_type == type::nil; }
                bool is_numer() const 		{ return m_type == type::numer; }
                bool is_list() const		{ return m_type == type::list; }
                bool is_dict() const            { return m_type == type::dict; }
		bool is_string() const 		{ return m_type == type::string; }
		
		strlst check_dict(strlst lst, check_type ct);
		std::pair<strlst,strlst> check_dict_symmetric(strlst lst);

	public:
		trent& operator= (const trent& other);
		trent& operator= (const std::string& str);

		trent& operator= (float num);
		trent& operator= (double num);
		trent& operator= (long double num);

		trent& operator= (short i);
		trent& operator= (int i);
		trent& operator= (long i);
		trent& operator= (long long i);

		trent& operator= (unsigned short i);
		trent& operator= (unsigned int i);
		trent& operator= (unsigned long i);
		trent& operator= (unsigned long long i);
		int size();

		bool contains(gxx::buffer buf);

		size_t printTo(gxx::io::ostream& os) const {
			bool sep = false;
			switch(get_type()) {

                                case trent::type::numer:
                                    os.print(unsafe_numer_const());
				    return 0;
			
				case trent::type::string: 
				    os.putchar('"'); 
				    os.print(unsafe_string_const());
				    os.putchar('"');
				    return 0;
                                case trent::type::list:
				    os.putchar('[');
                                    for(auto& v : unsafe_list_const()) {
					    if (sep) os.putchar(',');
					    v.printTo(os);
					    sep = true;
				    }
				    os.putchar(']');
				    return 0; 
                                case trent::type::dict:
				    os.putchar('{');
                                    for(auto& p : unsafe_dict_const()) {
					    if (sep) os.putchar(',');
					    os.putchar('"');
					    os.print(p.first);
					    os.putchar('"');
					    os.putchar(':');
					    p.second.printTo(os);
					    sep = true;
				    }
				    os.putchar('}');
				    return 0; 
                                case trent::type::nil:
				    os.print("nil");
				    return 0;
			}

		}	
	};
}

#endif
