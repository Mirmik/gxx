#ifndef GXX_MEMORY_WRITER_H
#define GXX_MEMORY_WRITER_H

#include <string.h>

namespace gxx {
	enum class CharCase {
		Upper,
		Default,
	};

	enum class Alignment {
		Default,
		Left,
		Right,
		Center,
	};

	class EmptySpec {
	public:
		Alignment align() { return Alignment::Default; } 
		CharCase charCase() { return CharCase::Default; }
		size_t width() { return 0; }
		char fill() { return ' '; }
	};

	class AlignSpec : public EmptySpec {
		Alignment _align; 
		char _fill;
	public:
		AlignSpec(Alignment align = Alignment::Default) : _align(align) {}
		Alignment align() { return _align; }
		char fill() { return _fill; }
		void set_align(Alignment align) { _align = align; }
		void set_fill(char fill) { _fill = fill; } 
	};

	class CharStrSpec : public AlignSpec {
		CharCase _ccase;
	public:
		CharStrSpec(Alignment align = Alignment::Default, CharCase ccase = CharCase::Default) : _ccase(ccase), AlignSpec(align) {}
		CharCase charCase() { return _ccase; }
		void set_charCase(CharCase ccase) { _ccase = ccase; }
	};

	class memory_writer {
	protected:
		char* m_data;
		char* m_data_end;
		char* m_cursor;

	public:
		memory_writer(char* data, size_t sz) : m_data(data), m_data_end(data + sz), m_cursor(data) {}

		void write_fill(char c, int n) {
			while(m_cursor != m_data_end && n--) {
				*m_cursor++ = c;
			}
		}

		template<typename Spec = EmptySpec>
		size_t write(const char*& str, const Spec& spec = EmptySpec()) {
			const char* sstr = str;

			size_t len = strlen(str);

			int prewidth = 0;
			int postwidth = 0;

			if (spec.width() > len) {
				size_t tofill = spec.width() - len;
				switch(spec.align()) {
					case Alignment::Default:
					case Alignment::Right: 	
						prewidth = tofill; 
						break;
					case Alignment::Left: 	
						postwidth = tofill; 
						break;
					case Alignment::Center: 
						prewidth = tofill / 2  + tofill % 2; 
						postwidth = tofill / 2; 
						break;
				}
			}

			if (prewidth) write_fill(spec.fill(), prewidth);

			while(m_cursor != m_data_end && *str != 0) {
				*m_cursor++ = *str++;
			}			

			if (postwidth) write_fill(spec.fill(), postwidth);

			return str - sstr; 
		}
/*
		size_t write(gxx::buffer buf, ) {
			const char* sstr = str;
			while(m_cursor != m_data_end && n--) {
				*m_cursor++ = *str++;
			}			
			return str - sstr; 
		}
*/
		size_t write(const char c) {
			if(m_cursor != m_data_end) {
				*m_cursor++ = c;
				return 1; 
			}
			else return 0; 
		}

		size_t size() const {
			return m_cursor - m_data;
		}
	};
}

#endif