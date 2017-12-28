#ifndef GXX_GEOM_TOPO2_H
#define GXX_GEOM_TOPO2_H

#include <gxx/geom/geom2.h>
#include <memory>

namespace gxx {
	namespace topo2 {
		namespace g2 = gxx::geom2;
		using curve2 = gxx::geom2::curve;

		class vertex_impl {
		public:
			g2::point pnt;
			vertex_impl(const g2::point& pnt) : pnt(pnt) {}
		};

		class vertex;
		class segment;
		class contour;
		class figure;

		class vertex {
		public:
			std::shared_ptr<vertex_impl> impl;
			vertex(const g2::point& pnt) : impl(new vertex_impl(pnt)) {}
			vertex(const vertex& oth) : impl(oth.impl) {}
			vertex(vertex&& oth) : impl(std::move(oth.impl)) {}
			g2::point loc() const { return impl->pnt; }
		};

		//Сегмент объединен с реализацией, т.к. на сегмент может ссылаться только один контур.
		class segment {
		public:
			vertex v1, v2;
			std::shared_ptr<curve2> crv;
			bool reversed;

			segment(const g2::line& l) : crv(new g2::line(l)), v1(l.start()), v2(l.finish()) {}
			segment(const vertex& v1, const vertex& v2) : v1(v1), v2(v2), crv(new g2::line(v1.loc(), v2.loc())) {}
		};

		class contour {
		public:
			std::vector<segment> segs;
			bool reversed;
			contour(const std::initializer_list<segment>& segs) : segs(segs) {}
		};

		class figure {
		public:
			std::vector<contour> conts;
			figure(const contour& cntr) : conts{cntr} {}			
		};
	}
}

#endif