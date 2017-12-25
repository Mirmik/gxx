#ifndef GXX_GEOM3_H
#define GXX_GEOM3_H

#include <gxx/math/malgo3.h>
#include <gxx/util/setget.h>
#include <gxx/print.h>
#include <limits>

namespace gxx { namespace geom3 {
	constexpr static double infinity = std::numeric_limits<double>::infinity();
	constexpr static double precision = 0.00000001;

	class point : public malgo3::vector3<double> {
	public: 
		point() = default;
		point(double x, double y, double z) : malgo3::vector3<double>(x,y,z) {}
		point(const point& oth) : malgo3::vector3<double>(oth) {}
		point(const malgo3::vector3<double>& oth) : malgo3::vector3<double>(oth) {}
		double distance(const point& oth) { return sub(oth).abs(); }
	};

	class vector : public malgo3::vector3<double> {
	public:
		vector() = default;
		vector(double x, double y, double z) : malgo3::vector3<double>(x,y,z) {}
		vector(const vector& oth) : malgo3::vector3<double>(oth) {}
		vector(const malgo3::vector3<double>& oth) : malgo3::vector3<double>(oth) {}
	};

	class direction : public malgo3::vector3<double> {
	public:
		direction() : malgo3::vector3<double>(0,0,1) {};
		direction(double x, double y, double z, bool norm = true) : malgo3::vector3<double>(x,y,z) { if (norm) self_normalize(); }
		direction(const direction& oth) : malgo3::vector3<double>(oth) {}
		direction(const malgo3::vector3<double>& oth, bool norm = true) : malgo3::vector3<double>(oth) { if (norm) self_normalize(); }
	};

	class axis {
	public:
		point l;
		direction d;

		axis(point l, direction d) : l(l), d(d) {}

		CONSTREF_GETTER(loc, l);
		CONSTREF_GETTER(dir, d);
	};

	class axis2 {
	public:
		point l;
		direction n;
		direction dx;
		direction dy;
	
		axis2(point l, direction n, direction vx) : l(l), n(n) {
			dy = n.vecmul(vx); 
			dx = dy.vecmul(n); 
		}

		axis2(point l, direction n) : l(l), n(n) {
			vector vx;

			if (n.is_same(vector(0,0,1), precision)) vx = vector(1,0,0);
			else vx = direction(0,0,1);

			dy = n.vecmul(vx); 
			dx = dy.vecmul(n); 
		}

		axis2(point a, point b, point c) : l(a) {
			dx = direction(b-a);
			auto dpy = b-c;
			n = dx.vecmul(dpy);
			dy = direction(n.vecmul(dx));
		}

		CONSTREF_GETTER(loc, l);
		CONSTREF_GETTER(dirx, dx);
		CONSTREF_GETTER(diry, dy);

		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint(o,"(l:{},x:{},y:{},n:{})", l, dx, dy, n);
		}
	};

	class axis3 {
	public:
		point l;
		direction dx;
		direction dy;
		direction dz;

		axis3(point l, direction n, direction vx) : l(l), dz(n) {
			dy = n.vecmul(vx); 
			dx = dy.vecmul(n); 
		}
	
		CONSTREF_GETTER(loc, l);
		CONSTREF_GETTER(dirx, dx);
		CONSTREF_GETTER(diry, dy);
		CONSTREF_GETTER(dirz, dz);

		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint(o,"(l:{},x:{},y:{},z:{})", l, dx, dy, dz);
		}
	};

	inline point origin() { return point(0,0,0); }

	inline direction dirx() { return direction(1,0,0,false); }
	inline direction diry() { return direction(0,1,0,false); }
	inline direction dirz() { return direction(0,0,1,false); }

	inline axis Ox() { return axis(origin(), direction(1,0,0)); }	
	inline axis Oy() { return axis(origin(), direction(0,1,0)); }
	inline axis Oz() { return axis(origin(), direction(0,0,1)); }

	inline axis2 Oxy() { return axis2(origin(), direction(0,0,1), direction(1,0,0)); }
	inline axis2 Oyz() { return axis2(origin(), direction(1,0,0), direction(0,1,0)); }
	inline axis2 Ozx() { return axis2(origin(), direction(0,1,0), direction(0,0,1)); }
	/*inline axis2 Oyx() { return axis2(origin(), direction(0,0,1), direction(0,1,0)); }
	inline axis2 Ozy() { return axis2(origin(), direction(1,0,0), direction(0,0,1)); }
	inline axis2 Oxz() { return axis2(origin(), direction(0,1,0), direction(1,0,0)); }*/
	
	inline axis3 Ovector3() { return axis3(origin(), direction(0,0,1), direction(1,0,0)); }
}}

#endif