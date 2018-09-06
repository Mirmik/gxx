#include <gxx/print.h>
#include <gxx/datastruct/pool/pool.h>
#include <gxx/datastruct/pool/paged_pool.h>

#include <gxx/print.h>

int main() {
	struct pool_head pool;
	pool_init(&pool, 16);

	void* ptr = malloc(32);
	pool_engage(&pool, ptr, 32);


	gxx::print_dump(ptr, 32);

	gxx::println(ptr);
	gxx::println();

	void* ptr2 = pool_alloc(&pool);


	gxx::println(pool_alloc(&pool));
	gxx::println(ptr2);
	
	pool_free(&pool, ptr2);
	gxx::println(pool_alloc(&pool));
	gxx::println(pool_alloc(&pool));
}