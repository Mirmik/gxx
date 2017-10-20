#ifndef GXX_SLIST_H
#define GXX_SLIST_H

#include <gxx/datastruct/slist_head.h>
#include <gxx/util/member.h>

namespace gxx {

	template<typename type, slist_head type::* member>
	class slist {
		slist_head head;
	public:

		slist() { head.next = nullptr; }

		bool empty() {
			return head.next == nullptr;
		}

		void move_front(type& obj) {
			(obj.*member).next = head.next;
			head.next = &(obj.*member);
		}

		class iterator {
		public:
			//using iterator_category = std::bidirectional_iterator_tag;
			using value_type = type;
			using difference_type = ptrdiff_t;
			using pointer = type*;
			using reference = type&;

		public:
			slist_head* current;
		public:
			iterator() : current(nullptr) {};	
			iterator(slist_head* head) : current(head) {};	
			iterator(const iterator& other) : current(other.current) {};		
					
			iterator operator++(int) { iterator i = *this; current=current->next; return i; }
			iterator operator++() { current=current->next; return *this; }
			bool operator!= (const iterator& b) {return current != b.current;}
			bool operator== (const iterator& b) {return current == b.current;}
					
			type& operator*() {return *member_container(current,member);}
			type* operator->() {return member_container(current,member);}
		};

		iterator begin() { return iterator(head.next); }
		iterator end() { return iterator(nullptr); }	
	};
}

#endif