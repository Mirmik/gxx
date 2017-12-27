#ifndef GXX_GEOM_GEOM2_H
#define GXX_GEOM_GEOM2_H

#include <gxx/math/malgo2.h>
#include <limits>

namespace gxx { namespace geom2 {
	constexpr static double infinity = std::numeric_limits<double>::infinity();

	class point : public malgo2::vector2<double> {
	public: 
		point()=default;
		point(double x, double y) : malgo2::vector2<double>(x,y) {}
		point(const point& oth) : malgo2::vector2<double>(oth) {}
		point(const malgo2::vector2<double>& oth) : malgo2::vector2<double>(oth) {}
	};

	class vector : public malgo2::vector2<double> {
	public:
		vector()=default;
		vector(double x, double y) : malgo2::vector2<double>(x,y) {}
		vector(const vector& oth) : malgo2::vector2<double>(oth) {}
		vector(const malgo2::vector2<double>& oth) : malgo2::vector2<double>(oth) {}
	};

	class direction : public malgo2::vector2<double> {
	public:
		direction()=default;
		direction(double x, double y, bool norm = true) : malgo2::vector2<double>(x,y) { if (norm) self_normalize(); }
		direction(const direction& oth) : malgo2::vector2<double>(oth) {}
		direction(const malgo2::vector2<double>& oth, bool norm = true) : malgo2::vector2<double>(oth) { if (norm) self_normalize(); }
	};

	class basic_curve {
	public:
		virtual point d0(double t) = 0;
		virtual vector d1(double t) = 0;
		virtual bool is_closed() { return false; }
		virtual bool is_periodic() { return false; }
		virtual double tmin() { return 0; }
		virtual double tmax() { return 0; }
		virtual ~basic_curve() {}
		virtual size_t printTo(gxx::io::ostream& o) const { return gxx::print("curve"); }		

		double bmax, bmin;
		basic_curve() : bmax(tmax()), bmin(tmin()) {}
		basic_curve(double bmin, double bmax) : bmax(bmax), bmin(bmin) {}
	};

	class line : public basic_curve {
	public:
		point l;
		direction d;

		line(const point& l, const vector& v) : l(l), d(v), basic_curve(0, v.abs()) {}

		point d0(double t) override {
			return point(l.x + d.x * t, l.y + d.y * t);
		}

		vector d1(double t) override {
			return d;
		}

		double tmin() override { return - geom2::infinity; }
		double tmax() override { return   geom2::infinity; }
	};


	enum class curve_enum : uint8_t {
		none,
		line
	};

	class curve {
	public:
		curve_enum type;
		union {
			line ln;
		};

		curve(){}

		curve(const line& ctr) {
			ln = ctr;
			type = curve_enum::line;
		}
		
		curve(const curve& oth){
			copy(oth);
		}
		
		curve(const point& pnt, const vector& vec) {
			ln = line(pnt, vec);
			type = curve_enum::line;
		}

		~curve(){}

		curve& operator=(curve&& oth) {
			invalidate();
			move(std::move(oth));
		}

		void copy(const curve& oth) {
			type = oth.type;
			switch(oth.type) {
				case curve_enum::line:
					ln = oth.ln;
					return;
				default: gxx::panic("copy: undefined curve2");
			}
		}

		void move(curve&& oth) {
			type = oth.type;
			switch(oth.type) {
				case curve_enum::line:
					ln = oth.ln;
					return;
				default: gxx::panic("move: undefined curve2");
			}
		}

		void invalidate() {}
	};
}}

#endif