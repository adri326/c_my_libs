#include "color.h"

Color Color_new(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
  Color c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;
  return c;
}
