#ifndef GXX_MEMORY_WRITER_H
#define GXX_MEMORY_WRITER_H

#include <string.h>
#include <gxx/util/numconvert.h>

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

	enum class Prefix {
		No,
		Need,
		Bin,
		Oct,
		Hex,
	};

	class EmptySpec {
	public:
		Alignment align() const { return Alignment::Default; } 
		CharCase charCase() const { return CharCase::Default; }
		size_t width() const { return 0; }
		char fill() const { return ' '; }
		uint8_t base() const { return 10; }
	};

	class AlignSpec : public EmptySpec {
	protected:
		Alignment _align = Alignment::Default; 
		char _fill = ' ';
		size_t _width = 0;
	public:
		AlignSpec() {}
		Alignment align() const { return _align; }
		size_t width() const { return _width; }
		char fill() const { return _fill; }
		AlignSpec& align(Alignment align) { _align = align; ; return *this; }
		AlignSpec& fill(char fill) { _fill = fill; return *this; } 
		AlignSpec& width(size_t width) { _width = width; return *this; } 
	};

	class CharStrSpec : public AlignSpec {
	protected:
		CharCase _ccase = CharCase::Default;
	public:
		CharStrSpec() {}
		CharCase charCase() const { return _ccase; }
		CharStrSpec& charCase(CharCase ccase) { _ccase = ccase; return *this; }
		CharStrSpec& align(Alignment align) { _align = align; ; return *this; }
		CharStrSpec& fill(char fill) { _fill = fill; return *this; } 
		CharStrSpec& width(size_t width) { _width = width; return *this; } 
		using AlignSpec::align;
		using AlignSpec::width;
		using AlignSpec::fill; 
	};

	class IntegerSpec : public CharStrSpec {
	protected:
		Prefix _prefix = Prefix::No;
		uint8_t _base = 10;
	public:
		IntegerSpec() {}
		Prefix prefix() const { return _prefix; }
		uint8_t base() const { return _base; }
		IntegerSpec& prefix(Prefix prefix) { _prefix = prefix; return *this; }
		IntegerSpec& charCase(CharCase ccase) { _ccase = ccase; return *this; }
		IntegerSpec& align(Alignment align) { _align = align; ; return *this; }
		IntegerSpec& fill(char fill) { _fill = fill; return *this; } 
		IntegerSpec& width(size_t width) { _width = width; return *this; } 
		IntegerSpec& base(uint8_t base) { _base = base; return *this; } 
		using AlignSpec::align;
		using AlignSpec::width;
		using AlignSpec::fill; 
		using CharStrSpec::charCase; 
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
		size_t write(const char* str, size_t len, const Spec& spec = CharStrSpec()) {
			const char* sstr = str;

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

			switch (spec.charCase()) {
				case CharCase::Default:
					while(m_cursor != m_data_end && *str != 0) {
						*m_cursor++ = *str++;
					}			
					break;
				case CharCase::Upper:
					while(m_cursor != m_data_end && *str != 0) {
						*m_cursor++ = toupper(*str++);
					}			
					break;
			}

			if (postwidth) write_fill(spec.fill(), postwidth);

			return str - sstr; 
		}

		template<typename Spec = IntegerSpec>
		size_t write_int(int64_t num, const IntegerSpec& spec = IntegerSpec()) {
			char str[100];
			
			switch (spec.prefix()) {
				case Prefix::Bin: putchar('0'); putchar('b'); break;
				case Prefix::Hex: putchar('0'); putchar('x'); break;
				case Prefix::Oct: putchar('0'); break;
			}

			i64toa(num, str, spec.base()); 
			return write(str, strlen(str), spec);
		}		

		template<typename Spec = EmptySpec>
		size_t write(const char* str, const Spec& spec = EmptySpec()) {
			return write(str, strlen(str), spec);
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
		size_t putchar(const char c) {
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