#include <gxx/memory/heap.h>
#include <gxx/buffer.h>

gxx::memory::heap heap;

int main() {
	heap.engage_block(gxx::allocate_buffer(128));
	heap.engage_block(gxx::allocate_buffer(128));
	gxx::print(heap);
}