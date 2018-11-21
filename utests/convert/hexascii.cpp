#include <gtest/gtest.h>
#include <gxx/util/hexascii.h>
#include <gxx/buffer.h>

TEST(hexascii, hexascii_8) {
	char buf[2];
	uint8_t u8 = 0xAB;

	uint8_to_hex(buf, u8);
	EXPECT_EQ(gxx::buffer(buf), "AB");

	uint8_t restore = hex_to_uint8(buf);
	EXPECT_EQ(restore, u8);			
}

TEST(hexascii, hexascii_16) {
	char buf[4];
	uint16_t u16 = 0xABCD;

	uint16_to_hex(buf, u16);
	EXPECT_EQ(gxx::buffer(buf), "ABCD");

	uint16_t restore = hex_to_uint16(buf);
	EXPECT_EQ(restore, u16);			
}

TEST(hexascii, hexascii_32) {
	char buf[8];
	uint32_t u32 = 0xABCDEF01;

	uint32_to_hex(buf, u32);
	EXPECT_EQ(gxx::buffer(buf), "ABCDEF01");

	uint32_t restore = hex_to_uint32(buf);
	EXPECT_EQ(restore, u32);			
}

TEST(hexascii, hexascii_64) {
	char buf[16];
	uint64_t u64 = 0xABCDEF01ABCDEF01;

	uint64_to_hex(buf, u64);
	EXPECT_EQ(gxx::buffer(buf), "ABCDEF01ABCDEF01");

	uint64_t restore = hex_to_uint64(buf);
	EXPECT_EQ(restore, u64);			
}
