#ifndef GXX_RING_H
#define GXX_RING_H

#include <memory>
#include <gxx/panic.h>

//Implementation of abstract ring buffer

namespace gxx {
	template <typename T, typename Alloc = std::allocator<T>>
	class ring {
		int head;
		int tail;
		bool isfull;

		T* buffer;
		size_t reserved;

		Alloc alloc;

	public:
		ring() : head(0), tail(0), isfull(false), buffer(nullptr), reserved(0) {}

		void init() {
			head = 0;
			tail = 0;
			isfull = false;
		}

		bool empty() {
			return head == tail && !isfull;
		}

		void reserve(size_t sz) {
			T* newbuffer = alloc.allocate(sz);

			if (empty()) {
				buffer = newbuffer;
				reserved = sz;
				head = 0;
				tail = 0;
				isfull = false;
			}
			else {
				gxx::panic("NeedToImplement");
			}
		}
		
		T& front() {
			return *(buffer + tail);
		}

		T& back() {
			return *(buffer + (head - 1) % reserved);
		}

		void push(const T& obj) {
			alloc.construct(buffer + head++, obj);
			if (head == reserved) head = 0;
			if (head == tail) isfull = true; 
		}

		void pop() {
			if (!empty()) {
				if (++tail == reserved) tail = 0;
				isfull = false;
			}
		}
	};
}

#endif