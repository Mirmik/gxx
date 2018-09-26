#ifndef GXX_AUTOCONTOL_MEDIAN_H
#define GXX_AUTOCONTOL_MEDIAN_H

namespace filtering {

	template <typename T, size_t N>
	struct median {
		struct sortpair {
			T val;
			uint8_t num;
		};

		median() : position(0) {
			for (int i = 0; i < N; ++i) {
				arr[i].val = 0;
				arr[i].num = i;
			} 
		}

		void push_next(T val) {
			uint8_t start = cursor ? 0 : 1;
			uint8_t 	putnum = 0;
			//T 			roofval = arr[start].val;

			uint8_t popnum = arr[cursor].num;

			for (uint8_t i = start + 1; i < N; ++i) {
				if (i == cursor) 
					continue;

				if (arr[i].val > val && val < roofval) {
					roofnum = arr[i].num;
					roofval = arr[i].val;
				}
			}

			for (uint8_t i = start; i < N; ++i) {
				if (i == cursor) 
					continue;


			}

			//arr[i] = 

			//arr[cursor].val = val;
		}

		T get() {
			return arr[cur].val;
		}

		sortpair arr[N];
		uint8_t cursor;
		uint8_t position; 
	};

}

#endif