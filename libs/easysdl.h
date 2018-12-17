#ifndef MY_LIBS_EASYSDL_H
#define MY_LIBS_EASYSDL_H

#include <stdlib.h>
#include <easysdl.h>
#include "geometry.h"
#include "color.h"

void Point_draw(const Point p, Color c);
void Poly_stroke(const Poly p, Color c);

#define strokePoint(x, y, c) EZ_trace_point((unsigned int)x, (unsigned int)y, c.r, c.g, c.b, c.a)
#define strokeLine(x1, y1, x2, y2, c) EZ_trace_segment((unsigned int)x1, (unsigned int)y1, (unsigned int)x2, (unsigned int)y2, c.r, c.g, c.b, c.a)

#endif
