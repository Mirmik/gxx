#ifndef GXX_VECTOR_H
#define GXX_VECTOR_H

#include <gxx/utility.h>
#include <gxx/algorithm.h>
#include <gxx/allocator.h>

#include <gxx/util/setget.h>

namespace gxx {

	template<typename T, class Allocator = gxx::allocator<T>>
	class vector {
	public:
		using iterator = T*;
		using const_iterator = const T*;

	private:
		//resources
		T* m_data = nullptr;
		size_t m_capacity = 0;
		size_t m_size = 0;
	
		//generated
		Allocator m_alloc;

	public:
		CONSTREF_GETTER(data, m_data);
		CONSTREF_GETTER(size, m_size);
		CONSTREF_GETTER(capacity, m_capacity);

		vector(const Allocator& alloc = Allocator()) {}

		vector(const vector& other) : m_data(other.m_data), m_capacity(other.m_capacity), m_size(other.m_size) {
			m_data = m_alloc.allocate(m_size);
			//gxx::copy(other.m_data, other.m_data + other.m_size, m_data);
			for (auto ip = other.m_data, op = m_data; ip != other.m_data + other.m_size; ip++, op++) {
				gxx::constructor(op, *ip);
			}
		}
	
		~vector() {
			gxx::array_destructor(begin(),end());
			if (m_data) m_alloc.deallocate(m_data);
		}

		unsigned char reserve(size_t sz) {
			if (sz > m_capacity) return changeBuffer(sz);
			return 1;
		}

		iterator begin() { return m_data; }
		iterator end() { return m_data + m_size; }
		iterator rbegin() { return m_data + m_size - 1; }
		iterator rend() { return m_data - 1; }
	
		template <typename ... Args>
		void emplace_back(Args&& ... args) {
			reserve(m_size + 1);
			gxx::constructor(m_data + m_size, gxx::forward<Args>(args)...);
			m_size++; 
		}
	
		void push_back(const T& ref) {
			reserve(m_size + 1);
			gxx::constructor(m_data + m_size, ref);
			m_size++; 
		}

		iterator insert(const_iterator pos, const T& value) {
			//TODO insert optimization 
			size_t _pos = pos - m_data;

			reserve(m_size + 1);
			m_size++; 
			
			iterator first = m_data + _pos;
			iterator last = gxx::prev(end());
			gxx::move_backward(first, last, end());
			*first = value;
			
			return first;
		}

		iterator insert(int pos, const T& value) {
			return insert(m_data + pos, value);
		}

		iterator insert_sorted(T const& item) {
		    return insert(gxx::upper_bound(begin(), end(), item ), item);
		}
	
		T& operator[](size_t num) {
			reserve(num + 1);
			if (num >= m_size) m_size = num + 1;
			return *(m_data + num);
		}

		void resize(size_t n) {
			reserve(n);
			m_size = n;
		}

		void erase(iterator newend) {
			m_size = newend - m_data;
		}

	protected:
		unsigned char changeBuffer (size_t sz) {
			auto newbuf = m_alloc.allocate(sz);
			m_capacity = sz;
			if (m_data == nullptr) {
				m_data = newbuf;
				return 1;
			}
			
			auto ie = end();
			auto oe = newbuf + sz;

			for(auto ip = begin(), op = newbuf; op != oe && ip != ie; op++, ip++) {
				gxx::constructor(op, *ip);
			}

			gxx::array_destructor(begin(), end());
			auto oldbuf = m_data; 
			m_data = newbuf;
			m_alloc.deallocate(oldbuf);
			return 1;
		}
	};
};

#endif