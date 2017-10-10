#include <stdlib.h>
#include <iostream>

void* operator new[](size_t sz) {
	std::cout << sz << std::endl;
	return malloc(sz);
}

void operator delete[](void* ptr) {
	return free(ptr);
}

class A {
public:
	A() {
		std::cout << "A()" << std::endl; 
	}

	~A() {
		std::cout << "~A()" << std::endl; 
	}
};

int main() {
	A* ptr = new A[5];
}