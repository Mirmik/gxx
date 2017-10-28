#ifndef GXX_MEMORY_HEAP_H
#define GXX_MEMORY_HEAP_H

#include <gxx/print.h>
#include <gxx/slist.h>
#include <new>

namespace gxx {
	namespace memory {
		struct freenode {
			slist_head lnk;
			size_t sz;
			freenode(size_t sz) : sz(sz) {}
		};
		
		using freelist = gxx::slist<freenode, &freenode::lnk>;
			
		class memcontroller {
			//void* allocate
		};

		class heap {
		public:
			freelist fl;
			
			heap() {}
			heap(void* ptr, size_t sz) {
				engage_block(ptr, sz);
			}

			void engage_block(void* ptr, size_t sz) {
				fl.move_front(* new (ptr) freenode(sz));
			}

			inline void engage_block(gxx::buffer buf) {
				engage_block(buf.data(), buf.size());
			}


		};
	}

	template<>
	struct print_functions<memory::heap> {
		static int print(gxx::io::ostream& o, memory::heap const& heap) {
		//	return gxx::fprint("({},{})", &node, node.sz);			
			for(auto& node : heap.fl) {
				gxx::fprintln(o, "{}, {}", &node, node.sz);
			}
		}
	};
}

#endif