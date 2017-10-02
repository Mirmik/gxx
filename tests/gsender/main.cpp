#include <gxx/debug/dprint.h>
#include <gxx/format.h>

namespace fmt = gxx::fmt;

#include <gxx/msg/gsender.h>
#include <gxx/debug/debug_ostream.h>

#include <gxx/buffer.h>
#include <gxx/vecbuf.h>

#include <gxx/io/ring_stream.h>



int main() {
	gxx::debug_ostream dostream;
	dostream.hexmode(true);

	gxx::io::ring_stream ring(gxx::allocate_buffer(128));
	gxx::msg::gmsgproto::sender smsg(&ring);

	ring.dump(dostream);

	gxx::vecbuf buffs;

	const char* str0 = "HelloWorld";
	const char* str1 = "HelloWorld2";	

	buffs.emplace_back(str0);
	buffs.emplace_back(str1);


	smsg.send(buffs);

	ring.dump(dostream);
}