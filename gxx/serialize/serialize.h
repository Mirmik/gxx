#ifndef GXX__SERIALIZESERIALIZE_H
#define GXX__SERIALIZESERIALIZE_H

#include <gxx/util/stub.h>
#include <gxx/result.h>
#include <gxx/buffer.h>
#include <tuple>

namespace gxx {
	template <typename M, typename T, typename U = int>
	struct is_have_serialize : std::false_type { };

	template <typename M, typename T>
	struct is_have_serialize <M, T, decltype((void) &T::template serialize<M>, 0)> : std::true_type { };

	template <typename M, typename T, bool HaveSerialize = true> 
	struct serialize_helper_basic {
		static void serialize(M& keeper, const T& obj) {
			obj.serialize(keeper);
		}
	
		static void deserialize(M& keeper, T& obj) {
			obj.deserialize(keeper);
		}
	};

	template <typename M, typename T> 
	struct serialize_helper_basic<M,T,false> {
		static void serialize(M& keeper, const T& obj) {
			keeper.dump(obj);
		}
	
		static void deserialize(M& keeper, T& obj) {
			keeper.load(obj);
		}
	};

	template <typename M, typename T> 
	struct serialize_helper : public serialize_helper_basic<M,T,is_have_serialize<M,T>::value> {};

	template <typename M, typename T> inline void serialize(M& keeper, const T& obj) {
		serialize_helper<M,T>::serialize(keeper, obj);
	}

	template <typename M, typename T> inline void deserialize(M& keeper, T& obj) {
		serialize_helper<M,std::remove_cv_t<T>>::deserialize(keeper, obj);
	}

	template <typename M, typename T> inline void serialize(M& keeper, T&& obj) {
		serialize_helper<M,std::remove_cv_t<T>>::serialize(keeper, std::move(obj));
	}

	template <typename M, typename T> inline void deserialize(M& keeper, T&& obj) {
		serialize_helper<M,std::remove_cv_t<T>>::deserialize(keeper, std::move(obj));
	}

	namespace archive {

		template <typename T>
		struct data {
			T* ptr;
			size_t sz;
			data(T* ptr, size_t sz) : ptr(ptr), sz(sz) {}
			data(const T* ptr, size_t sz) : ptr((T*)ptr), sz(sz) {}
			template<typename R> void reflect(R& r) { r.dump_data((const char*)ptr, sz * sizeof(T)); }
		};

		/*template <typename T, typename S, typename A = std::allocator<T>>
		struct allocated_data {
			T*& ptr;
			S& sz;
			A alloc;			
			allocated_data(T*& ptr, S& sz, const A& alloc) : ptr(&ptr), sz(sz), alloc(alloc) {}
			
			template<typename R>
			void serialize(R& r) const {
				r.dump(sz);
				r.dump_data(ptr, sz * sizeof(T));
			}

			template<typename R>
			void deserialize(R& r) {
				r.load(sz);
				ptr = alloc.allocate(sz);
				r.dump_data(ptr, sz * sizeof(T));
			}
		};*/

		class writer_basic {


			//int _length = 0;
			//gxx::buffer buf;
			//char* ptr;

		public:
			//binary_writer(gxx::buffer buf) : buf(buf), ptr(buf.data()) {}

			template<typename T>
			void operator& (const T& obj) {
				gxx::serialize(*this, obj);
			}

			//Для избежания проблем с типизацией 
			//передавать перед int его длину. 
			/*void dump(int i) {
				memcpy(ptr, (char*)&i, sizeof(int));
				_length += sizeof(int);
				ptr += sizeof(int);
			} */
			virtual void dump(const char* dat, uint16_t sz) = 0;
			virtual void dump_data(const char* dat, uint16_t sz) = 0;
			
			/*void dump(const char* str) {
				dump(str, strlen(str));
			} 

			void dump(gxx::buffer buf) {
				dump(buf.data(), buf.size());
			} */

			void dump(unsigned char i) { dump_data((char*)&i, sizeof(i)); }
			void dump(unsigned long i) { dump_data((char*)&i, sizeof(i)); } 

			/*template<typename T>
			void dump(const gxx::archive::data<T> dat) {
				dump_data((char*)dat.ptr, dat.sz * sizeof(T));
			} 
*/
			template<typename T>
			void dump(const T& ref) {
				((std::remove_cv_t<std::remove_reference_t<T>>&)(ref)).reflect(*this);
			}

			//CONSTREF_GETTER(length, _length);
		};

		class binary_string_writer : public writer_basic {
		public:
			std::string str;

			void dump(const char* dat, uint16_t size) override {
				str.append((char*)&size, sizeof(uint16_t));
				str.append(dat, size);
				//memcpy(ptr, (char*)&sz, sizeof(uint16_t));
				//_length += sizeof(uint16_t);
				//ptr += sizeof(uint16_t);
				//memcpy(ptr, str, sz);
				//_length += sz;
				//ptr += sz;
			} 

			void dump_data(const char* dat, uint16_t size) override {
				str.append(dat, size);
			} 

			using writer_basic::dump;
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
			gxx::panic("todo");
		}
	};

	template<typename Archive, typename T> 
	struct serialize_helper<Archive, std::vector<T>> {
		static void serialize(Archive& keeper, const std::vector<T>& vec) {
			gxx::serialize(keeper, vec.size());
			gxx::serialize(keeper, gxx::archive::data<T>{vec.data(), vec.size()});
		}
	
		static void deserialize(Archive& keeper, std::vector<T>& vec) {
			gxx::panic("todo");
		}
	};
}

#endif
