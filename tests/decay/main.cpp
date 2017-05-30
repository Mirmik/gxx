#include <iostream>

#include <gxx/utility.h>

template< class T >
struct decay {
private:
    typedef typename gxx::remove_reference<T>::type U;
public:
    typedef typename gxx::conditional< 
        gxx::is_array<U>::value,
        typename gxx::remove_extent<U>::type*,
        typename gxx::conditional< 
            gxx::is_function<U>::value,
            typename gxx::add_pointer<U>::type,
            typename gxx::remove_cv<U>::type
        >::type
    >::type type;
};

int main() {
	decay<int>::type i;
}