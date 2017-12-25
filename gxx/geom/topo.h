#ifndef GXX_GEOM_TOPO_H
#define GXX_GEOM_TOPO_H

#include <memory>
#include <vector>
#include <set>
#include <gxx/geom/curve2.h>
#include <gxx/geom/curve3.h>
#include <gxx/geom/surface3.h>

namespace gxx {
	namespace topo {
		//using namespace geom3;

		class surface {
			std::shared_ptr<gxx::surf3::surface> impl;
		public:
			template<typename Surface>
			surface(const Surface& surf) : impl(new Surface(surf)) {}
			surface() = default;
			size_t printTo(gxx::io::ostream& o) const { return gxx::print(*impl); }
		};

		class curve3 {
			std::shared_ptr<gxx::curve3::curve> impl;
		public:
			template<typename Curve>
			curve3(const Curve& crv) : impl(new Curve(crv)) {}
			curve3() = default;
			size_t printTo(gxx::io::ostream& o) const { return gxx::print(*impl); }
		};

		class curve2 {
			std::shared_ptr<gxx::curve2::curve> impl;
		public:
			template<typename Curve>
			curve2(const Curve& crv) : impl(new Curve(crv)) {}
			curve2() = default;
			size_t printTo(gxx::io::ostream& o) const { return gxx::print(*impl); }
		};

		class shape;
		class vertex;
		class edge;
		class wire;
		class face;
		class shell;
		class solid;

		class vertex_impl;
		class edge_impl;
		class wire_impl;
		class face_impl;
		class shell_impl;
		class solid_impl;

		class vertex {
		public:
			std::shared_ptr<vertex_impl> impl;

			vertex(vertex& oth) : impl(oth.impl) {}
			vertex(const vertex& oth) : impl(oth.impl) {}
			vertex(vertex&& oth) : impl(std::move(oth.impl)) {}

			template <typename ... Args>
			vertex(Args&& ... args) : impl(new vertex_impl(std::forward<Args>(args) ...)) {}
		
			bool is_same(const vertex& oth);

			const geom3::point& loc() const;
			size_t printTo(gxx::io::ostream& o) const;

			//vertex& operator=(const vertex& oth) {
			//	impl = oth.impl;
			//}

			void sew(vertex& oth);
			void add_sinew(edge_impl* edg);
		};

		class edge {
			std::shared_ptr<edge_impl> impl;
		public:
			bool reversed;
		
		public:
			const geom3::point& start() const;
			const geom3::point& finish() const;

			edge(edge& oth) : impl(oth.impl) {}
			edge(const edge& oth) : impl(oth.impl) {}
			edge(edge&& oth) : impl(std::move(oth.impl)) {}

			template <typename ... Args>
			edge(Args&& ... args) : impl(new edge_impl(std::forward<Args>(args) ...)) {}
		
			vertex& a_vertex();
			vertex& b_vertex();
			const vertex& a_vertex() const;
			const vertex& b_vertex() const;

			vertex& start_vertex();
			vertex& finish_vertex();

			//vertex first_vertex();
			//vertex last_vertex();	

			size_t printTo(gxx::io::ostream& o) const;
		};

		class wire {
			std::shared_ptr<wire_impl> impl;
		public:
			surface cycle_plane() const;
			bool reversed;

			template <typename ... Args>
			wire(Args&& ... args) : impl(new wire_impl(std::forward<Args>(args) ...)) {}
			wire(const std::initializer_list<edge>& lst);

			std::set<vertex_impl*> list_of_vertex();
		};

		class face {
			std::shared_ptr<face_impl> impl;
		public:
			//face(const wire& wr);

			template <typename ... Args>
			face(Args&& ... args) : impl(new face_impl(std::forward<Args>(args) ...)) {}
		};

		class shell {
			std::shared_ptr<shell_impl> impl;
		public:
		};

		class solid {
			std::shared_ptr<solid_impl> impl;
		public:
		};


		class vertex_impl {
		public:
			geom3::point pnt;
			std::set<edge_impl*> sinews;
			vertex_impl(const geom3::point& pnt) : pnt(pnt) {}

			const geom3::point& loc() const { return pnt; }
			void add_sinew(edge_impl* edg) { sinews.insert(edg); }

			size_t printTo(gxx::io::ostream& o) const;
		};

		class edge_impl {
		public:
			curve3 crv;
			double tmin3d, tmax3d;
			
			//Представления граничной кривой, в пространстве координат lface и rface.
			curve2 rcrv;
			curve2 lcrv;
			double tmin2dr, tmax2dr;
			double tmin2dl, tmax2dl;
			
			//Вершины, на которые опирается ребро. 
			vertex avtx;
			vertex bvtx;

			//Грани, премыкающие к ребру.
			face* rface;
			face* lface;

			edge_impl(gxx::geom3::point pnt1, gxx::geom3::point pnt2) : 
				crv(gxx::curve3::line(pnt1, pnt2)), avtx(pnt1), bvtx(pnt2) 
			{
				avtx.add_sinew(this);
				bvtx.add_sinew(this);
				tmin3d = 0;
				tmax3d = (pnt2 - pnt1).abs();
			}
		};

		class wire_impl {
		public:
			std::vector<edge> edges;
			bool closed;

			//Только для плоского цикла.
			surface cycle_plane() const {
				auto pnt1 = edges[0].start();
				auto pnt2 = edges[0].start();
				auto pnt3 = edges[1].finish();

				return surface(surf3::plane(geom3::axis2(pnt1, pnt2, pnt3)));
			}

			wire_impl(const std::initializer_list<edge>& lst) : edges(lst) {
				evaluate_edges_orientation();
				sew_edges();
			} 

			void evaluate_edges_orientation();
			void sew_edges();

			std::set<vertex_impl*> list_of_vertex();
		};

		class face_impl {
		public:
			surface surf;
			std::vector<wire> cycles;

			void evaluate_cycles_orientation();

			//face(surf3::surface* surf) : surf(surf) {}
			face_impl(const wire& wr) : surf(wr.cycle_plane()) {
				//cycles.push_back(wr);
			}
		};

		/*class shape {
		public:
		};

		class vertex : public shape {
		public:
			geom3::point pnt;
			std::vector<edge*> edgs;

			vertex(const geom3::point& pnt) : pnt(pnt) {}

			std::shared_ptr<vertex> copy() {
				return std::shared_ptr<vertex>(new vertex(pnt));
			}
		};

		class edge : public shape {
		public:
			//Трехмерная огранниченная кривая, на которой строится ребро.
			std::unique_ptr<curve3::curve> crv;
			double tmin3d, tmax3d;
			
			//Представления граничной кривой, в пространстве координат lface и rface.
			std::unique_ptr<curve2::curve> rcrv;
			std::unique_ptr<curve2::curve> lcrv;
			double tmin2dr, tmax2dr;
			double tmin2dl, tmax2dl;
			
			//Вершины, на которые опирается ребро. 
			std::shared_ptr<vertex> tvtx;
			std::shared_ptr<vertex> bvtx;

			//Грани, премыкающие к ребру.
			face* rface;
			face* lface;

			edge(std::shared_ptr<vertex> a, std::shared_ptr<vertex> b) : bvtx(a), tvtx(b) {
				crv.reset(new gxx::curve3::line(a->pnt, b->pnt));
				tmin3d = 0;
				tmax3d = a->pnt.distance(b->pnt);

				gxx::println("maked edge");
			} 

			geom3::point start() const {
				return crv->d0(tmin3d);
			} 

			geom3::point finish() const {
				return crv->d0(tmin3d);
			} 

			/*edge(vertex* a, vertex* b, curve3::curve* rv, double tmin, double tmax) {
				bvtx.reset(a);
				tvtx.reset(b);
				crv.reset(rv);
				tmin3d = tmin;
				tmax3d = tmax;
			}*/
		/*};

		class wire {
		public:
			std::vector<std::shared_ptr<edge>> edges;

			//Только для плоского цикла.
			gxx::surf3::plane* generate_plane() {
				auto pnt1 = edges[0]->start();
				auto pnt2 = edges[0]->start();
				auto pnt3 = edges[1]->finish();

				return new gxx::surf3::plane(geom3::axis2(pnt1, pnt2, pnt3));
			}
		};

		class face : public shape {
		public:
			std::unique_ptr<surf3::surface> surf;
			std::vector<std::shared_ptr<wire>> cycles;

			//face(surf3::surface* surf) : surf(surf) {}
			face(std::shared_ptr<wire> wr) {
				cycles.emplace_back(wr);
				surf.reset(wr->generate_plane());
			}
		};

		class shell : public shape {
		public:
			std::vector<std::shared_ptr<face>> faces;
		};

		class solid : public shape {
		public:
			shell shl;
		};

		class cube : public solid {
		public:
			cube(double a) {
//				geom3::point apnt = geom3::origin();
//				geom3::point bpnt = geom3::point(a,a,a);

				/*auto vtx0 = new vertex(geom3::point(0,0,0));
				auto vtx1 = new vertex(geom3::point(a,0,0));
				auto vtx2 = new vertex(geom3::point(a,a,0));
				auto vtx3 = new vertex(geom3::point(0,a,0));
				auto vtx4 = new vertex(geom3::point(0,0,a));
				auto vtx5 = new vertex(geom3::point(a,0,a));
				auto vtx6 = new vertex(geom3::point(a,a,a));
				auto vtx7 = new vertex(geom3::point(0,a,a));

				auto edg0 = new edge(vtx0, vtx1);
				auto edg1 = new edge(vtx1, vtx2);
				auto edg2 = new edge(vtx2, vtx3);
				auto edg3 = new edge(vtx3, vtx0);*/
				//auto edg4 = new edge(vtx1, vtx2);
				//auto edg5 = new edge(vtx1, vtx2);
				//auto edg6 = new edge(vtx1, vtx2);
				//auto edg7 = new edge(vtx1, vtx2);
				//auto edg8 = new edge(vtx1, vtx2);
				//auto edg9 = new edge(vtx1, vtx2);

				//gxx::surf3::plane pln1(geom3::axis2(apnt, geom3::direction(-1, 0, 0)));
				//gxx::surf3::plane pln2(geom3::axis2(apnt, geom3::direction( 0,-1, 0)));
				//gxx::surf3::plane pln3(geom3::axis2(apnt, geom3::direction( 0, 0,-1)));
				//gxx::surf3::plane pln4(geom3::axis2(bpnt, geom3::direction( 1, 0, 0)));
				//gxx::surf3::plane pln5(geom3::axis2(bpnt, geom3::direction( 0, 1, 0)));
				//gxx::surf3::plane pln6(geom3::axis2(bpnt, geom3::direction( 0, 0, 1)));

				//shl.faces.emplace_back(new face(new gxx::surf3::plane(geom3::axis2(apnt, geom3::direction(-1, 0, 0)))));
				//shl.faces.emplace_back(new face(new gxx::surf3::plane(geom3::axis2(bpnt, geom3::direction( 0, 1, 0)))));
				//shl.faces.emplace_back(new face(new gxx::surf3::plane(geom3::axis2(bpnt, geom3::direction( 1, 0, 0)))));
				//shl.faces.emplace_back(new face(new gxx::surf3::plane(geom3::axis2(apnt, geom3::direction( 0,-1, 0)))));
		/*	}
		};

		static std::shared_ptr<wire> multiline(std::vector<geom3::point> pnts, bool closed = false) {
			std::shared_ptr<wire> ret(new wire);

			std::vector<std::shared_ptr<vertex>> vtxs;
			for (const auto& p : pnts) {
				vtxs.emplace_back(new vertex(p));
			} 
			for (int i=0; i < vtxs.size() - 1; ++i) {
				ret->edges.emplace_back(new edge(vtxs[i], vtxs[i+1]));
			}
			if (closed) ret->edges.emplace_back(new edge(vtxs[vtxs.size()-1], vtxs[0]));

			return ret;
		}*/
	}
}

#endif