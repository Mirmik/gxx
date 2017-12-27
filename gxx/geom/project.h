#ifndef GXX_GEOM_PROJECT_H
#define GXX_GEOM_PROJECT_H

#include <gxx/geom/topo.h>
//#include <gxx/geom/curve3.h>

namespace gxx {
	namespace topo {
		/*inline curve2 project_line_to_plane(
			const gxx::curve3::line& l3, 
			const gxx::surf3::plane& pln, 
			double tmax
		) {
			const auto& ax2 = pln.pos();			
			gxx::geom2::vector vec = ax2.project_vector(l3.dir().scale(tmax));
			gxx::geom2::point pnt = ax2.project_point(l3.loc());

			return curve2(pnt, vec);
		}*/
	}
}

#endif