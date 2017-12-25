#ifndef GXX_GEOM2_H
#define GXX_GEOM2_H

#include <gxx/geom/geom2.h>

namespace gxx { namespace curve2 {
	using namespace geom2;

	class curve {
	public:
		virtual point d0(double t) = 0;
		virtual bool is_closed() { return false; }
		virtual bool is_periodic() { return false; }
		virtual double tmin() { return 0; }
		virtual double tmax() { return 0; }
	};

	class line : public curve {
	public:
		point l;
		direction d;

		geom2::point d0(double t) override {
			return point(l.x + d.x * t, l.y + d.y * t);
		}
		double tmin() override { return - geom2::infinity; }
		double tmax() override { return   geom2::infinity; }
	};

	class line_segment : public curve {
	public:
		point l1;
		point l2;

		geom2::point d0(double t) override {
			return point(l1.scale(1-t).add(l2.scale(t)));
		}
		double tmax() override { return 1; }
	};
}}

#endif