#ifndef GXX_CHECKER_H
#define GXX_CHECKER_H

namespace gxx {
	namespace checker {
		template <typename Predicate>
		class predicate_falling_edge {
		public:
			Predicate pred;
			bool phase = 0;

			predicate_falling_edge(Predicate&& pred) : pred(pred) {}

			bool check() {
				bool ans = pred();
				switch (phase) {
					case 0:
						if (ans == true) phase = 1;
						return false;
					case 1:
						if (ans == false) {
							phase = 2;
							return true;
						}
						return false;
					case 2:
						return true;
				} 
			}
		};

		template <typename Predicate>
		predicate_falling_edge<Predicate> falling_edge(Predicate&& pred) {
			return predicate_falling_edge<Predicate>(std::forward<Predicate>(pred));
		}
	}
}

#endif