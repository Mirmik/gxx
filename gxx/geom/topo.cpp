#include <gxx/geom/topo.h>
#include <gxx/print/stdprint.h>
#include <gxx/geom/project.h>

namespace gxx {
	namespace topo {
		wire::wire(const std::initializer_list<edge>& lst) : impl(new wire_impl(lst)) {}
		//edge::edge(geom3::point pnt1, geom3::point pnt2) : impl(new edge_impl(pnt1, pnt2)) {}
	
		void wire_impl::evaluate_edges_orientation() {
			if (edges[0].a_vertex().is_same(edges[1].a_vertex())) { edges[0].reversed = true; edges[1].reversed = false; }
			else 
			if (edges[0].a_vertex().is_same(edges[1].b_vertex())) { edges[0].reversed = true; edges[1].reversed = true; }
			else 
			if (edges[0].b_vertex().is_same(edges[1].a_vertex())) { edges[0].reversed = false; edges[1].reversed = false; }
			else 
			if (edges[0].b_vertex().is_same(edges[1].b_vertex())) { edges[0].reversed = false; edges[1].reversed = true; }
			else {
				gxx::print(edges[0]);
				gxx::print(edges[1]);
				gxx::panic("evaluate_edges_orientation error");
			}

			for (int i = 2; i < edges.size(); ++i) {
				const geom3::point& last_pnt = edges[i-1].finish();

				if (edges[i].a_vertex().is_same(last_pnt)) { edges[i].reversed = false; }
				else
				if (edges[i].b_vertex().is_same(last_pnt)) { edges[i].reversed = true; }
				else {
					gxx::println(edges[i-1].start());
					gxx::println(last_pnt);
					gxx::println(edges[i]);
					gxx::panic("evaluate_edges_orientation error");
				}
			}
		} 

		void wire_impl::sew_edges() {
			for (int i = 0; i < edges.size() - 1; ++i) {
				edges[i].finish_vertex().sew(edges[i+1].start_vertex());
			}
			if (edges[edges.size() - 1].finish_vertex().is_same(edges[0].start_vertex())) {
				edges[edges.size() - 1].finish_vertex().sew(edges[0].start_vertex());
				closed = true;
			}
		}

		vertex& edge::a_vertex() { return impl->avtx; }
		vertex& edge::b_vertex() { return impl->bvtx; }
		const vertex& edge::a_vertex() const { return impl->avtx; }
		const vertex& edge::b_vertex() const { return impl->bvtx; }

		vertex& edge::start_vertex() {
			return reversed ? b_vertex() : a_vertex();
		}

		vertex& edge::finish_vertex() {
			return reversed ? a_vertex() : b_vertex();
		}

		const geom3::point& edge::start() const {
			return (reversed ? b_vertex() : a_vertex()).loc();
		}
		
		const geom3::point& edge::finish() const {
			return (reversed ? a_vertex() : b_vertex()).loc();
		}

		bool vertex::is_same(const vertex& oth) {
			return oth.impl->pnt.is_same(impl->pnt);
		}

		const geom3::point& vertex::loc() const { return impl->loc(); }

		size_t edge::printTo(gxx::io::ostream& o) const {
			return gxx::fprint("edge(a:{},b:{},crv:{}", a_vertex(), b_vertex(), impl->crv);
		} 

		size_t vertex::printTo(gxx::io::ostream& o) const {
			return gxx::fprint("vtx(l:{}", impl->loc());
		} 

		size_t vertex_impl::printTo(gxx::io::ostream& o) const {
			return gxx::fprint("vtx(l:{},s:{}", loc(), sinews);
		} 

		void vertex::sew(vertex& oth) {
			impl->sinews.insert(oth.impl->sinews.begin(), oth.impl->sinews.end());
			oth.impl = impl;
		}

		void vertex::add_sinew(edge_impl* edg) {
			impl->add_sinew(edg);
		}

		std::set<vertex_impl*> wire_impl::list_of_vertex() {
			std::set<vertex_impl*> ret;
			for (const auto& e : edges) {
				ret.insert(e.a_vertex().impl.get());
				ret.insert(e.b_vertex().impl.get());
			}
			return ret;
		}

		std::vector<edge>& wire::edges() {
			return impl->edges;
		}

		const std::vector<edge>& wire::edges() const {
			return impl->edges;
		}

		std::set<vertex_impl*> wire::list_of_vertex() {
			return impl->list_of_vertex(); 
		}

		surface wire::cycle_plane() const {
			return impl->cycle_plane();
		}

		/*bool wire::cycle_orientation() const {
			
		}

		void face_impl::evaluate_cycles_orientation() {
			//wire& fcycle = cycles[0];
			//bool forient = fcycle.cycle_orientation();
		}*/

		void face_impl::find_edges_projection() {
			for (auto& w : cycles) {
				for (auto& e : w.edges()) {
					e.project_to(surf);
				}
			}
		}

		void edge::project_to(const surface& surf) {
			crv2 = impl->crv.project_to(surf);
		}
	}
}

		