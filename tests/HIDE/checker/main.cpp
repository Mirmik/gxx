#include <gxx/print.h>
#include <gxx/checker.h>

int main() {

	gxx::checker::falling_edge([](){ return false; });
}