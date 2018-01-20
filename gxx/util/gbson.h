#ifndef GXX_UTIL_GBSON_H
#define GXX_UTIL_GBSON_H

//Определение номеров типов протокола gbson

namespace gxx {
	static constexpr unsigned char gbson_integer_type = 0;
	static constexpr unsigned char gbson_float_type = 1;
	static constexpr unsigned char gbson_bytes_type = 2;
	static constexpr unsigned char gbson_array_type = 3;
	static constexpr unsigned char gbson_dictionary_type = 4;
    //static constexpr unsigned char gbson_boolean_type = 5;
}

#endif