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
			vertex(double a, double b) : vertex(g2::point(a,b)) {}
			vertex(const vertex& oth) : impl(oth.impl) {}
			vertex(vertex&& oth) : impl(std::move(oth.impl)) {}
			vertex& operator= (const vertex& oth) { impl = oth.impl; return *this; }
			g2::point loc() const { return impl->pnt; }
			void swap(vertex& oth) { std::swap(impl, oth.impl); }
		};

		//Сегмент объединен с реализацией, т.к. на сегмент может ссылаться только один контур.
		class segment {
		public:
			vertex v1, v2;
			std::shared_ptr<curve2> crv;
			bool reversed = false;

			//segment(const g2::line& l) : crv(new g2::line(l)), v1(l.start()), v2(l.finish()) {}
			segment(const vertex& v1, const vertex& v2) : v1(v1), v2(v2), crv(new g2::line(v1.loc(), v2.loc())) { check_critical(); }

			void check_critical() {
				if (v1.loc().is_not_same(crvstart()) || v2.loc().is_not_same(crvfinish())) {
					gxx::vprintln("v1.loc():", v1.loc());
					gxx::vprintln("v2.loc():", v2.loc());
					gxx::vprintln("crv->start():", reversed ? crv->finish() : crv->start());
					gxx::vprintln("crv->finish():", reversed ? crv->start() : crv->finish());
					gxx::panic("segment check failure");
				}
			}

			void reverse() {
				reversed = !reversed;
				v1.swap(v2);
			}

			g2::point crvstart() { return reversed ? crv->finish() : crv->start(); }
			g2::point crvfinish() { return reversed ? crv->start() : crv->finish(); }
			g2::point start() const { return v1.loc(); }
			g2::point finish() const { return v2.loc(); }
		};

		class contour {
		public:
			std::vector<segment> segs;
			bool reversed = false;
			bool closed = false;

			void orient_segments() {
				if (segs.size() == 1) return;
				auto f = segs[0].finish();
				if (f.is_not_same(segs[1].start()) && f.is_not_same(segs[1].finish())) segs[0].reverse();
				for (int i = 1; i < segs.size(); ++i) {
					if (segs[i].start().is_not_same(segs[i-1].finish())) segs[i].reverse();
					//if (segs[i].start().is_not_same(segs[i-1].finish())) gxx::panic("broken contour");
				}
				if (segs[segs.size()-1].finish().is_same(segs[0].start())) closed = true;
			}

			void sew_vertexs() {
				for (int i = 0; i < segs.size() - 1; ++i) {
					segs[i].v2 = segs[i+1].v1;
				}
				if (closed) segs[segs.size()-1].v2 = segs[0].v1;
			}

			void check_segment_connection_critical(const segment& s1, const segment& s2) const {
				if (s2.start().is_not_same(s1.finish())) {
					gxx::vprintln("s1.start():", s1.start());
					gxx::vprintln("s1.finish():", s1.finish());
					gxx::vprintln("s2.start():", s2.start());
					gxx::vprintln("s2.finish():", s2.finish());
					gxx::panic("contour conection error");
				}
			}

			void check_closed_critical() const {
				if (closed == false) gxx::panic("contour isn't closed");
			}

			void check_critical() {
				for (int i = 0; i < segs.size() - 1; ++i) {
					check_segment_connection_critical(segs[i], segs[i+1]);
				}
				if (closed) check_segment_connection_critical(segs[segs.size()-1], segs[0]);
				for (auto & s: segs) {
					s.check_critical();
				}
			}

			contour(const std::initializer_list<segment>& segs) : segs(segs) {
				orient_segments();
				check_critical();
				sew_vertexs();
				check_critical();
			}
		};

		class figure {
		public:
			std::vector<contour> conts;
			figure(const contour& cntr) : conts{cntr} {
				cntr.check_closed_critical();
			}			
		};
	}
}

#endif