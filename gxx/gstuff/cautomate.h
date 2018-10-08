#ifndef GXX_GSTUFF_CAUTOMATE_H
#define GXX_GSTUFF_CAUTOMATE_H

#include <sys/cdefs.h>

struct gstuff_automate {
	struct sline line;
	uint8_t crc;
	uint8_t state;
	void(*callback)(void*,char*,int);
	void* callback_argument;
};

__BEGIN_DECLS

static inline void
__gstuff_automate_reset(struct gstuff_automate * autom) {
	autom->crc = 0xff;
	sline_reset(&autom->line);
}

static inline void
gstuff_automate_reset(struct gstuff_automate * autom) {
	__gstuff_automate_reset(autom);
	autom->state = 0;
}

static inline void
gstuff_automate_init(struct gstuff_automate * autom, void * buf, int len, 
	void(*callback)(char*,int), void * arg
) {
	sline_init(&autom->line, buf, len);
	gstuff_automate_reset();
	autom->callback = callback;
	autom->callback_argument = arg;
}

static inline void 
gstuff_automate_newchar(struct gstuff_automate * autom, char c) {
	switch (state) {
		/*case 0:
			if (c == gxx::gmsg::strt) {
				//Похоже на символ начала пакета.
				__gstuff_automate_reset(autom);
				autom->state = 1;
			}
			break;*/
		case 1:
			switch (c) 
			{
				case gxx::gmsg::strt:
					//Приняли стартовый символ.
					if (autom->line->len == 0) //< Повторный стартовый. Ничего не делаем.
						break;
					
					if (crc != 0) 
					{
						//Принят символ окончания пакета, но crc не пройден. 
						//dprln("packager::crc_error:", crc);
					}
					else {
						//gxx::println("callback");
						invoke_callback();
					}
					__gstuff_automate_reset(autom);
					break;
				case gxx::gmsg::stub:
					autom->state = 2;
					break;
				default:
					sline_putchar(&autom->line, c);
					strmcrc8(&autom->crc, c);
			}
			break;

		case 2:
			switch (c) {
				case gxx::gmsg::stub_strt:
					sline_putchar(&autom->line, GSTUFF_START);
					strmcrc8(&autom->crc, GSTUFF_START);
					state = 1;
					break;
				case gxx::gmsg::stub_stub:
					sline_putchar(&autom->line, GSTUFF_STUB);
					strmcrc8(&autom->crc, GSTUFF_STUB);
					state = 1;
					break;
				default:
					__gstuff_automate_reset(autom);
					state = 0;
			}				
			break;

	}
}


__END_DECLS

#endif