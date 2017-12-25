#ifndef GXX_GEOM_TOPO_H
#define GXX_GEOM_TOPO_H

#include <memory>
#include <vector>
#include <gxx/geom/curve2.h>
#include <gxx/geom/curve3.h>
#include <gxx/geom/surface3.h>

namespace gxx {
	namespace topo {
		//using namespace geom3;

		class shape;
		class vertex;
		class edge;
		class wire;
		class face;
		class shell;
		class solid;

		class shape {
		public:
		};

		class vertex : public shape {
		public:
			geom3::point pnt;
			std::vector<edge*> edgs;

			vertex(const geom3::point& pnt) : pnt(pnt) {}
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

			/*edge(vertex* a, vertex* b, curve3::curve* rv, double tmin, double tmax) {
				bvtx.reset(a);
				tvtx.reset(b);
				crv.reset(rv);
				tmin3d = tmin;
				tmax3d = tmax;
			}*/
		};

		class wire {
		public:
			std::vector<std::shared_ptr<edge>> edges;
		};

		class face : public shape {
		public:
			std::unique_ptr<surf3::surface> surf;
			std::vector<std::vector<wire>> cycles;

			face(surf3::surface* surf) : surf(surf) {}
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
			}
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
		}
	}
}

#endif