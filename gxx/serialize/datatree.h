#ifndef GXX_DATATREE_H
#define GXX_DATATREE_H

#include <cstdint>
#include <cassert>
#include <utility>

#include <string>
#include <vector>
#include <map>

#include <gxx/string.h>

#include <gxx/util/ctrdtr.h>
#include <gxx/buffer.h>

namespace gxx {
	class datatree {
	public:
		enum class type {
			string,
			array,
			dictionary,
			integer,
			noinit,
		};

		using check_type = uint8_t;

		static constexpr check_type check_subset = 0;
		static constexpr check_type check_gyperset = 1;
		static constexpr check_type check_equal = 2;

	protected:
		datatree::type m_type = datatree::type::noinit;

		union {
			int64_t m_i64;
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
		datatree(int64_t i64);

	private:
		template <typename T>	
		void reset(T obj) {
			invalidate();
			init(obj);
		}

		void init(datatree::type t);
		void init(const std::string& str);
		void init(const int64_t& i64);
		void invalidate();

	public:
		datatree& operator[](size_t i);
		datatree& operator[](const char* key);
		datatree& operator[](const std::string& key);
		datatree& operator[](const gxx::buffer& key);

		std::map<std::string, datatree>& as_dictionary();
		std::vector<datatree>& as_vector();
		std::string& as_string();
		int64_t& as_integer();

		int64_t get_integer(const char*, int64_t def);
		int64_t get_integer(const std::string&, int64_t def);

		datatree::type get_type() const;
		const char * type_to_str();

		bool is_nil() 			{ return m_type == type::noinit; }
		bool is_integer() 		{ return m_type == type::integer; }
		bool is_array() 		{ return m_type == type::array; }
		bool is_dictionary()	{ return m_type == type::dictionary; }
		bool is_string() 		{ return m_type == type::string; }
		
		strlst check_dict(strlst lst, check_type ct);

	public:
		datatree& operator= (const datatree& other);
		datatree& operator= (const std::string& str);
		datatree& operator= (const int64_t& i64);
		int size();

		bool contains(gxx::buffer buf);
	};

}

#endif