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
	//dprptr(ptr);dln();
	printf("ARR %s %d\n", ptr->data(), i);
}

/*template<typename ... T>
struct helper {
	static int func(gxx::argument<T>&& ... args) {
		//auto list = gxx::make_arglist<generic> (gxx::move(args) ...);
		//list.invoke(0, 0);
		//list.invoke(1, 1);
		//list.invoke(2, 2);
		//list.invoke(3, 3);
	}
};*/

int func_impl(const gxx::arglist<generic>& args) {
	args.invoke(0, 0);
	//args.invoke(1, 1);
	//args.invoke(2, 2);
	//args.invoke(3, 3);
}

template<typename ... T>
int func(T&& ... args) {
	return func_impl(gxx::make_arglist<generic>(args ...));
}

int main() {
	char msg[128] = "Hello";
	//func(4,6,"lalal", "kekeke"_a=89, "msg"_a=msg);
	func("hello");

//	std::cout << "HelloWorld" << std::endl;

}