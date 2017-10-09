#ifndef GXX_CHECKER_H
#define GXX_CHECKER_H

#include <stdint.h>
#include <gxx/debug/dprint.h>

namespace gxx {
	namespace checker {
		template <typename Predicate>
                class predicate_edge {
		public:
			Predicate pred;
                        uint8_t phase = 0;
                        bool level = false;

                        predicate_edge(Predicate&& pred, bool lvl) : pred(pred), level(lvl) {}

			bool check() {
				bool ans = pred();
                                dprln(ans);
				switch (phase) {
					case 0:
                                                if (ans != level) phase = 1;
						return false;
					case 1:
                                                if (ans == level) {
							phase = 2;
							return true;
						}
						return false;
					case 2:
						return true;
				} 
			}

                        bool isstart() {
                            return phase == 0 || phase == 2;
                        }
		};

		template <typename Predicate>
                static inline predicate_edge<Predicate> falling_edge(Predicate&& pred) {
                        return predicate_edge<Predicate>(std::forward<Predicate>(pred), false);
		}

                template <typename Predicate>
                static inline predicate_edge<Predicate> rising_edge(Predicate&& pred) {
                        return predicate_edge<Predicate>(std::forward<Predicate>(pred), true);
                }
	}
}

#endif