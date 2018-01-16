#ifndef GXX_RPC_STATUS_H
#define GXX_RPC_STATUS_H

#include <gxx/result.h>
#include <gxx/serialize/serialize.h>

namespace gxx {
	namespace rpc {
		enum class status : uint8_t {
			OK,
			WrongArgsFormat,
			WrongArgsData,
			InternalError,
		};

		template <typename T>
		using result = gxx::result_type::result<T, status>;
	}

	template<typename Archive> 
	struct serialize_helper<Archive, rpc::status> {
		static void serialize(Archive& keeper, const rpc::status& sts) {
			gxx::serialize(keeper, (const uint8_t&) sts);
		}
	
		static void deserialize(Archive& keeper, rpc::status& sts) {
			gxx::deserialize(keeper, (uint8_t&) sts);	
		}
	};

}

#endif