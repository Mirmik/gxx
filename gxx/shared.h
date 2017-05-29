#include <gxx/utility.h>
#include <inttypes.h> 

namespace gxx {

	template<typename T>
	class default_deleter {
	public:
		void operator()(T* ptr) { delete ptr; }
	};

	class shared_control_block_basic {
	public:
		uint16_t refs;

		void addref() { refs++; }
		void remref() { 
			refs--; 
			if (refs == 0) destroy();
		}

		virtual void destroy() = 0;
	};

	template <typename T, typename Deleter>
	class shared_control_block : public shared_control_block_basic, public Deleter {
		shared_control_block(){}

		void destroy() {

		}
	};

	template <typename T>
	class shared_ptr {	
		T* ptr;
		shared_control_block_basic* ctrl;

	public:
			explicit shared_ptr(T* p) : ptr(p), ctrl(new shared_control_block<T, default_deleter<T>>()) {
				ctrl->addref();
			}

			~shared_ptr() {
				if (ptr) ctrl->remref();
			}
		/*
			shared_ptr(pointer p, delete_fn d) : ptr(p), cnt( new counter(1) ), del(d) {
					gxx::cout << "shared_ptr(pointer, delete_fn)\n";
			}
	
			shared_ptr(const shared_ptr &x) : shared_ptr(x.ptr, x.del) {
					cnt = x.cnt;
					++*cnt;
					gxx::cout << "shared_ptr(const shared_ptr&)\n";
			}
	
			shared_ptr(shared_ptr &&x)
					: ptr( gxx::move(x.ptr) ),
					  cnt( gxx::move(x.cnt) ),
					  del( gxx::move(x.del) )
			{
					gxx::cout << "shared_ptr(shared_ptr&&)\n";
					x.ptr = nullptr;
					x.cnt = nullptr;
			}
	
			shared_ptr& operator = (const shared_ptr &x)
			{
					gxx::cout << "shared_ptr::operator=&\n";
					if (this != &x) {
							reset();
							ptr = x.ptr;
							cnt = x.cnt;
							del = x.del;
							++*cnt;
					}
					return *this;
			}
	
			shared_ptr& operator = (shared_ptr &&x)
			{
					gxx::cout << "shared_ptr::operator=&&\n";
					shared_ptr::swap(x);
					return *this;
			}
	
			void swap(shared_ptr &x)
			{
					gxx::cout << "shared_ptr::swap(shared_ptr&)\n";
					gxx::swap(ptr, x.ptr);
					gxx::swap(cnt, x.cnt);
					gxx::swap(del, x.del);
			}
	
			~shared_ptr()
			{
					gxx::cout << "~shared_ptr::~shared_ptr()\n";
					if (cnt != nullptr && --*cnt == 0) {
							gxx::cout << " destroyed " << *ptr << "\n";
							del(ptr);
							delete cnt;
					}
			}
	
			pointer operator -> () const noexcept
			{
					return ptr;
			}
	
			reference operator * () const noexcept
			{
					return *ptr;
			}
	
			pointer get() const noexcept
			{
					return ptr;
			}
	
			explicit operator bool() const noexcept
			{
					return ptr != nullptr;
			}
	
			bool unique() const noexcept
			{
					return use_count() == 1;
			}
	
			counter use_count() const noexcept
			{
					return cnt != nullptr ? *cnt : 0;
			}
	
			void reset()
			{
					this->~shared_ptr();
					ptr = nullptr;
					cnt = nullptr;
			}
	
			void reset(pointer p)
			{
					reset();
					cnt = new counter(1);
					ptr = p;
			}
	
			void reset(pointer p, delete_fn d)
			{
					reset();
					cnt = new counter(1);
					ptr = p;
					del = d;
			}*/
	};
	
	template <class T, class... Args>
	shared_ptr<T> make_shared(Args&& ...args) {
			//return shared_ptr<T>( new T( gxx::forward<Args>(args)... ) );
	}
}