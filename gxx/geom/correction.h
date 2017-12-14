#ifndef GXX_COORDINATES_CORRECTION_TABLE_H
#define GXX_COORDINATES_CORRECTION_TABLE_H

#include <gxx/geom/ncurve.h>

namespace gxx {
	namespace ngeom {
		template <typename T>
		class single_axis_correction_table {
			math::vector<T> coords;
			math::matrix<T> table;
			uint8_t base_axis;

		public:
			single_axis_correction_table(	
				uint8_t dim,
				uint8_t base, 
				const math::vector<T>& corcoords,
				const std::vector<uint8_t>& numcoords,
				const math::matrix<T>& cormatrix
			) : base_axis(base), coords(corcoords), table(corcoords.size(), dim) {

				for (int i = 0; i < numcoords.size(); ++i) {
					auto ax = numcoords[i];
					
					//Копируем столбцы
					auto src = cormatrix.column(i);
					auto dst = table.column(ax);
					std::copy(src.begin(), src.end(), dst.begin());
				}

				//gxx::print(table);
			}
			

			multiline correction( const line& l ) {
				const auto& first_point = l.cfirst();
				const auto& last_point = l.csecond();
				float cstart = l.cfirst()[base_axis];
				float cstop = l.csecond()[base_axis];
				bool reversed = cstart > cstop;
	
				float low = reversed ? cstop : cstart;
				float high = reversed ? cstart : cstop;
		
				auto lower = std::lower_bound(coords.begin(), coords.end(), low);
				auto upper = std::upper_bound(coords.begin(), coords.end(), high);

				auto distance = std::distance(lower, upper);

				multiline ml(distance + 2, l.dim());
				matrix& mat = ml.raw;

				auto first_row = mat.row(0);
				auto last_row = mat.row(mat.size1() - 1);
				std::copy(first_point.begin(), first_point.end(), first_row.begin());
				std::copy(last_point.begin(), last_point.end(), last_row.begin());

				auto centermat = mat.proxy(1,0,distance,mat.size2());


				auto iline = l.to_infinity_line();
				//iline.evaluate_point(0, cstart[base_axis]);

				gxx::println(l);
				gxx::println(mat);
				gxx::println(centermat);

				return ml;
			}		
		};


		/*multiline single_axis_correction(
			const line& l, 
			int c,
			const single_axis_correction_table& cortable
		) {
			/*const auto& first_point = l.cfirst();
			const auto& last_point = l.csecond();

			gxx::println("HelloWorld");
			assert(corcoords.size() == cormatrix.size1());
			assert(coords.size() == cormatrix.size2());
			assert(corcoords.is_sorted());

			float cstart = l.cfirst()[c];
			float cstop = l.csecond()[c];
			bool reversed = cstart > cstop;

			float low = reversed ? cstop : cstart;
			float high = reversed ? cstart : cstop;

			dprln("low", low);
			dprln("high", high);
			dprln("reversed", reversed);
			gxx::println(corcoords);

			auto lower = std::lower_bound(corcoords.begin(), corcoords.end(), low);
			auto upper = std::upper_bound(corcoords.begin(), corcoords.end(), high);
			
			assert(lower != corcoords.end()); 
			assert(upper != corcoords.end()); 
			
			auto distance = std::distance(lower, upper);

			dprln("lower", *lower);
			dprln("upper", *upper);
			dprln("distance", distance);

			multiline ml(distance + 2, l.dim());
			matrix& mat = ml.raw;

			auto first_row = math::make_matrix_row(mat, 0);
			auto last_row = math::make_matrix_row(mat, mat.size1() - 1);
			std::copy(first_point.begin(), first_point.end(), first_row.begin());
			std::copy(last_point.begin(), last_point.end(), last_row.begin());
			


			gxx::print(mat);

			//auto it = ml.raw.begin1();*/

			//auto fr = cormatrix.const_row_accessor(2);
			//gxx::print(fr);
			//return ml;
		//}
	}
}

#endif