#include <gtest/gtest.h>
#include <gxx/container/pool.h>

TEST(Container, pool) {
	
	char poolbuf[8 * 16];
	gxx::pool pool(poolbuf, 8 * 16, 16);
	
	EXPECT_EQ(pool.size(), 8);
	EXPECT_EQ(pool.element_size(), 16);
	
	EXPECT_EQ(pool.avail(), 8);

	void* block0 = pool.get();
	EXPECT_EQ(pool.avail(), 7);

	void* block1 = pool.get();
	EXPECT_EQ(pool.avail(), 6);
	EXPECT_EQ((uintptr_t)block0 - 16, (uintptr_t)block1);

	void* block2 = pool.get();
	EXPECT_EQ(pool.avail(), 5);
	EXPECT_EQ((uintptr_t)block0 - 16 * 2, (uintptr_t)block2);

	void* block3 = pool.get();
	EXPECT_EQ(pool.avail(), 4);
	EXPECT_EQ((uintptr_t)block0 - 16 * 3, (uintptr_t)block3);

	void* block4 = pool.get();
	EXPECT_EQ(pool.avail(), 3);
	EXPECT_EQ((uintptr_t)block0 - 16 * 4, (uintptr_t)block4);

	void* block5 = pool.get();
	EXPECT_EQ(pool.avail(), 2);
	EXPECT_EQ((uintptr_t)block0 - 16 * 5, (uintptr_t)block5);

	void* block6 = pool.get();
	EXPECT_EQ(pool.avail(), 1);
	EXPECT_EQ((uintptr_t)block0 - 16 * 6, (uintptr_t)block6);

	void* block7 = pool.get();
	EXPECT_EQ(pool.avail(), 0);
	EXPECT_EQ((uintptr_t)block0 - 16 * 7, (uintptr_t)block7);

	void* block8 = pool.get();
	EXPECT_EQ(pool.avail(), 0);
	EXPECT_EQ(block8, nullptr);

	pool.put(block6);
	EXPECT_EQ(pool.avail(), 1);	

	pool.put(block1);
	EXPECT_EQ(pool.avail(), 2);
}
