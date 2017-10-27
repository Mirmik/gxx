#ifndef GXX_GENERATOR_H
#define GXX_GENERATOR_H

namespace gxx {
	template<typename T, typename C>
	class generator {
		bool need_continue = true;

	public:
                using iterator = C&;
                using const_iterator = C&;

		void nil() { need_continue = false; }

		C& operator++() {
			need_continue = ((C*)this)->next();
			return *(C*)this;
		}

		decltype(auto) operator* () {
			return ((C*)this)->value();
		} 	

		C& begin() const {
			return *(C*)this; 
		}
	
		C& end() const {
			return *(C*)this;
		}

		bool operator != (generator& et) {
			return need_continue;
		}

		bool operator == (generator& et) {
			return !need_continue;
		}

                decltype(auto) vector() {
                    std::vector<typename C::value_type> vec;
                    for (const auto& t: *this) vec.emplace_back(t);
                    return vec;
                }
	};
}

namespace std {
	template<typename T, typename C>
	class iterator_traits<gxx::generator<T,C>> {
	public:
		using iterator_category = std::forward_iterator_tag;
        using value_type = T;
	};
}

#endif
