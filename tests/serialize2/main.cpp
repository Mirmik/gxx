#include <iostream>
#include <gxx/serialize/trent.h>
#include <gxx/serialize/json.h>
#include <gxx/debug/dprint.h>

template <typename type> class reflection_invoker {};

template<typename type>
class vector3 {
public:
	type x, y, z;
	vector3() = default;
	vector3(type x, type y, type z) : x(x), y(y), z(z) {}
};

template <typename type> struct reflection_invoker<vector3<type>> { 
	template <typename operation> static void invoke(operation& op, vector3<type>& obj) { 
		return op(obj.x) && op(obj.y) && op(obj.z); 
	} 
};

struct trent_serializer {
	struct type_getter_operation {
		std::vector<int> vec;
		bool operator()(int&) { vec.push_back(1); return false; } 
		bool operator()(std::string&) { vec.push_back(2); return false; }

		template<typename T>
		bool operator()(T& obj) {
			return reflection_invoker<T>::invoke(*this, obj);
		}
	};

	template <typename Arg>
	static std::vector<int> get_types(Arg& arg) {
		type_getter_operation op;
		op(arg);
		return op.vec;
	}
};

int main() {
	vector3<int> vec(3,4,5);
	trent_serializer::get_types(vec);
}