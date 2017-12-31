#ifndef GXX_GEOM_GEOM2_H
#define GXX_GEOM_GEOM2_H

#include <gxx/print/stdprint.h>
#include <gxx/math/malgo2.h>
#include <limits>
#include <memory>

namespace gxx { namespace geom2 {
	constexpr static double infinity = std::numeric_limits<double>::infinity();
	constexpr static double precision = 0.00000001;

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
		//virtual double rotation_angle() const { return 0; }
		virtual size_t printTo(gxx::io::ostream& o) const { return gxx::print("nilcurve"); }	
		virtual curve_enum gettype() const { return curve_enum::none; }	

		//point start() const { return d0(bmin); }
		//point finish() const { return d0(bmax); }
		//point start_d1() const { return d1(bmin); }
		//point finish_d1() const { return d1(bmax); }

		//double bmax, bmin;
		//curve() : bmax(tmax()), bmin(tmin()) {}
		//curve(double bmin, double bmax) : bmax(bmax), bmin(bmin) {}
	};

	class nilcurve : public curve {
		point d0(double t) const override { return point(); }
		vector d1(double t) const override { return vector(); }
	};

	class line : public curve {
	public:
		point l;
		direction d;

		line(const point& l, const vector& v) : l(l), d(v) {}
		//line(const point& p1, const point& p2) : l(p1), d(p2-p1) {}

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
			return gxx::fprint("line(l:{},d:{})",l,d);
		} 
	};


	class curve_segment : public curve {
	public:
		double bmin, bmax;
		std::shared_ptr<curve> crv;
		curve_segment(std::shared_ptr<curve> sptr) : crv(sptr) {}
	};

	struct point_intersection {
		double first;
		double second;
		point_intersection(double a, double b) : first(a), second(b) {}
		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint("({},{})", first, second);
		}
	};

	struct interval_intersection {
		double first_start;
		double first_finish;
		double second_start;
		double second_finish;
		interval_intersection(double a, double b, double c, double d) : first_start(a), first_finish(b), second_start(c), second_finish(d) {}
		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint("({},{},{},{})", first_start, first_finish, second_start, second_finish);
		}
	};

	struct curve_intersection_result {
		std::vector<point_intersection> points;
		std::vector<interval_intersection> intervals;
		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint("(pnts:{}, ints:{})", points, intervals);
		}
	};

	inline curve_intersection_result intersect_line2_line2(const line& a, const line& b) {
		curve_intersection_result res;
		
		point l12 = a.l - b.l;
		double dd = a.d.crossmul(b.d);

		if (gxx::math::early_zero(dd, precision)) {
			if (gxx::math::early_zero(l12.crossmul(a.d), precision)) {
				//прямые совпадают
				gxx::println("same");
				res.intervals.emplace_back(-infinity, infinity, -infinity, infinity);
			}
			else {
				gxx::println("not intersect");
				//нет пересечений
			}
		}
		else {
			gxx::println("one point");
			//одна точка пересечения
			double t1 = b.d.crossmul(l12) / dd;
			double t2 = a.d.crossmul(l12) / dd;
			res.points.emplace_back(t1, t2);
		}

		return res;
	}

	inline curve_intersection_result intersect_curve2_curve2(const curve& a, const curve& b) {
		if (typeid(a) == typeid(line) && typeid(b) == typeid(line)) {
			return intersect_line2_line2(static_cast<const line&>(a), static_cast<const line&>(b));
		}
	}

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