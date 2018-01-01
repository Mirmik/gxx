#ifndef GXX_X11_2D_SHOWER
#define GXX_X11_2D_SHOWER

#include <X11/Xlib.h>
#include <gxx/geom/geom2.h>

namespace gxx {
	class shower2d {
	public:
		std::vector<gxx::geom2::point> points;

		void add(gxx::geom2::point pnt) {
			points.push_back(pnt);
		}

		void exec() {
			Display *d;
			Window w;
			XEvent e;
			const char *msg = "Hello, World!";
			int s;

			//Соединиться с X сервером, если X сервер на удаленной машине
			//следует разрешить на машине, где запущен X Server 
			//удаленные соединения командой xhost+ (см. man xhost)
			
			if ((d = XOpenDisplay(getenv("DISPLAY"))) == NULL) {
				printf("Can't connect X server:%s\n", strerror(errno));
				exit(1);
			}

			s = XDefaultScreen(d);

			/* Создать окно */
			w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1, XWhitePixel(d, s), XBlackPixel(d, s));

			/* На какие события будем реагировать */
			XSelectInput(d, w, ExposureMask | KeyPressMask);

			//Вывести окно на экран
			XMapWindow(d, w);

			//Бесконечный цикл обработки событий
			while (1) {
				XNextEvent(d, &e);

				//Перерисовать окно */
				if (e.type == Expose) {
					XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
					XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, strlen(msg));
				}
				//При нажатии кнопки-выход
				if (e.type == KeyPress) {
					break;
				}
			}

			//Закрыть соединение с X сервером
			XCloseDisplay(d);

			return;
		}
	};
} 

#endif