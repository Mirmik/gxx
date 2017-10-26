#ifndef GXX_CONTAINER_H
#define GXX_CONTAINER_H

#include <gxx/iteratible.h>

namespace gxx { namespace container {
    template <typename Container, typename Type>
    bool contain(const Container& ctr, const Type& ptn) {
        for (const auto& v : ctr) { if (v == ptn) return true; }
        return false;
    }

    /*template<typename Container, typename Class, typename Field, Field Class::* member>
    class iterate_field {
        typename Container::iterator it;
        typename Container::iterator eit;

        using iterator = gxx::gen<>;

    public:
        iterate_field(Container& ctr) {
            it = ctr.begin();
            eit = ctr.end();
        }

        K& value() {
            return const_cast<K&>(it->first);
        }

        bool next() {
            it++;
            if (it == eit) return true;
            return false;
        }

        iterator begin() {
            return iterator(*this, dict.empty() ? true : false);
        }

        iterator end() {
            return iterator(*this, true);
        }
    };*/
}}

#endif // GXX_CONTAINER_H
