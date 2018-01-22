#ifndef GXX_RABBIT_DRAW_H
#define GXX_RABBIT_DRAW_H

#include <gxx/x11wrap/shower2d.h>
#include <gxx/rabbit/topo2.h>

namespace rabbit {
	void draw(gxx::drawer2d& d, const loop2& l) {
		for(const auto& t : l.edges) {
			d.add_line(t.start(), t.finish());
		}
	}
}

#endif