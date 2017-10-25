#include <iostream>
#include <gxx/serialize/trent.h>
#include <gxx/serialize/json.h>
#include <gxx/serialize/serialize.h>
#include <gxx/debug/dprint.h>

template<typename type>
class vector3 {
public:
	type x, y, z;
	vector3() = default;
	vector3(type x, type y, type z) : x(x), y(y), z(z) {}

	//void serialize(gxx::trent& keeper) const;
	//bool deserialize(gxx::trent& keeper);
};

namespace gxx {
	template<typename T> 
	struct serializer<gxx::trent, vector3<T>> {
		static void serialize(gxx::trent& keeper, const vector3<T>& v) {
			auto& internal = keeper.as_vector();
			internal.resize(3);
			internal[0] = v.x;
			internal[1] = v.y;
			internal[2] = v.z;
		}
	};	
	/*template<typename T> 
	bool serializer<gxx::trent, vector3<T>>::deserialize(gxx::trent& keeper, vector3<T>& v) {
		auto& internal = keeper.as_vector();
		v.x = internal[0].as_integer();
		v.y = internal[1].as_integer();
		v.z = internal[2].as_integer();
	}*/
}

template <typename type> class reflection_invoker<vector3<type>> { 
	template <typename operation> void invoke(operation& op, vector3& obj) { 
		op(obj.x); op(obj.y); op(obj.z); 
	} 
};

//template<typename T>
//vector3<T> vector3<T>::deserialize(gxx::trent& keeper) {
//	return vector3<T>(keeper[0].as_integer(), keeper[1].as_integer(), keeper[2].as_integer());
//}

namespace gxx {
	template<>
	struct serializer<gxx::trent, int> {
		static void serialize(gxx::trent& keeper, const int& i) { keeper = i; }
		static result<void> deserialize(gxx::trent& keeper, int& i) { i = tryS(keeper.as_numer_critical()); return result<void>(); }
	};

	template<>
	struct serializer<gxx::trent, std::string> {
		static void serialize(gxx::trent& keeper, const std::string& i) { keeper = i; }
		static result<void> deserialize(gxx::trent& keeper, std::string& i) { i = keeper.as_string_critical().unwrap(); return result<void>(); }
	};
}

int main() {
	//std::string i = "fsadf";
	//vector3<int> i(32, 67, 45);
	auto i = std::make_tuple(33,33, "Lelala",28);
	gxx::trent keeper;

	gxx::serialize(keeper, i);
	gxx::json::pretty_print_to(keeper, std::cout);

	//vector3<int> s;
	std::tuple<int, int, std::string, int> s;
	tryP(gxx::deserialize(keeper, s), err, {
		dprln(err.what());
		exit(0);
	});
}