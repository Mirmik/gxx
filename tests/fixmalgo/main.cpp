#include <gxx/math/linalg.h>
#include <gxx/print.h>

using namespace gxx::linalg;

int f(int a, int b) { return a+b; }

int main() {
	//constexpr mat<double,2,2> m1 = {{
	//	{1,1}, {1,1}
	//}};

	constexpr vec<int,2> a {1,2};
	constexpr vec<int,2> b {2,3};

	auto res = zip(a,b,f);

	gxx::print_dump(&res, sizeof(res));

	//constexpr mat<double,2,2> m {a,b};




}