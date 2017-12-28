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

	enum class curve_enum : uint8_t {
		none,
		line
	};

	class curve {
	public:
		virtual point d0(double t) const = 0;
		virtual vector d1(double t) const = 0;
		virtual bool is_closed() { return false; }
		virtual bool is_periodic() { return false; }
		virtual double tmin() { return 0; }
		virtual double tmax() { return 0; }
		virtual double rotation_angle() const { return 0; }
		virtual ~curve() {}
		virtual size_t printTo(gxx::io::ostream& o) const { return gxx::print("nilcurve"); }	
		virtual curve_enum gettype() const { return curve_enum::none; }	

		point start() const { return d0(bmin); }
		point finish() const { return d0(bmax); }

		double bmax, bmin;
		curve() : bmax(tmax()), bmin(tmin()) {}
		curve(double bmin, double bmax) : bmax(bmax), bmin(bmin) {}
	};

	class nilcurve : public curve {
		point d0(double t) const override { return point(); }
		vector d1(double t) const override { return vector(); }
	};

	class line : public curve {
	public:
		point l;
		direction d;

		line(const point& l, const vector& v) : l(l), d(v), curve(0, v.abs()) {}

		point d0(double t) const override {
			return point(l.x + d.x * t, l.y + d.y * t);
		}

		vector d1(double t) const override {
			return d;
		}

		double tmin() override { return - geom2::infinity; }
		double tmax() override { return   geom2::infinity; }

		curve_enum gettype() const override { return curve_enum::line; }	

		size_t printTo(gxx::io::ostream& o) const override {
			return gxx::fprint("line(l:{},d:{},bmin:{},bmax:{})",l,d,bmin,bmax);
		} 
	};

	/*class curve {
	public:
		union {
			nilcurve nil;
			line ln;
		};

		curve() {
			new (&nil) nilcurve();
		}

		curve(const line& ctr) {
			new (&ln) line(ctr);
		}
		
		curve(const curve& oth){
			copy(oth);
		}
		
		curve(const point& pnt, const vector& vec) {
			new (&ln) line(pnt, vec);
		}

		~curve(){}

		curve& operator=(curve&& oth) {				
			invalidate();
			move(std::move(oth));
		}

		void copy(const curve& oth) {
			switch(oth.gettype()) {
				case curve_enum::none: new (&nil) nilcurve(); return;
				case curve_enum::line: new (&ln) line(oth.ln); return;
				default: gxx::panic("copy: undefined curve2");
			}
		}

		void move(curve&& oth) {
			switch(oth.gettype()) {
				case curve_enum::none: new (&nil) nilcurve(); return;
				case curve_enum::line: new (&ln) line(oth.ln); return;
				default: gxx::panic("move: undefined curve2");
			}
		}

		void invalidate() {}

		basic_curve& abstract() { return *static_cast<basic_curve*>(&ln); }
		const basic_curve& abstract() const { return *static_cast<const basic_curve*>(&ln); }
		curve_enum gettype() const { return abstract().gettype(); }

		point d0(double t) const {
			return abstract().d0(t);
		}

		vector d1(double t) const {
			return abstract().d1(t);
		}

		double bmin() const {
			return abstract().bmin;
		}

		double bmax() const {
			return abstract().bmax;
		}

		double rotation_angle() const {
			return abstract().rotation_angle();
		}

		size_t printTo(gxx::io::ostream& o) const {
			return abstract().printTo(o);
		}
	};*/
}}

#endif