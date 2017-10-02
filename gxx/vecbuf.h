#ifndef GXX_VECBUF_H
#define GXX_VECBUF_H

#include <vector>
#include <gxx/io/ostream.h>
#include <gxx/buffer.h>

namespace gxx {
	using vecbuf = std::vector<gxx::buffer>;

	void dump(const vecbuf& vec, gxx::io::ostream& out) {
		for (auto& v : vec) {
			out.print(v);
		}
	}
}

#endif