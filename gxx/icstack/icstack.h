#ifndef GENOS_ICSTACK_H
#define GENOS_ICSTACK_H

namespace gxx {
	struct ic_field {
		void* data;
		size_t sz;
	}

	struct iccoder {
		gxx::vector<ic_field> vec;

		void add_field(void* data, size_t sz) {
			vec.emplace_back(data, sz);
		}

		ic_field* get_list() {
			vec.emplace_back(nullptr, 0);
			return vec.data();
		}
	}
}

#endif