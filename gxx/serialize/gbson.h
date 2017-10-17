#ifndef GXX_SERIALIZE_GBSON_H
#define GXX_SERIALIZE_GBSON_H

#include <gxx/io/iostream.h>
#include <gxx/serialize/trent.h>

#include <gxx/result.h>

namespace gxx {
    namespace gbson {
        using namespace result_type;

        static constexpr unsigned char gbson_integer_type = 0;
        static constexpr unsigned char gbson_float_type = 1;
        static constexpr unsigned char gbson_bytes_type = 2;
        static constexpr unsigned char gbson_array_type = 3;
        static constexpr unsigned char gbson_dictionary_type = 4;
        //constexpr unsigned char gbson_boolean_type = 5;

        void dump(const trent& tr, gxx::io::ostream& os);
        //void pretty_print_to(const trent& tr, std::ostream& os, int tab = 0);

        //result<trent> parse(std::istream& is);
        //trent parse_number(std::istream& is);
        //result<trent> parse_string(std::istream& is);
        //result<trent> parse_array(std::istream& is);
        //result<trent> parse_dictionary(std::istream& is);

        result<trent> parse(gxx::io::istream& is);
        static inline result<trent> parse(gxx::io::istream&& is) { return parse(is); };
    }
}

#endif // GBSON_H
