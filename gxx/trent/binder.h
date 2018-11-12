#ifndef GXX_TRENT_BINDER_H
#define GXX_TRENT_BINDER_H

#include <gxx/trent/trent.h>

namespace gxx 
{
	template <typename T> 
	struct trent_binder_ops {
		T from_trent(const gxx::trent& tr);
		void set_trent(gxx::trent& tr, const T& val);
	};

	template <> 
	struct trent_binder_ops<int32_t> {
		int32_t from_trent(const gxx::trent& tr) { return tr.as_integer(); }
		void set_trent(gxx::trent& tr, const int32_t& val) { tr = val; }
	};

	template < typename T, typename Saver >
	class trent_binder : public trent_binder_ops<T>
	{
		Saver saver;
		trent_binder_ops<T> ops;	

		T _local;

	public:
		template <typename ... Args>
		trent_binder(Args && ... args) : saver(std::forward<Args>(args) ...) 
		{
			saver.sync();
			_local = ops.from_trent(saver.node());
		}
	
		void update(const T& val) 
		{
			_local = val;
			ops.set_trent(saver.node(), _local);
			saver.save();
		}		

		T get() 
		{
			return _local;
		}
	};	
}

#endif