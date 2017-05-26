#include <iostream>
#include <gxx/arglist.h>

using namespace gxx::literals;

struct generic {
	template<typename T> static int genfunc(T* ptr, int i);
};

template<> int generic::genfunc<int>(int* ptr, int i) {
	printf("INT %d %d\n", *ptr, i);
}

template<> int generic::genfunc<gxx::object_buffer<const char>>(gxx::object_buffer<const char>* ptr, int i) {
	printf("ARR %s %d\n", ptr->data(), i);
}

template<typename ... T>
struct helper {
	static int func(gxx::argument<T>&& ... args) {
		auto list = gxx::make_arglist<generic> (gxx::move(args) ...);
		list.invoke(0, 0);
		list.invoke(1, 1);
		list.invoke(2, 2);
		list.invoke(3, 3);
	}
};

template<typename ... T>
int func(T&& ... args) {
	return helper<T ...>::func(gxx::forward<T>(args) ...);
}

int main() {

	func(4,6,"lalal", "kekeke"_a=89);

//	std::cout << "HelloWorld" << std::endl;

}