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
	class datatree {
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
		datatree::type m_type = datatree::type::noinit;

		union {
			double m_num;
			std::string m_str;
			std::vector<datatree> m_arr;
			std::map<std::string, datatree> m_dict;
		};

	public:
		~datatree();
		datatree();
		datatree(const datatree& other);
		datatree(const std::string& str);
		datatree(const datatree::type& t);
		datatree(double i64);

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(datatree::type t);
		void init(const std::string& str);
		void init(const double& i64);
		void invalidate();

	public:
		datatree& operator[](size_t i);
		datatree& operator[](const char* key);
		datatree& operator[](const std::string& key);
		datatree& operator[](const gxx::buffer& key);

		std::map<std::string, datatree>& as_dictionary();
                result<std::map<std::string, datatree>&> as_dictionary_critical();

                std::vector<datatree>& as_array();
                result<std::vector<datatree>&> as_array_critical();
                std::vector<datatree>& as_vector();
                result<std::vector<datatree>&> as_vector_critical();
		
		const double& as_numer();
		const double as_numer_default(const double i);
		result<const double&> as_numer_critical();

		const std::string& as_string();
		const std::string& as_string_default(const std::string& str);
		result<const std::string&> as_string_critical();
		
		
		//double get_number(const char*, double def);
		//double get_number(const std::string&, double def);

		//result<double> get_number_critical(const std::string&);
		


		datatree::type get_type() const;
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
		datatree& operator= (const datatree& other);
		datatree& operator= (const std::string& str);
		datatree& operator= (const double& i64);
		int size();

		bool contains(gxx::buffer buf);
	};
}

#endif
