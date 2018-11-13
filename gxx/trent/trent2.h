#ifndef GXX_TRENT_H
#define GXX_TRENT_H

#include <memory>
#include <gxx/panic.h>
#include <gxx/container/dlist.h>


namespace gxx
{
	class trent
	{
		enum Type
		{
			Nil = 0x00,
			Bool = 0x01,
			Numer = 0x02,
			String = 0x03,
			Table = 0x10,
			List = 0x11,
			Dict = 0x12,
		};

		dlist_head lnk;
		uint8_t type;

		union internal_union
		{
			double num;
			std::string str;
			gxx::dlist<trent, &trent::lnk> tbl;

			internal_union() {}
			~internal_union() {}
		} data;

	public:
		trent() : type(Type::Nil)
		{}

		~trent()
		{
			invalidate();
		}

		void invalidate()
		{
			switch (type)
			{
				case Type::Nil:
				case Type::Numer:
				case Type::Bool:
					return;

				case List:
				case Dict:
				case Table:
				{
					while (!data.tbl.empty()) 
					{
						trent* ptr = data.tbl.first();
						ptr->invalidate();
						delete ptr;
					}
				}

				default:
					PANIC_TRACED();
			}
		}

		bool is_table() { return type & 0x10; }
		bool is_list() { return type == Type::List; }
		bool is_dict() { return type == Type::Dict; }

		trent& operator= (double num)
		{
			if (is_table()) 
				invalidate();

			type = Type::Numer;
			data.num = num;
			return *this;
		}


	};
}

#endif