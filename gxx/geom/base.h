#ifndef GXX_GEOM_BASE_H
#define GXX_GEOM_BASE_H

#include <gxx/print.h>
#include <gxx/util/setget.h>

namespace gxx {
    namespace geom {
        class xyz {
        public:
            float x,y,z;

        public:
            xyz coord_translate(const xyz& b) {
                return xyz(x+b.x, y+b.y, z+b.z);
            }

            xyz coord_rotateX(float a) {
                float s = sin(a);
                float c = cos(a);
                return xyz(x, y*c-z*s, z*c+y*s);
            }

            xyz coord_rotateY(float a) {
                float s = sin(a);
                float c = cos(a);
                return xyz(x*c+z*s, y, z*c-x*s);
            }

            xyz coord_rotateZ(float a) {
                float s = sin(a);
                float c = cos(a);
                return xyz(x*c-y*s, y*c+x*s, z);
            }

            xyz coord_add(const xyz& b) const {
                return xyz(x+b.x, y+b.y, z+b.z);
            }

            xyz coord_sub(const xyz& b) const {
                return xyz(x-b.x, y-b.y, z-b.z);
            }

            xyz coord_mul(const xyz& b) const {
                return xyz(x*b.x, y*b.y, z*b.z);
            }

            xyz coord_div(const xyz& b) const {
                return xyz(x/b.x, y/b.y, z/b.z);
            }

            xyz coord_cross_mul(const xyz& b) const {
                return xyz(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
            }

            xyz coord_scale(float scl) const {
                return xyz(x*scl, y*scl, z*scl);
            }

            float eval_abs() const {
                return sqrt(x*x + y*y + z*z);
            }


            void change_coord_translate(const xyz& b) {
                x+=b.x; y+=b.y; z+=b.z;
            }

            void change_coord_rotateX(float a) {
                float s = sin(a);
                float c = cos(a);
                float ny = y*c-z*s;
                float nz = z*c+y*s;
                y = ny;
                z = nz;
            }

            void change_coord_rotateY(float a) {
                float s = sin(a);
                float c = cos(a);
                float nx = x*c+z*s;
                float nz = z*c-x*s;
                x = nx;
                z = nz;
            }

            void change_coord_rotateZ(float a) {
                float s = sin(a);
                float c = cos(a);
                float nx = x*c-y*s;
                float ny = y*c+x*s;
                x = nx;
                y = ny;
            }

            void change_coord_add(const xyz& b) {
                x+=b.x; y+=b.y; z+=b.z;
            }

            void change_coord_sub(const xyz& b) {
                x-=b.x; y-=b.y; z-=b.z;
            }

            void change_coord_mul(const xyz& b) {
                x*=b.x; y*=b.y; z*=b.z;
            }

            void change_coord_div(const xyz& b) {
                x/=b.x; y/=b.y; z/=b.z;
            }

            void change_coord_cross_mul(const xyz& b) {
                float nx = y*b.z - z*b.y;
                float ny = z*b.x - x*b.z;
                float nz = x*b.y - y*b.x;
                x = nx; y = ny; z = nz;
            }

            void change_coord_scale(float scl) {
                x*=scl; y*=scl; z*=scl;
            }

        public:
            xyz(float x, float y, float z);

            size_t printTo(io::ostream &o) const {
                return gxx::fprint(o, "({},{},{})", x, y, z);
            }
        };

        class vertex;
        class vector;
        class direction;

        class vector : public xyz {
        public:
            vector(float x, float y, float z);
            vector(const xyz& oth);
            vector(const vertex& spnt, const vertex& epnt);

            float abs() { return eval_abs(); }

            //rotateX;
            //rotateY;
            //rotateZ;
            //translate;

            inline vector rotatedX(float angle) { return vector(coord_rotateX(angle)); }
            inline vector rotatedY(float angle) { return vector(coord_rotateY(angle)); }
            inline vector rotatedZ(float angle) { return vector(coord_rotateZ(angle)); }
            inline vector translated(const xyz& oth) { return vector(coord_translate(oth)); }
            inline vector scaled(float mod) { return vector(coord_scale(mod)); }

            inline vector rotateX(float angle) { change_coord_rotateX(angle); }
            inline vector rotateY(float angle) { change_coord_rotateY(angle); }
            inline vector rotateZ(float angle) { change_coord_rotateZ(angle); }
            inline vector translate(const xyz& oth) { change_coord_translate(oth); }
            inline vector scale(float mod) { change_coord_scale(mod); }
        };

        class direction : public xyz {
        public:
            direction(float x, float y, float z);
            direction(const xyz& oth);
        };

        class vertex : public xyz {
        public:
            vertex(float x, float y, float z);
            vertex(const xyz& oth);

            void translate(const gxx::geom::vector& vect);
            vertex translated(const gxx::geom::vector& vect) { return vertex(coord_translate(vect)); }

            inline vector rotatedX(float angle) { return vector(coord_rotateX(angle)); }
            inline vector rotatedY(float angle) { return vector(coord_rotateY(angle)); }
            inline vector rotatedZ(float angle) { return vector(coord_rotateZ(angle)); }
        };

        class axis {
            vertex vrx;
            direction dir;

        public:
            axis(vertex vrx, direction dir);
        };

        inline vector vector_multiply(const vector& a, const vector& b) {
            return vector(a.coord_cross_mul(b));
        }
    }
}

#endif
