#ifndef GXX_GENERATOR_H
#define GXX_GENERATOR_H

namespace gxx {
	template<typename T, typename C>
	class generator {
		bool need_continue = true;
		
	public:
		generator() {
			operator++();
		}

		C& operator++() {
			need_continue = ((C*)this)->next();
			return *(C*)this;
		}

		decltype(auto) operator* () {
			return ((C*)this)->value();
		} 	

		C& begin() {
			return *(C*)this; 
		}
	
		C& end() {
			return *(C*)this;
		}

		bool operator != (generator& et) {
			return need_continue;
		}
	};
}

#endif