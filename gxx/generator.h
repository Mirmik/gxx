#ifndef GXX_GENERATOR_H
#define GXX_GENERATOR_H

namespace gxx {
	template<typename T, typename C>
	class generator {
		bool need_continue = true;

	public:
		using iterator = generator<T,C>&;
		using const_iterator = generator<T,C>&;

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
	};
}

#endif