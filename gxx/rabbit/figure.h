#ifndef GXX_RABBIT_FIGURE_H
#define GXX_RABBIT_FIGURE_H

#include <gxx/rabbit/topo2.h>

namespace rabbit {
	namespace figure {
		loop2 rectangle(double x, double y) {
			rabbit::point pnts[] = {
				{0, 0},
				{x, 0},
				{x, y},
				{0, y},
			};

			return loop2 {
				rabbit::line2(pnts[0], pnts[1]),
				rabbit::line2(pnts[1], pnts[2]),
				rabbit::line2(pnts[2], pnts[3]),
				rabbit::line2(pnts[3], pnts[0]),
			};
		}
	}
} 

#endif