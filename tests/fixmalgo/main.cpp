#include <gxx/math/linalg.h>
#include <gxx/print.h>
#include <gxx/print/linalg.h>

using namespace gxx::linalg;

constexpr int f(int a, int b) { return a+b; }

int main() {
	//constexpr mat<double,2,2> m1 = {{
	//	{1,1}, {1,1}
	//}};

	constexpr vec<int,2> a {1,2};
	constexpr vec<int,2> b {4,3};

	constexpr mat<int,2,2> m{a,b}; 
	//constexpr vec<int,2> m2 = zip(a, b, f); 
	//constexpr vec<int,2> m2 = zip(a, b, std::plus<int>());
	//constexpr vec<int,2> m2 = a + b;


	constexpr auto m2 = (m * m - m) * mat<int,2,2>();

	gxx::println(m2);

	//constexpr mat<double,2,2> m {a,b};




}