#ifndef GXX_SLICE_H
#define GXX_SLICE_H

//#include <gxx/allocator.h>
#include <inttypes.h>
#include <stdlib.h>
#include <gxx/util/setget.h>

namespace gxx {
	template <typename T>
	class object_buffer {
	protected:
		T* m_data;
		size_t m_size;

	public:
		ACCESSOR(data, m_data);
		ACCESSOR(size, m_size);
		
		VALUE_GETTER(bytesize, m_size * sizeof(T));

		object_buffer() : m_data(nullptr), m_size(0) {};
		object_buffer(T* data, size_t size) : m_data(data), m_size(size) {}

		template<size_t N>
		object_buffer(const T (& data) [N]) : m_data((T*) data), m_size(N) {}

		using iterator = T*;

		iterator begin() {
			return m_data;
		}

		iterator end() {
			return m_data + m_size;
		}

		gxx::object_buffer<T> slice(){
			return gxx::object_buffer<T>(m_data, m_size);
		}

		gxx::object_buffer<T> slice(size_t len){
			return gxx::object_buffer<T>(m_data, len);
		}

		gxx::object_buffer<T> slice(size_t first, size_t len){
			return gxx::object_buffer<T>(m_data + first, len);
		}
	
		T& operator[](int i) {
			return *(m_data + i);
		}
	};

/*	template <typename T, typename Allocator = gxx::allocator<T>>
	class allocated_object_buffer : public object_buffer<T> {
		using Parent = object_buffer<T>;

		Allocator m_alloc;
	public:
		CONSTREF_GETTER(data, Parent::m_data);
		CONSTREF_GETTER(size, Parent::m_size);

		allocated_object_buffer(size_t n) : object_buffer<T>(m_alloc.allocate(n), n) {}

		~allocated_object_buffer() {
			m_alloc.deallocate(Parent::m_data);
		}
	};*/
}

#endif