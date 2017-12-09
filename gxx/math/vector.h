#ifndef GXX_MATH_VECTOR_H
#define GXX_MATH_VECTOR_H

#include <math.h>
#include <gxx/math/util.h>
#include <gxx/print.h>

namespace gxx {
	namespace math {
		class vector3 {
		public:
			float x,y,z;			

		public:
			vector3(float x, float y, float z) : x(x), y(y), z(z) {}

			float abs() {
				return sqrt(x*x + y*y + z*z);
			}

			float quick_invabs() {
				return quick_rsqrt(x*x + y*y + z*z);
			}

			vector3 rotateX(float a) {
				float s = sin(a);
				float c = cos(a);
				return vector3(x, y*c-z*s, z*c+y*s);
			}

			vector3 rotateY(float a) {
				float s = sin(a);
				float c = cos(a);
				return vector3(x*c+z*s, y, z*c-x*s);
			}

			vector3 rotateZ(float a) {
				float s = sin(a);
				float c = cos(a);
				return vector3(x*c-y*s, y*c+x*s, z);
			}

			vector3 add(const vector3& b) const {
				return vector3(x+b.x, y+b.y, z+b.z);
			}

			vector3 sub(const vector3& b) const {
				return vector3(x-b.x, y-b.y, z-b.z);
			}

			vector3 coord_mul(const vector3& b) const {
				return vector3(x*b.x, y*b.y, z*b.z);
			}

			vector3 coord_div(const vector3& b) const {
				return vector3(x/b.x, y/b.y, z/b.z);
			}

			vector3 vecmul(const vector3& b) const {
				return vector3(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
			}

			vector3 scale(float scl) {
				return vector3(x*scl, y*scl, z*scl);
			}

			vector3 rscale(float scl) {
				return vector3(x/scl, y/scl, z/scl);
			}

			vector3 normalize() {
				return rscale(abs());
			}

			vector3 quick_normalize() {
				return scale(quick_invabs());
			}

			void self_rotateX(float a) {
				float s = sin(a);
				float c = cos(a);
				float ny = y*c-z*s;
				float nz = z*c+y*s;
				y = ny;
				z = nz;
			}

			void self_rotateY(float a) {
				float s = sin(a);
				float c = cos(a);
				float nx = x*c+z*s;
				float nz = z*c-x*s;
				x = nx;
				z = nz;
			}

			void self_rotateZ(float a) {
				float s = sin(a);
				float c = cos(a);
				float nx = x*c-y*s;
				float ny = y*c+x*s;
				x = nx;
				y = ny;
			}

			void self_add(const vector3& b) {
				x+=b.x; y+=b.y; z+=b.z;
			}

			void self_sub(const vector3& b) {
				x-=b.x; y-=b.y; z-=b.z;
			}

			void self_coord_mul(const vector3& b) {
				x*=b.x; y*=b.y; z*=b.z;
			}

			void self_coord_div(const vector3& b) {
				x/=b.x; y/=b.y; z/=b.z;
			}

			void self_vecmul(const vector3& b) {
				float nx = y*b.z - z*b.y;
				float ny = z*b.x - x*b.z;
				float nz = x*b.y - y*b.x;
				x = nx; y = ny; z = nz;
			}

			void self_scale(float scl) {
				x*=scl; y*=scl; z*=scl;
			}

			void self_rscale(float scl) {
				x/=scl; y/=scl; z/=scl;
			}

			void self_normalize() {
				float mod = abs();
				self_rscale(mod);			
			}

			void self_quick_normalize() {
				float invabs = quick_invabs();
				self_scale(invabs);
			}

			size_t printTo(io::ostream &o) const {
				return gxx::fprint(o, "({},{},{})", x, y, z);
			}

			//static vector3 normalized(float x, float y, float z) {
			//	float invabs = 
			//}
		};

		class vector2 {
		public:
			float x,y;
		
		public:
			vector2(float x, float y) : x(x), y(y) {}

			float abs() {
				return sqrt(x*x + y*y);
			}

			float quick_invabs() {
				return quick_rsqrt(x*x + y*y);
			}

			vector2 rotate(float a) {
				float s = sin(a);
				float c = cos(a);
				return vector2(x*c-y*s, y*c+x*s);
			}

			vector2 add(const vector2& b) const {
				return vector2(x+b.x, y+b.y);
			}

			vector2 sub(const vector2& b) const {
				return vector2(x-b.x, y-b.y);
			}

			vector2 scale(float scl) {
				return vector2(x*scl, y*scl);
			}

			vector2 rscale(float scl) {
				return vector2(x/scl, y/scl);
			}

			vector2 normalize() {
				return rscale(abs());
			}

			vector2 quick_normalize() {
				return scale(quick_invabs());
			}

			void self_rotate(float a) {
				float s = sin(a);
				float c = cos(a);
				float nx = x*c-y*s;
				float ny = y*c+x*s;
				x = nx;
				y = ny;
			}

			void self_add(const vector2& b) {
				x+=b.x; y+=b.y;
			}

			void self_sub(const vector2& b) {
				x-=b.x; y-=b.y;
			}

			void self_scale(float scl) {
				x*=scl; y*=scl;
			}

			void self_rscale(float scl) {
				x/=scl; y/=scl;
			}

			void self_normalize() {
				float mod = abs();
				self_rscale(mod);			
			}

			void self_quick_normalize() {
				float invabs = quick_invabs();
				self_scale(invabs);
			}

			size_t printTo(io::ostream &o) const {
				return gxx::fprint(o, "({},{})", x, y);
			}
		};
	}
}

#endif