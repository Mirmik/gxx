#ifndef GXX_RPC_BINCALL_H
#define GXX_RPC_BINCALL_H

#include <gxx/event/delegate.h>
#include <gxx/serialize/serialize.h>
#include <gxx/result.h>
#include <gxx/print.h>

namespace gxx {
	namespace rpc {
		enum class status : uint8_t {
			OK,
			WrongArgsFormat,
			WrongArgsData,
			InternalError,
		};

		/*class error : public gxx::result_type::exception {
		public:
			gxx::rpc::status status; 

			const char* what() {
				return "error";
			}
		};*/

		template <typename T>
		using rpcresult = gxx::result_type::result<T, status>;

		template<typename Ret, typename ... Args>
		struct bincaller_invoke { 
			static status impl(gxx::archive::binary_writer& writer, gxx::delegate<Ret, Args ...>& dlg, Args& ... args) {
				Ret ret = dlg(args ...);
				if (ret.is_error()) {
					return ret.getError();
				}
				gxx::serialize(writer, ret.getData());
				return gxx::rpc::status::OK;
			}
		};

		class bincaller_basic {
		public:
			virtual status invoke(gxx::archive::binary_reader& reader, gxx::archive::binary_writer& writer) = 0;
		};

		/*template <typename R>
		class bincaller : public bincaller_basic {
			gxx::delegate<R, T0> dlg;		
		public:
			bincaller(gxx::delegate<R, T0> dlg) : dlg(dlg) {}
			void invoke(gxx::archive::binary_reader& keeper, gxx::buffer answer) override {
				bincaller_invoke_impl(dlg);
			}
		};

		template <typename R, typename T0>
		class bincaller : public bincaller_basic {
			gxx::delegate<R, T0> dlg;		
		public:
			bincaller(gxx::delegate<R, T0> dlg) : dlg(dlg) {}
			void invoke(gxx::archive::binary_reader& keeper, gxx::buffer answer) override {
				T0 arg0;
				keeper.load(arg0);
				bincaller_invoke_impl(dlg, arg0);
			}
		};*/

		template <typename R, typename T0, typename T1>
		class bincaller : public bincaller_basic {
			gxx::delegate<rpcresult<R>, T0, T1> dlg;		
		public:
			bincaller(gxx::delegate<rpcresult<R>, T0, T1> dlg) : dlg(dlg) {}
			status invoke(gxx::archive::binary_reader& keeper, gxx::archive::binary_writer& writer) override {
				T0 arg0;
				T1 arg1;
				gxx::deserialize(keeper, arg0);
				gxx::deserialize(keeper, arg1);
				if (keeper.iserror() && keeper.avail()) return status::WrongArgsFormat;
				return bincaller_invoke<rpcresult<R>, T0, T1>::impl(writer, dlg, arg0, arg1);
			}
		};

		template <typename Ret, typename ... Args>
		bincaller<Ret, Args...> make_bincaller(gxx::delegate<rpcresult<Ret>, Args ...> dlg) {
			return bincaller<Ret, Args...>(dlg);
		}
	}

	template<> 
	struct print_functions<gxx::rpc::status> {
		static int print(gxx::io::ostream& o, const gxx::rpc::status& sts) {
			const char * str;
			switch(sts) {
				case gxx::rpc::status::OK: 				str = "OK"; break;
				case gxx::rpc::status::WrongArgsFormat: 	str = "WrongArgsFormat"; break;
				case gxx::rpc::status::WrongArgsData: 	str = "WrongArgsData"; break;
				case gxx::rpc::status::InternalError: 	str = "InternalError"; break;
			}
			return gxx::print(o, str);
		}
	};
}

#endif