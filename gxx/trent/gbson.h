#ifndef GXX_SERIALIZE_GBSON_H
#define GXX_SERIALIZE_GBSON_H

#include <gxx/io/iostream.h>
#include <gxx/trent/trent.h>
//#include <gxx/util/gbson.h>
#include <gxx/result.h>

namespace gxx {

	//static constexpr unsigned char gbson_integer_type = 0;
	/*static constexpr unsigned char gbson_numer_type = 1;
	static constexpr unsigned char gbson_integer_type = 2;
	static constexpr unsigned char gbson_string_type = 3;
	static constexpr unsigned char gbson_list_type = 4;
	static constexpr unsigned char gbson_dict_type = 5;*/

	constexpr int8_t GBSON_INTERNAL_ERROR = -10;

	namespace gbson {
		enum class type : uint8_t {
			integer = 0,
			numer = 1,
			string = 2,
			list = 3,
			dict = 4,
		};

		int dump(const gxx::trent& tr, char* buffer, size_t maxlen);
		int load(	   gxx::trent& tr, char* buffer, size_t maxlen);


		//using namespace result_type;

		/*void dump(const trent& tr, gxx::io::ostream& os);
		inline void dump(const trent& tr, gxx::io::ostream&& os) { dump(tr, os); }

		void dump(const trent& tr, std::ostream& os);
		inline void dump(const trent& tr, std::ostream&& os) { dump(tr, os); }

		result<trent> parse(gxx::io::istream& is);
		static inline result<trent> parse(gxx::io::istream&& is) { return parse(is); };
	
		result<trent> parse(std::istream& is);
		static inline result<trent> parse(std::istream&& is) { return parse(is); };
		*/


	}
}

#endif // GBSON_H
