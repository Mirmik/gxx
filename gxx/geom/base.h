#ifndef GXX_GEOM_BASE_H
#define GXX_GEOM_BASE_H

#include <gxx/print.h>
#include <gxx/util/setget.h>
#include <gxx/math/vector.h>

namespace gxx {
	namespace geom3d {
		/*class xyz {
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
			xyz() = default;
			xyz(float x, float y, float z);

			size_t printTo(io::ostream &o) const {
				return gxx::fprint(o, "({},{},{})", x, y, z);
			}
		};*/

		class Point;
		class Vector;
		class Direction;

		class Vector {
		public:
			gxx::math::vector3 raw;

		public:
			Vector(float x, float y, float z);
			Vector(const math::vector3& oth);
			Vector(const Point& spnt, const Point& epnt);
			Vector(const Direction& dir, float length);

			//float abs() { return eval_abs(); }

			Vector translate(const geom3d::Vector& vect) { raw.self_add(vect.raw); }
			Vector rotateX(float angle) { raw.self_rotateX(angle); }
			Vector rotateY(float angle) { raw.self_rotateY(angle); }
			Vector rotateZ(float angle) { raw.self_rotateZ(angle); }
			Vector scale(float scl) { raw.self_scale(scl); }

			Vector translated(const geom3d::Vector& vect) { return Vector(raw.add(vect.raw)); }
			Vector rotatedX(float angle) { return Vector(raw.rotateX(angle)); }
			Vector rotatedY(float angle) { return Vector(raw.rotateY(angle)); }
			Vector rotatedZ(float angle) { return Vector(raw.rotateZ(angle)); }
			Vector scaled(float scl) { return Vector(raw.scale(scl)); }
		};

		class Point {
		public:
			gxx::math::vector3 raw;

		public:
			Point(float x, float y, float z);
			Point(const math::vector3& oth);

			void translate(const geom3d::Vector& vect) { raw.self_add(vect.raw); }
			void rotateX(float angle) { raw.self_rotateX(angle); }
			void rotateY(float angle) { raw.self_rotateY(angle); }
			void rotateZ(float angle) { raw.self_rotateZ(angle); }

			Point translated(const geom3d::Vector& vect) { return Point(raw.add(vect.raw)); }
			Point rotatedX(float angle) { return Point(raw.rotateX(angle)); }
			Point rotatedY(float angle) { return Point(raw.rotateY(angle)); }
			Point rotatedZ(float angle) { return Point(raw.rotateZ(angle)); }
		};

		

		class Direction {
		public:
			gxx::math::vector3 raw;

		public:
			Direction(float x, float y, float z) : raw(x,y,z) { raw.self_normalize(); }
			Direction(const math::vector3& oth) : Direction(oth.x, oth.y, oth.z) {};
			Direction(const geom3d::Vector& oth) : Direction(oth.raw) {};
		};

		class Axis {
			Point 	pnt;
			Direction dir;

		public:
			const Point& location() const { return pnt; }
			const Direction& direction() const { return dir; }

		public:
			Axis(const Point& vrx, const Direction& dir);
		};
/*
		class Axis2 {
			Point origin;

		};


		class line {
			Axis 	ax;

		public:
			const Point& 	location() const { return ax.location(); }
			const Direction& 	direction() const { return ax.direction(); }
			const Axis& 	position() const { return ax; }

			line(const Point& pnt, const Direction& dir) : ax(pnt,dir) {}
			line(const Axis& ax) : ax(ax) {}

			float distance(const line& oth) {

			}
		};





		inline Vector vector_multiply(const Vector& a, const Vector& b) {
			return Vector(a.coord_cross_mul(b));
		}*/
	}
}

#endif
