#include <gxx/shared.h>
#include <gxx/debug/testclass.h>

#include <vector>

std::vector<gxx::shared_ptr<TestClass>> vec;

void func(gxx::shared_ptr<TestClass> ptr) {
	//gxx::shared_ptr<TestClass> ptr(new TestClass());
	auto ptr2 = ptr;

	ptr2->method(53);

	vec.emplace_back(ptr);

	dpr("refs:"); dprln(ptr.get_control_block()->refs);
}

int main() {
	auto ptr = gxx::make_shared<TestClass>("lala");
	func(ptr);
	dprln("end");


	ptr->method(52);
}