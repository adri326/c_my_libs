#ifndef MY_LIBS_COLOR_H
#define MY_LIBS_COLOR_H

struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

typedef struct Color Color;

Color Color_new(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a);

Color Color_blend(const Color a, const Color b, const double value);

#define Color_unwrap(c) (c).r, (c).g, (c).b, (c).a

#endif
