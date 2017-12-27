#include <gxx/geom/geom3.h>

namespace gxx {
	namespace geom3 {

		curve2 plane::projection(const curve& crv) const {
			if (crv.gettype() == curve_enum::line) {
				const auto& ln = crv.as_line();
				point pnt = ln.loc();
				vector vec = ln.vec();
				return line2(ax2.project_point(pnt), ax2.project_vector(vec));
			}
		} 

	}
}