#include <gxx/math/linalg.h>
#include <gxx/print.h>
#include <gxx/print/linalg.h>

#include <gxx/math/geometric.h>

using namespace linalg;

constexpr int f(int a, int b) { return a+b; }

int main() {

	vec<float, 3> a(0,0,0);
	vec<float, 3> b(1,0,0);
	vec<float, 3> c(0,1,0);


	gxx::println(geometric::trinormal(a,b,c));
	gxx::println(geometric::plane_of(a,b,c));
	gxx::println(geometric::gradient(a,b,c,0.5,0.5,1));
}