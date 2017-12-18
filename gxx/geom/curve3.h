#ifndef GXX_GEOM_CURVE3_H
#define GXX_GEOM_CURVE3_H

#include <gxx/geom/geom3.h>
#include <math.h>

namespace gxx { namespace curve3 {
	using namespace gxx::geom3;

	class curve {
	public:
		virtual point d0(double t) = 0;
	};

	class infinity_line : public curve {
	public:
		point l;
		direction d;

		infinity_line(point l, direction d) : l(l), d(d) {}

		point d0(double t) override {
			return point(l.x + d.x * t, l.y + d.y * t, l.z + d.z * t);
		}
	};

	class bounded_curve : public curve {
	public:
		double tmin, tmax;
		bool tcls, tper;

		bounded_curve(double tmin, double tmax, bool tcls, bool tper) 
			: tmin(tmin), tmax(tmax), tcls(tcls), tper(tper) {} 
	};

	class circle : public bounded_curve {
	public:
		double r;
		axis2 ax2;

		circle(double r, const axis2& ax2) : r(r), ax2(ax2), bounded_curve(0, 2*M_PI, true, true) {}

		point d0(double t) override {
			auto& pl = ax2.l;
			auto& dx = ax2.dx;
			auto& dy = ax2.dy;
			double s = sin(t) * r;
			double c = cos(t) * r;
			return point(
				pl.x + c * dx.x + s * dy.x, 
				pl.y + c * dx.y + s * dy.y, 
				pl.z + c * dx.z + s * dy.z
			);
		}
	};

	class elipse : public bounded_curve {
	public:
		double xr;
		double yr;
		axis2 ax2;

		elipse(double xr, double yr, const axis2& ax2) : xr(xr), yr(yr), ax2(ax2), bounded_curve(0, 2*M_PI, true, true) {}

		point d0(double t) override {
			auto& pl = ax2.l;
			auto& dx = ax2.dx;
			auto& dy = ax2.dy;
			double s = sin(t) * yr;
			double c = cos(t) * xr;
			return point(
				pl.x + c * dx.x + s * dy.x, 
				pl.y + c * dx.y + s * dy.y, 
				pl.z + c * dx.z + s * dy.z
			);
		}
	};

	class line : public bounded_curve {
	public:
		point a;
		direction d;

		line(point pnt1, point pnt2) : a(pnt1), d(pnt2.sub(pnt1)), bounded_curve(0, 1, false, false) {}

		point d0(double t) override {
			return point(a.x + d.x * t, a.y + d.y * t, a.z + d.z * t);
		}
	};

}}

#endif