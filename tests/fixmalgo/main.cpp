#include <gxx/math/linalg.h>
#include <gxx/print.h>
#include <gxx/print/linalg.h>

using namespace linalg;

constexpr int f(int a, int b) { return a+b; }

int main() {
	//constexpr mat<double,2,2> m1 = {{
	//	{1,1}, {1,1}
	//}};

	constexpr vec<int,2> a {1,-2};
	constexpr vec<int,2> b {4,3};

	constexpr vec<int,2> c = linalg::abs(a);

	constexpr mat<int,2,2> m{a,b}; 
	//constexpr vec<int,2> m2 = zip(a, b, f); 
	//constexpr vec<int,2> m2 = zip(a, b, std::plus<int>());
	//constexpr vec<int,2> m2 = a + b;


	constexpr mat<int,2,2> m2 = m * m - m;

	constexpr mat<int,2,2> m3 = linalg::abs(m2);	

	gxx::println(linalg::mul(m2,m2));

	//constexpr mat<double,2,2> m {a,b};




}