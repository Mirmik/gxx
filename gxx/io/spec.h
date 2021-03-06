#ifndef GXX_IO_INTEGER_SPEC_H
#define GXX_IO_INTEGER_SPEC_H

#include <gxx/debug/dprint.h>

namespace gxx
{
	namespace io
	{
		enum class alignment 
		{
			left, right, center
		};

		enum class text_case 
		{
			upper, lower, none
		};

		struct basic_spec
		{
			alignment align = alignment::left;
			text_case tcase = text_case::none;
			int width = 0;
			char fill = ' ';
		};

		struct integer_spec : public basic_spec
		{
			integer_spec(gxx::buffer opts_)
			{
				char* opts = opts_.data();
				unsigned int it = 0;

				if (opts != nullptr)
				{
					while(it != opts_.size())
					{
						if (isdigit(opts[it]))
						{
							char* fin;
							width = atou32(opts + it, 10, &fin);
							it = fin - opts;
							continue;
						}

						switch (opts[it])
						{
							case '<':
								align = alignment::left; 
								break;

							case '>':
								align = alignment::right; 
								break;

							case '^':
								align = alignment::center; 
								break;

							case 'f':
								fill = opts[it+1]; it++; 
								break;

							//case 'X':
							//	spec.charCase(io::CharCase::Upper);

							//case 'x':
							//	spec.base(16);
							//	if ( spec.prefix() == io::Prefix::Need ) spec.prefix(io::Prefix::Hex);
							//	continue;

							//case 'p':
							//	spec.prefix(io::Prefix::Need);
						}

						it++;
					}
				}
			}
		};

		struct float_spec : public basic_spec
		{
			float_spec(gxx::buffer opts_)
			{
				char* opts = opts_.data();
				unsigned int it = 0;

				if (opts != nullptr)
				{
					while(it != opts_.size())
					{
						if (isdigit(opts[it]))
						{
							char* fin;
							width = atou32(opts + it, 10, &fin);
							it = fin - opts;
							continue;
						}

						switch (opts[it])
						{
							case '<':
								align = alignment::left; 
								break;

							case '>':
								align = alignment::right; 
								break;

							case '^':
								align = alignment::center; 
								break;

							case 'f':
								fill = opts[it+1]; it++; 
								break;

							//case 'X':
							//	spec.charCase(io::CharCase::Upper);

							//case 'x':
							//	spec.base(16);
							//	if ( spec.prefix() == io::Prefix::Need ) spec.prefix(io::Prefix::Hex);
							//	continue;

							//case 'p':
							//	spec.prefix(io::Prefix::Need);
						}

						it++;
					}
				}
			}
		};

		struct text_spec : public basic_spec
		{
			text_spec(gxx::buffer opts_)
			{
				char* opts = opts_.data();
				unsigned int it = 0;

				if (opts != nullptr)
				{
					while(it != opts_.size())
					{
						if (isdigit(opts[it]))
						{
							char* fin;
							width = atou32(opts + it, 10, &fin);
							it = fin - opts;
							continue;
						}

						switch (opts[it])
						{
							case '<':
								align = alignment::left; 
								break;

							case '>':
								align = alignment::right; 
								break;

							case '^':
								align = alignment::center; 
								break;

							case 'U':
								tcase = text_case::upper;
								break;

							case 'l':
								tcase = text_case::lower;
								break;

							case 'f':
								fill = opts[it+1]; it++; 
								break;

							//case 'f':
							//	spec.fill(*++opts); continue;

							//case 'X':
							//	spec.charCase(io::CharCase::Upper);

							//case 'x':
							//	spec.base(16);
							//	if ( spec.prefix() == io::Prefix::Need ) spec.prefix(io::Prefix::Hex);
							//	continue;

							//case 'p':
							//	spec.prefix(io::Prefix::Need);
						}

						it++;
					}
				}
			}
		};
	}
}

#endif