
#include <gxx/memory/heap.h>
#include <gxx/buffer.h>

#include <gxx/print/stdprint.h>

gxx::memory::heap heap;

int main() {
	gxx::buffer buf = gxx::allocate_buffer(500);

//	heap.engage_block(buf.slice(500,100));
//	heap.engage_block(buf.slice(300,100));
//	heap.engage_block(buf.slice(400,100));
//	heap.engage_block(buf.slice(  0,100));
//	heap.engage_block(buf.slice(100,100));

	std::vector<int, gxx::memory::heap::allocator<int>> vec{gxx::memory::heap::allocator<int>(heap)};

	vec.push_back(3);
	gxx::println(heap);
	vec.push_back(4);
	gxx::println(heap);
	vec.push_back(5);
	gxx::println(heap);
	vec.push_back(7);
	gxx::println(heap);
	vec.push_back(8);
	gxx::println(heap);
	vec.push_back(9);
	gxx::println(heap);
	vec.push_back(10);
	gxx::println(heap);

	gxx::println(vec);

	vec.~vector();
	gxx::println(heap);

}