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
		line,
		circle
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
		double angle;
		line(const point& l, const vector& v) : l(l), d(v), angle(atan2(v.y, v.x)) {}
		point d0(double t) const override { return point(l.x + d.x * t, l.y + d.y * t); }
		double rev_d0(point pnt) const { return (pnt-l).sclmul(d); }
		vector d1(double t) const override { return d; }
		double tmin() override { return - geom2::infinity; }
		double tmax() override { return   geom2::infinity; }
		curve_enum gettype() const override { return curve_enum::line; }	
		size_t printTo(gxx::io::ostream& o) const override { return gxx::fprint("line(l:{},d:{})",l,d); } 

		double distance(point pnt) const {
			auto l21 = pnt - l;
			return std::fabs(l21.crossmul(d));
		}

		direction normal() const { 
			return direction(-sin(angle), cos(angle)); 
		}
	};

	class circle : public curve {
	public:
		point l;
		double r;
		double sp;
		direction dirx;
		ACCESSOR(center, l);
		ACCESSOR(radius, r);
		circle(double r, const point& l, const direction& d = direction(1,0,false)) : l(l), dirx(d), r(r), sp(atan2(d.y, d.x)) {}
		point d0(double t) const override { auto c = cos(t+sp); auto s = sin(t+sp); return point(l.x + c*r, l.y + s*r); }
		vector d1(double t) const override { gxx::panic("circle"); }
		double tmax() override { return 2 * M_PI; }
		curve_enum gettype() const override { return curve_enum::circle; }	
		size_t printTo(gxx::io::ostream& o) const override { return gxx::fprint("circle(r:{},c:{},v:{})",r,l,dirx); } 
		double sparam() { return atan2(dirx.x, dirx.y); }
	};

	class curve_segment : public curve {
	public:
		double bmin, bmax;
		std::shared_ptr<curve> crv;
		curve_segment(std::shared_ptr<curve> sptr) : crv(sptr) {}
	};

	/*struct point_intersection {
		double first;
		double second;
		bool tangent;
		point_intersection(double a, double b, bool tangent = false) : first(a), second(b), tangent(tangent) {}
		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint("({},{},tan:{})", first, second, tangent);
		}
	};*/

	struct interval {
		double start;
		double finish;
		interval(double start, double finish) : start(start), finish(finish) {}
		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint("({},{})", start, finish);
		}
	};

	class curve_parts {
	public:
		std::vector<double> points;
		std::vector<interval> intervals;
	public:
		size_t printTo(gxx::io::ostream& o) const {
			return gxx::fprint("(pnts:{}, ints:{})", points, intervals);
		}
	};

	
	inline void intersect_line2_line2(const line& a, const line& b, curve_parts& ares, curve_parts& bres) {
		point l12 = a.l - b.l;
		double dd = a.d.crossmul(b.d);

		if (gxx::math::early_zero(dd, precision)) {
			if (gxx::math::early_zero(l12.crossmul(a.d), precision)) {
				//прямые совпадают
				gxx::println("same");
				ares.intervals.emplace_back(-infinity, infinity);
				bres.intervals.emplace_back(-infinity, infinity);
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
			ares.points.emplace_back(t1);
			bres.points.emplace_back(t2);
		}

		return;
	}

	inline void intersect_line2_circle2(const line& a, const circle& b, curve_parts& ares, curve_parts& bres) {
		auto linenorm = a.normal();
		auto distance = linenorm.sclmul(a.l - b.l);
		auto r = b.radius();
		
		if (distance < 0) { linenorm.self_reverse(); distance = -distance; }
				
		if (gxx::math::is_same(distance, r, precision)) {
			gxx::println("касание");			
			auto t1 = a.d.sclmul(b.l-a.l);
			auto t2 = -b.sp + atan2(linenorm.y, linenorm.x); 
			ares.points.emplace_back(t1);
			bres.points.emplace_back(t2);
			return;
		}

		if (distance > r) {
			gxx::println("нет пересечения");
			return;
		}

		auto cos_diff_angle = distance / r;
		auto diff_angle = acos(cos_diff_angle);
		auto t2 = -b.sp + atan2(linenorm.y, linenorm.x); 

		ares.points.emplace_back(a.rev_d0(b.d0(t2 - diff_angle)));
		bres.points.emplace_back(t2 - diff_angle);
		ares.points.emplace_back(a.rev_d0(b.d0(t2 + diff_angle)));
		bres.points.emplace_back(t2 + diff_angle);
			
		gxx::println("два пересечения");
		return;
	}

	inline void intersect_line2_curve2(const line& a, const curve& b, curve_parts& ares, curve_parts& bres) {
		if (typeid(b) == typeid(line)) { intersect_line2_line2(a, static_cast<const line&>(b), ares, bres); return; }
		if (typeid(b) == typeid(circle)) { intersect_line2_circle2(a, static_cast<const circle&>(b), ares, bres); return; }
		gxx::panic("undefined curve");
	}

	inline std::pair<curve_parts, curve_parts> intersect_curve2_curve2(const curve& a, const curve& b) {
		std::pair<curve_parts, curve_parts> res;
		if (typeid(a) == typeid(line)) { intersect_line2_curve2(static_cast<const line&>(a), b, res.first, res.second); return res; }
		if (typeid(b) == typeid(line)) { intersect_line2_curve2(static_cast<const line&>(b), a, res.second, res.first); return res; }
		gxx::panic("undefined curve");
		return res;
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