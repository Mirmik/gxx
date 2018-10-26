#ifndef UTIL_MACRO_H
#define UTIL_MACRO_H

//Макросы препроцессора.

//compat names
//#define STRINGIFY(x) __MACRO_STRING(x)
//#define CAT(x,y) __MACRO_CONCATE(x,y)

//Раскрытие
#define MACRO_EXPAND(m) m

//Косвенное превращение в строку
#define MACRO_STRING(...) __MACRO_STRING(__VA_ARGS__)
#define __MACRO_STRING(...) # __VA_ARGS__
#define STRINGIFY(...) #__VA_ARGS__
#define STRINGIFY2(...) STRINGIFY(__VA_ARGS__)

//Косвенная конкатенация. Интересно, в чем разница???
#define MACRO_CONCAT(m1, m2) __MACRO_CONCATE(m1,m2)
#define __MACRO_CONCATE(m1, m2) m1##m2
#define CONCAT(a,b) a##b
#define CONCAT2(a,b) CONCAT(a,b)
#define CONCAT3(a,b) CONCAT2(a,b)

//Вызов функции
#define MACRO_INVOKE(m, ...) m(__VA_ARGS__)

//Вызов функции-члена
#define MACRO_MEMBER_INVOKE(o, m, ...) o.m(__VA_ARGS__)

//Уникализация имени добавления "_at_line_[LINE]".
#define MACRO_GUARD(symbol) __MACRO_GUARD(symbol)
#define __MACRO_GUARD(symbol) MACRO_CONCAT(symbol ## _at_line_, __LINE__)

//Короткий синоним для MACRO_GUARD
#define __mgrd(symbol) MACRO_GUARD(symbol)

#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGS(...) ELEVENTH_ARGUMENT(_, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

//#define COUNT_ARGS2(...) ((int)(sizeof((int[]){ __VA_ARGS__ })/sizeof(int)))

#define ARGS_INVOKE_FOR_EACH_9(I,a,b,c,d,e,f,g,h)   I(a);I(b);I(c);I(d);I(e);I(f);I(g);I(h);
#define ARGS_INVOKE_FOR_EACH_8(I,a,b,c,d,e,f,g)     I(a);I(b);I(c);I(d);I(e);I(f);I(g);
#define ARGS_INVOKE_FOR_EACH_7(I,a,b,c,d,e,f)       I(a);I(b);I(c);I(d);I(e);I(f);
#define ARGS_INVOKE_FOR_EACH_6(I,a,b,c,d,e)         I(a);I(b);I(c);I(d);I(e);
#define ARGS_INVOKE_FOR_EACH_5(I,a,b,c,d)           I(a);I(b);I(c);I(d);
#define ARGS_INVOKE_FOR_EACH_4(I,a,b,c)             I(a);I(b);I(c);
#define ARGS_INVOKE_FOR_EACH_3(I,a,b)               I(a);I(b);
#define ARGS_INVOKE_FOR_EACH_2(I,a)                 I(a)

#define ARGS_INVOKE_FOR_EACH(...) CONCAT2(ARGS_INVOKE_FOR_EACH_,COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)

#endif