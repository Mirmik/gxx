#ifndef GXX_SERIALIZE_GBSON_H
#define GXX_SERIALIZE_GBSON_H

#include <gxx/io/ostream.h>
#include <gxx/serialize/trent.h>

namespace gxx {
    namespace gbson {
        void print_to(const trent& tr, gxx::io::ostream& os);
        //void pretty_print_to(const trent& tr, std::ostream& os, int tab = 0);

        //result<trent> parse(std::istream& is);
        //trent parse_number(std::istream& is);
        //result<trent> parse_string(std::istream& is);
        //result<trent> parse_array(std::istream& is);
        //result<trent> parse_dictionary(std::istream& is);
    }
}

#endif // GBSON_H
