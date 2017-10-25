#ifndef GXX_SERIALIZE_H
#define GXX_SERIALIZE_H

#include <gxx/util/stub.h>
#include <gxx/result.h>

namespace gxx {
	template<typename M, typename T>
	struct serializer {
		static void serialize(M& keeper, const T& obj);
		static result<void> deserialize(M& keeper, T& obj);
	};

	template <typename M, typename T> void serialize(M& keeper, const T& obj) {
		serializer<M,T>::serialize(keeper, obj);
	}

	template <typename M, typename T> result<void> deserialize(M& keeper, T& obj) {
		return serializer<M,T>::deserialize(keeper, obj);
	}

	template<typename ... Args> 
	struct serializer<gxx::trent, std::tuple<Args...>> {
		using Tuple = std::tuple<Args...>;
		
		template<typename std::size_t ... I>
		static void tuple_serialize_helper(std::vector<gxx::trent>& vec, const Tuple& tpl, std::index_sequence<I...>) {
			std::vector<gxx::trent> v { std::get<I>(tpl) ... };
			vec.swap(v);
		}
	
		static void serialize(gxx::trent& keeper, const std::tuple<Args ...>& tpl) {
			tuple_serialize_helper(keeper.as_vector(), tpl, std::index_sequence_for<Args...>{});
		}
	
		template<typename std::size_t ... I>
		static result<void> tuple_deserialize_helper(std::vector<gxx::trent>& vec, std::tuple<Args ...>& tpl, std::index_sequence<I...>) {
			return have_error(gxx::deserialize(vec[I], std::get<I>(tpl)) ...); 
		}
  	
		static result<void> deserialize(gxx::trent& keeper, Tuple& tpl) {
			return tuple_deserialize_helper(keeper.as_vector(), tpl, std::index_sequence_for<Args...>{});
		}
	};
}

#endif
