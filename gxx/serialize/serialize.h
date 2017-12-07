#ifndef GXX__SERIALIZESERIALIZE_H
#define GXX__SERIALIZESERIALIZE_H

#include <gxx/util/stub.h>
#include <gxx/result.h>
#include <gxx/buffer.h>
#include <tuple>

namespace gxx {
	template <typename M, typename T> 
	struct serialize_helper {
		static void serialize(M& keeper, T& obj) {
			keeper.dump(obj);
		}
	
		static void deserialize(M& keeper, T& obj) {
			keeper.load(obj);
		}
	};

	template <typename M, typename T> inline void serialize(M& keeper, T& obj) {
		serialize_helper<M,T>::serialize(keeper, obj);
	}

	template <typename M, typename T> inline void deserialize(M& keeper, T& obj) {
		serialize_helper<M,T>::deserialize(keeper, obj);
	}

	template <typename M, typename T> inline void serialize(M& keeper, T&& obj) {
		serialize_helper<M,T>::serialize(keeper, obj);
	}

	template <typename M, typename T> inline void deserialize(M& keeper, T&& obj) {
		serialize_helper<M,T>::deserialize(keeper, obj);
	}

	namespace archive {
		class binary_writer {
			int _length = 0;
			gxx::buffer buf;
			char* ptr;

		public:
			binary_writer(gxx::buffer buf) : buf(buf), ptr(buf.data()) {}

			template<typename T>
			void operator& (T& obj) {
				dump(obj);
			}

			//Для избежания проблем с типизацией 
			//передавать перед int его длину. 
			void dump(int i) {
				memcpy(ptr, (char*)&i, sizeof(int));
				_length += sizeof(int);
				ptr += sizeof(int);
			} 

			void dump(const char* str, size_t size) {
				uint16_t sz = size;
				memcpy(ptr, (char*)&sz, sizeof(uint16_t));
				_length += sizeof(uint16_t);
				ptr += sizeof(uint16_t);
				memcpy(ptr, str, sz);
				_length += sz;
				ptr += sz;
			} 

			void dump(const char* str) {
				dump(str, strlen(str));
			} 

			void dump(gxx::buffer buf) {
				dump(buf.data(), buf.size());
			} 

			template<typename T>
			void dump(T& ref) {
				ref.reflect(*this);
			}

			CONSTREF_GETTER(length, _length);
		};

		class binary_reader {
			gxx::buffer buf;
			char* ptr;
			char* end;
			bool _iserror = false;

		public:
			binary_reader(gxx::buffer buf) : buf(buf), ptr(buf.data()), end(buf.data() + buf.size()) {}

			template<typename T>
			void operator& (T& obj) {
				load(obj);
			}

			void load(int& i) {
				if (_iserror || avail() < sizeof(int)) { _iserror = true; return; }
				memcpy((char*)&i, ptr, sizeof(int));
				ptr += sizeof(int);
			} 

			void load(long& i) {
				if (_iserror || avail() < sizeof(long)) { _iserror = true; return; }
				memcpy((char*)&i, ptr, sizeof(long));
				ptr += sizeof(long);
			} 

			void load(gxx::buffer& buf) {
				uint16_t sz;
				if (_iserror || avail() < sizeof(uint16_t)) { _iserror = true; return; }
				memcpy((char*)&sz, ptr, sizeof(uint16_t));
				ptr += sizeof(uint16_t);
				if (_iserror || avail() < sz) { _iserror = true; return; }
				buf.size(sz);
				buf.data(ptr);
				ptr += sz;
			} 

			template<typename T>
			void load(T& ref) {
				ref.reflect(*this);
			}

			template<typename T>
			T retload() {
				T ret; 
				gxx::deserialize(*this, ret);
				return ret;
			}

			bool iserror() {
				return _iserror;
			}

			int avail() {
				return end - ptr; 
			}

		};
	}

	/*template<typename M, typename T>
	struct serializer {
		static void serialize(M& keeper, const T& obj);
		static result<void> deserialize(M& keeper, T& obj);
	};

	template <typename M, typename T> void serialize(M& keeper, const T& obj) {
		serializer<M,T>::serialize(keeper, obj);
	}

	template <typename M, typename T> result<void> deserialize(M& keeper, T& obj) {
		return serializer<M,T>::deserialize(keeper, obj);
	}*/

	template<typename Archive, typename ... Args> 
	struct serialize_helper<Archive, std::tuple<Args...>> {
		using Tuple = std::tuple<Args...>;
		
		template<typename std::size_t ... I>
		static void tuple_serialize_helper(Archive& keeper, const Tuple& tpl, std::index_sequence<I...>) {
			int ___[] = {
				(gxx::serialize(keeper, std::get<I>(tpl)), 0) ...
			};
		}
	
		static void serialize(Archive& keeper, const Tuple& tpl) {
			tuple_serialize_helper(keeper, tpl, std::index_sequence_for<Args...>{});
		}
	
		template<typename std::size_t ... I>
		static void tuple_deserialize_helper(Archive& keeper, Tuple& tpl, std::index_sequence<I...>) {
			int ___[] = {
				(gxx::deserialize(keeper, std::get<I>(tpl)), 0) ...
			};
		}
	
		static void deserialize(Archive& keeper, Tuple& tpl) {
			tuple_deserialize_helper(keeper, tpl, std::index_sequence_for<Args...>{});
		}
	};

	template<typename Archive> 
	struct serialize_helper<Archive, std::string> {
		static void serialize(Archive& keeper, const std::string& str) {
			gxx::serialize(keeper, gxx::buffer::from_string(str));
		}
	
		static void deserialize(Archive& keeper, std::string& str) {
		}
	};
}

#endif
