#include "color.h"

Color Color_new(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
  Color c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;
  return c;
}

Color Color_blend(const Color a, const Color b, const double value) {
  return Color_new(
    a.r + (b.r - a.r) * value,
    a.g + (b.g - a.g) * value,
    a.b + (b.b - a.b) * value,
    a.a + (b.a - a.a) * value
  );
}
