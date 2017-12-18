#ifndef GXX_SURFACE_H
#define GXX_SURFACE_H

namespace gxx {
	namespace surf3 {
		using namespace geom3;

		class surface {
			virtual point d0(double v, double u) = 0; 
		};

		class bounded_surface : public surface {
		public:
			double vmin, vmax, umin, umax;	
			bool vcls, vper, ucls, uper;
			bounded_surface(double vmin, double vmax, double umin, double umax, bool vcls, bool vper, bool ucls, bool uper) 
				: vmin(vmin), vmax(vmax), umin(umin), umax(umax), vcls(vcls), vper(vper), ucls(ucls), uper(uper) {}
		};

		class cylinder : public bounded_surface {
		public:
			double r;
			double h;
			axis3 ax3;

			cylinder(double r, double h, const axis3& ax3) : r(r), h(h), ax3(ax3), 
				bounded_surface(0, 2*M_PI, 0, 1, true, true, false, false) {}

			point d0(double v, double u) {
				double c = r * cos(v);
				double s = r * sin(v);
				double w = h * u;
				return point(
					ax3.l.x + ax3.dx.x * c + ax3.dy.x * s + ax3.dz.x * w,
					ax3.l.y + ax3.dx.y * c + ax3.dy.y * s + ax3.dz.y * w,
					ax3.l.z + ax3.dx.z * c + ax3.dy.z * s + ax3.dz.z * w
				);
			}
		};

		class sphere : public bounded_surface {
		public:
			double r;
			axis3 ax3;

			sphere(double r, double h, const axis3& ax3) : r(r), ax3(ax3), 
				bounded_surface(0, 2*M_PI, -M_PI/2, M_PI/2, true, true, false, false) {}

			point d0(double v, double u) override {
				double a = r * cos(v) * cos(u);
				double b = r * sin(v) * cos(u);
				double c = r * sin(u);
				return point(
					ax3.l.x + ax3.dx.x * a + ax3.dy.x * b + ax3.dz.x * c,
					ax3.l.y + ax3.dx.y * a + ax3.dy.y * b + ax3.dz.y * c,
					ax3.l.z + ax3.dx.z * a + ax3.dy.z * b + ax3.dz.z * c
				);
			}
		};
	}
}

#endif