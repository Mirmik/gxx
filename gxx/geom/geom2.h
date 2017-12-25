#ifndef GXX_GEOM_GEOM2_H
#define GXX_GEOM_GEOM2_H

#include <gxx/math/malgo2.h>
#include <limits>

namespace gxx { namespace geom2 {
	constexpr static double infinity = std::numeric_limits<double>::infinity();

	class point : public malgo2::vector2<double> {
	public: 
		point();
		point(double x, double y) : malgo2::vector2<double>(x,y) {}
		point(const point& oth) : malgo2::vector2<double>(oth) {}
		point(const malgo2::vector2<double>& oth) : malgo2::vector2<double>(oth) {}
	};

	class vector : public malgo2::vector2<double> {
	public:
		vector();
		vector(double x, double y) : malgo2::vector2<double>(x,y) {}
		vector(const vector& oth) : malgo2::vector2<double>(oth) {}
		vector(const malgo2::vector2<double>& oth) : malgo2::vector2<double>(oth) {}
	};

	class direction : public malgo2::vector2<double> {
	public:
		direction(){};
		direction(double x, double y, bool norm = true) : malgo2::vector2<double>(x,y) { if (norm) self_normalize(); }
		direction(const direction& oth) : malgo2::vector2<double>(oth) {}
		direction(const malgo2::vector2<double>& oth, bool norm = true) : malgo2::vector2<double>(oth) { if (norm) self_normalize(); }
	};

}}

#endif