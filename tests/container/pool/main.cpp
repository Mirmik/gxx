#include <gxx/print.h>
#include <gxx/container/pool.h>

int main() 
{
	char poolbuf[8 * 16];

	gxx::pool pool(poolbuf, 8 * 16, 16);

	GXX_PRINT(pool.size());
	GXX_PRINT(pool.element_size());

	GXX_PRINT(pool.avail());

	void* block = pool.get();

	GXX_PRINT(pool.avail());	
}