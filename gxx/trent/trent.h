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
						integer,
						nil,
		};

		using check_type = uint8_t;

		static constexpr check_type check_subset = 0;
		static constexpr check_type check_superset = 1;
		static constexpr check_type check_equal = 2;

		using numer_type = long double;
		using integer_type = int64_t;
		using list_type = std::vector<trent>;
		using dict_type = std::map<std::string, trent>;
		using string_type = std::string;

	protected:
		trent::type m_type = trent::type::nil;

		union {
				numer_type m_num;
				integer_type m_int;
				list_type m_arr;
				dict_type m_dict;
				string_type m_str;
		};

	public:
		~trent();
		trent();
		trent(const trent& other);
		//trent(const trent::type& t);

		inline trent(const std::string& str) { init(str); }
		inline trent(const char* str) { init(str); }
		inline trent(const trent::type& t) { init(t); }
		inline trent(const float& i) { init(i); }
		inline trent(const double& i) { init(i); }
		inline trent(const long double& i) { init(i); }
		inline trent(const signed char& i) { init(i); }
		inline trent(const signed short& i) { init(i); }
		inline trent(const signed int& i) { init(i); }
		inline trent(const signed long& i) { init(i); }
		inline trent(const signed long long& i) { init(i); }
		inline trent(const unsigned char& i) { init(i); }
		inline trent(const unsigned short& i) { init(i); }
		inline trent(const unsigned int& i) { init(i); }
		inline trent(const unsigned long& i) { init(i); }
		inline trent(const unsigned long long& i) { init(i); }

	private:
		void init(trent::type t);
		void init(const std::string& str);
		void init(const char* str);
		void init(const float& i);
		void init(const double& i);
		void init(const long double& i);
		void init(const signed char& i);
		void init(const signed short& i);
		void init(const signed int& i);
		void init(const signed long& i);
		void init(const signed long long& i);
		void init(const unsigned char& i);
		void init(const unsigned short& i);
		void init(const unsigned int& i);
		void init(const unsigned long& i);
		void init(const unsigned long long& i);

		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}


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

		integer_type as_integer() const;
		integer_type as_integer_default(integer_type i) const;
		result<integer_type> as_integer_critical() const;

		string_type& as_string();
		const string_type& as_string() const;
		const gxx::buffer as_buffer() const;
		string_type& as_string_default(string_type& str);
		result<string_type&> as_string_critical();
		result<const string_type&> as_string_critical() const;
		

		REFERENCE_GETTER(unsafe_numer, m_num);
		REFERENCE_GETTER(unsafe_integer, m_int);
		REFERENCE_GETTER(unsafe_string, m_str);
		REFERENCE_GETTER(unsafe_list, m_arr);
		REFERENCE_GETTER(unsafe_dict, m_dict);

		CONSTREF_GETTER(unsafe_numer_const, m_num);
		CONSTREF_GETTER(unsafe_integer_const, m_int);
		CONSTREF_GETTER(unsafe_string_const, m_str);
		CONSTREF_GETTER(unsafe_list_const, m_arr);
		CONSTREF_GETTER(unsafe_dict_const, m_dict);


		trent::type get_type() const;
		const char * type_to_str() const;

		bool is_nil() const 		{ return m_type == type::nil; }
		bool is_numer() const 		{ return m_type == type::numer || m_type == type::integer; }
		bool is_integer() const     { return m_type == type::integer; }
		bool is_list() const		{ return m_type == type::list; }
		bool is_dict() const        { return m_type == type::dict; }
		bool is_string() const 		{ return m_type == type::string; }
		
		strlst check_dict(strlst lst, check_type ct);
		std::pair<strlst,strlst> check_dict_symmetric(strlst lst);

	public:
		trent& operator= (const trent& other);
		trent& operator= (const std::string& str);

		trent& operator= (float num);
		trent& operator= (double num);
		trent& operator= (long double num);

		trent& operator= (signed char i);
		trent& operator= (signed short i);
		trent& operator= (signed int i);
		trent& operator= (signed long i);
		trent& operator= (signed long long i);
		trent& operator= (unsigned char i);
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

				case trent::type::integer:
					os.print(unsafe_integer_const());
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