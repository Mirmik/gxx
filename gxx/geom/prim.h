#ifndef GXX_GEOM_PRIM_H
#define GXX_GEOM_PRIM_H

#include <gxx/geom/base.h>

namespace gxx {
    namespace geom {
        class segment {
            vertex v1;
            vertex v2;

        public:
            segment(vertex v1, vertex v2) : v1(v1), v2(v2) {}

            float length() const {
                return vector(v1, v2).abs();
            }

            size_t printTo(gxx::io::ostream& o) const {
                gxx::fprint(o, "({},{})", v1, v2);
            }
        };

        class triangle {
            vertex v1;
            vertex v2;
            vertex v3;

        public:
            triangle(vertex v1, vertex v2, vertex v3) : v1(v1), v2(v2), v3(v3) {}

            float area() {
                //Находим площадь треугольника, как половину длины векторного произведения образуюших векторов.
                return vector_multiply(vector(v3, v1), vector(v2, v1)).abs()/2;
            }

            size_t printTo(gxx::io::ostream& o) const {
                gxx::fprint(o, "({},{},{}})", v1, v2, v3);
            }
        };
    }
}

#endif
