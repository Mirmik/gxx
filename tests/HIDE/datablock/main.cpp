#include <gxx/serialize/datablock.h>
#include <gxx/io/stdstream.h>

int main() {
	std::string str;
	double arr[] = {33, 0.33, 444, 123123, 1};

	gxx::io::ostringstream out(str);
	gxx::send_datablock(out, std::begin(arr), std::end(arr));

	dpr_dump(str.data(), str.size());
}