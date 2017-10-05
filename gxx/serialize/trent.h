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

using namespace gxx::result_type;

namespace gxx {
	class trent {
	public:
		enum class type {
			string,
			array,
			dictionary,
			number,
			noinit,
		};

		using check_type = uint8_t;

		static constexpr check_type check_subset = 0;
		static constexpr check_type check_superset = 1;
		static constexpr check_type check_equal = 2;

	protected:
		trent::type m_type = trent::type::noinit;

		union {
			double m_num;
			std::string m_str;
			std::vector<trent> m_arr;
			std::map<std::string, trent> m_dict;
		};

	public:
		~trent();
		trent();
		trent(const trent& other);
		trent(const std::string& str);
		trent(const trent::type& t);
		trent(double i64);

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(trent::type t);
		void init(const std::string& str);
		void init(const double& i64);
		void invalidate();

	public:
		trent& operator[](size_t i);
		trent& operator[](const char* key);
		trent& operator[](const std::string& key);
		trent& operator[](const gxx::buffer& key);

		std::map<std::string, trent>& as_dictionary();
                result<std::map<std::string, trent>&> as_dictionary_critical();

                std::vector<trent>& as_array();
                result<std::vector<trent>&> as_array_critical();
                std::vector<trent>& as_vector();
                result<std::vector<trent>&> as_vector_critical();
		
		const double& as_numer();
		const double as_numer_default(const double i);
		result<const double&> as_numer_critical();

		const std::string& as_string();
		const std::string& as_string_default(const std::string& str);
		result<const std::string&> as_string_critical();
		
		
		//double get_number(const char*, double def);
		//double get_number(const std::string&, double def);

		//result<double> get_number_critical(const std::string&);
		
		REFERENCE_GETTER(unsafe_number, m_num);
		REFERENCE_GETTER(unsafe_string, m_str);
		REFERENCE_GETTER(unsafe_array, m_arr);
		REFERENCE_GETTER(unsafe_dictionary, m_dict);


		trent::type get_type() const;
		const char * type_to_str();

		bool is_nil() 			{ return m_type == type::noinit; }
		bool is_numer() 		{ return m_type == type::number; }
		//bool is_float() 		{ return m_type == type::float; }
		bool is_array() 		{ return m_type == type::array; }
		bool is_dictionary()	{ return m_type == type::dictionary; }
		bool is_string() 		{ return m_type == type::string; }
		
                strlst check_dict(strlst lst, check_type ct);
		std::pair<strlst,strlst> check_dict_symmetric(strlst lst);

	public:
		trent& operator= (const trent& other);
		trent& operator= (const std::string& str);
		trent& operator= (const double& i64);
		int size();

		bool contains(gxx::buffer buf);
	};
}

#endif
