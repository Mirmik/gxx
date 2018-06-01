#include <gxx/chain.h>

gxx::chain::chain(gxx::object_buffer<chainfunc_t> functape, gxx::buffer argstape) {
	data = malloc(functape.size() * sizeof(chainfunc_t) + argstape.size());
	size = functape.size();
	memcpy(data, functape.data(), size * sizeof(chainfunc_t));
	memcpy((char*)data + size * sizeof(chainfunc_t), argstape.data(), argstape.size());
}

gxx::chain::~chain() {
	free(data);
}

int8_t gxx::chain::exec() {
	chainfunc_t* fptr = (chainfunc_t*) data;
	chainfunc_t* efptr = (chainfunc_t*) ((char*)data + size * sizeof(chainfunc_t));
	char* dptr = (char*)data + size * sizeof(chainfunc_t);
	int8_t sts = 0;

	while (fptr != efptr) {
		dptr = (char*)(*fptr)(dptr, &sts);
		if (sts) return sts;
		++fptr;
	}
}