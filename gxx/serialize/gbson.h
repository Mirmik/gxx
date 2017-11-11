#ifndef GXX_SERIALIZE_GBSON_H
#define GXX_SERIALIZE_GBSON_H

#include <gxx/io/iostream.h>
#include <gxx/serialize/trent.h>
#include <gxx/util/gbson.h>
#include <gxx/result.h>

namespace gxx {
    namespace gbson {
        using namespace result_type;

        void dump(const trent& tr, gxx::io::ostream& os);
        inline void dump(const trent& tr, gxx::io::ostream&& os) { dump(tr, os); }

        result<trent> parse(gxx::io::istream& is);
        static inline result<trent> parse(gxx::io::istream&& is) { return parse(is); };
    }
}

#endif // GBSON_H
