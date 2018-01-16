#ifndef GXX_DATATREE_H
#define GXX_DATATREE_H

#include <cstdint>
#include <cassert>
#include <utility>

#include <string>
#include <vector>
#include <map>

#include <gxx/result.h>
#include <gxx/string.h>
#include <gxx/util/ctrdtr.h>
#include <gxx/buffer.h>
#include <gxx/print.h>

using namespace gxx::result_type;

namespace gxx {
	class trent {
	public:
		enum class type {
			string,
			array,
			dictionary,
			integer,
			single_floating,
			double_floating,
			noinit,
		};

		using check_type = uint8_t;

		static constexpr check_type check_subset = 0;
		static constexpr check_type check_superset = 1;
		static constexpr check_type check_equal = 2;

		using sfloat_type = float;
		using dfloat_type = long double;
		using numer_type = dfloat_type;
		using integer_type = int64_t;
		using array_type = std::vector<trent>;
		using dictionary_type = std::map<std::string, trent>;

	protected:
		trent::type m_type = trent::type::noinit;

		union {
			int64_t m_i64;
			sfloat_type m_sflt;
			dfloat_type m_dflt;
			std::string m_str;
			std::vector<trent> m_arr;
			std::map<std::string, trent> m_dict;
		};

	public:
		~trent();
		trent();
		trent(const trent& other);
		trent(const trent::type& t);

		trent(const char* str);
		trent(const std::string& str);

		trent(short i);
		trent(int i);
		trent(long i);
		trent(long long i);

		trent(float num);
		trent(double num);
		trent(long double num);

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(trent::type t);
		void init(const std::string& str);
		void init(const char* str);

		void init(float i);
		void init(double i);
		void init(long double i);

		void init(short i);
		void init(int i);
		void init(long i);
		void init(long long i);

		void init(unsigned short i);
		void init(unsigned int i);
		void init(unsigned long i);
		void init(unsigned long long i);

		void init_array(size_t reserve);
		void invalidate();

	public:
		trent& operator[](int i);
		trent& operator[](const char* key);
		trent& operator[](const std::string& key);
		trent& operator[](const gxx::buffer& key);

		trent& at(int i);
		trent& at(const char* key);
		trent& at(const std::string& key);
		trent& at(const gxx::buffer& key);

		const trent& at(int i) const;
		const trent& at(const char* key) const;
		const trent& at(const std::string& key) const;
		const trent& at(const gxx::buffer& key) const;

		std::map<std::string, trent>& as_dictionary();
		result<std::map<std::string, trent>&> as_dictionary_critical();

		std::vector<trent>& as_array();
		const std::vector<trent>& as_array() const;

		result<std::vector<trent>&> as_array_critical();
		result<const std::vector<trent>&> as_array_critical() const;
		
		std::vector<trent>& as_vector();
		const std::vector<trent>& as_vector() const;

		result<std::vector<trent>&> as_vector_critical();
		result<const std::vector<trent>&> as_vector_critical() const;
		
		numer_type as_numer() const;

		integer_type as_integer() const;
		result<integer_type> as_integer_critical() const;
		sfloat_type as_sfloat() const;
		dfloat_type as_dfloat() const;

		const double as_numer_default(const double i);
		result<double> as_numer_critical() const;

		std::string& as_string();
		const gxx::buffer as_buffer() const;
		std::string& as_string_default(std::string& str);
		result<std::string&> as_string_critical();
		result<const std::string&> as_string_critical() const;
		
		
		//double get_numer(const char*, double def);
		//double get_numer(const std::string&, double def);

		//result<double> get_numer_critical(const std::string&);

		REFERENCE_GETTER(unsafe_integer, m_i64);
		REFERENCE_GETTER(unsafe_sfloat, m_sflt);
		REFERENCE_GETTER(unsafe_dfloat, m_dflt);
		REFERENCE_GETTER(unsafe_string, m_str);
		REFERENCE_GETTER(unsafe_array, m_arr);
		REFERENCE_GETTER(unsafe_dictionary, m_dict);

		CONSTREF_GETTER(unsafe_integer_const, m_i64);
		CONSTREF_GETTER(unsafe_sfloat_const, m_sflt);
		CONSTREF_GETTER(unsafe_dfloat_const, m_dflt);
		CONSTREF_GETTER(unsafe_string_const, m_str);
		CONSTREF_GETTER(unsafe_array_const, m_arr);
		CONSTREF_GETTER(unsafe_dictionary_const, m_dict);


		trent::type get_type() const;
		const char * type_to_str();

		bool is_nil() const 		{ return m_type == type::noinit; }
		bool is_numer() const 		{ return m_type == type::single_floating || m_type == type::double_floating || m_type == type::integer; }
		bool is_float() const 		{ return m_type == type::single_floating || m_type == type::double_floating; }
		bool is_integer() const 	{ return m_type == type::integer; }
		bool is_array() const		{ return m_type == type::array; }
		bool is_dictionary() const  { return m_type == type::dictionary; }
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
		
				case trent::type::integer:
				    os.print(unsafe_integer_const());
				    break;
			
				case trent::type::single_floating:
				    os.print(unsafe_sfloat_const());
						    return 0;
			
				case trent::type::double_floating:
				    os.print(unsafe_dfloat_const());
				    return 0;
			
				case trent::type::string: 
				    os.putchar('"'); 
				    os.print(unsafe_string_const());
				    os.putchar('"');
				    return 0;
				case trent::type::array: 
				    os.putchar('[');
				    for(auto& v : unsafe_array_const()) {
					    if (sep) os.putchar(',');
					    v.printTo(os);
					    sep = true;
				    }
				    os.putchar(']');
				    return 0; 
				case trent::type::dictionary: 
				    os.putchar('{');
				    for(auto& p : unsafe_dictionary_const()) {
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
				case trent::type::noinit:
				    os.print("nil");
				    return 0;
			}

		}	
	};
}

#endif
