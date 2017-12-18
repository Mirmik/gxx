#include <gxx/math/matrix.h>
/*space gxx { namespace math {

matrix_accessor::matrix_accessor(float* data, size_t columns, size_t rows) 
: data(data), n(columns), m(rows), fsize(n*m) {} 

void matrix_accessor::fill(float arg) {
	size_t fsize = n * m;
	float* start = data;
	float* finish = data + fsize;

	while(start != data) {
		*start++ = arg;
	}
}

matrix matrix_accessor::add(const matrix_accessor& oth) const {
	matrix ret(n,m);
	size_t fsize = n * m;
		
	float * a = data;;
	float * b = oth.data;
	float * c = ret.data;

	float * end = data + fsize;

	while(a != end) {
		*c++ = *a++ + *b++;
	}

	return std::move(ret);
}

matrix matrix_accessor::diagonal(gxx::object_buffer<float> buf) {
	size_t num = buf.size();
	matrix ret(num, num);
			
	float* dat = ret.data;
	int step = num + 1;
			
	for (int i = 0; i < num; ++i) {
		*dat = *dat++;
		dat += step; 
	}

	return std::move(ret);
}


matrix matrix_accessor::diagonal(std::initializer_list<float> lst) {
	size_t num = lst.size();
	matrix ret(num, num);
			
	float* dat = ret.data;
	int step = num + 1;
			
	auto it = lst.begin();
	for (int i = 0; i < num; ++i) {
		*dat = *it++;
		dat += step; 
	}

	return std::move(ret);			
}

matrix matrix_accessor::identity(size_t num) {
	matrix ret(num, num);
	
	float* dat = ret.data;
	int step = num + 1;
			
	for (int i = 0; i < num; ++i) {
		*dat = 1;
		dat += step; 
	}

	return std::move(ret);	
}

matrix matrix_accessor::random(size_t n, size_t m, float a, float b) {
	matrix ret(n, m);
		
	float* dat = ret.data;
	float* fin = ret.data + ret.fsize;

	for (; dat != fin; ++dat) {
		*dat = float_random(a,b);
	}

	return std::move(ret);	
}

size_t matrix_accessor::printTo(gxx::io::ostream& o) const {
	float* mat = data;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			o.print(*mat++); 
			o.putchar(' ');
		}	
		o.println();
	}
	return m * n;
}

void matrix_accessor::self_add_column(size_t i, const vector& vec) {
	assert(m == vec.size());
	auto it = vec.begin();
	for (auto& ref : column_accessor(i)) {
		ref += *it++;
	}
}

matrix_accessor matrix_accessor::slice(size_t cstrt, size_t csize, size_t rstrt, size_t rsize) {
	return matrix_accessor(data + cstrt + csize * n, csize, rsize);
}

matrix::matrix(size_t columns, size_t rows) 
: matrix_accessor(new float[columns*rows], columns, rows) {
	memset(data, 0, n*m*sizeof(float));
}

matrix::~matrix() { 
	delete[] data; 
}
	
}} // namespaces*/