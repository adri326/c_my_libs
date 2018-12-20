#ifndef MY_LIBS_EASYSDL_H
#define MY_LIBS_EASYSDL_H

#include <stdlib.h>
#include <easysdl.h>
#include "geometry.h"
#include "color.h"

void Point_draw(const Point p, Color c);
void Poly_stroke(const Poly p, Color c);
void setEZSDLScale(double newScale);
void setEZSDLOffset(double x, double y);
void centerEZSDLOffset(double width, double height);

double getEZMouseX();
double getEZMouseY();

bool fetchEvents(void (*handler)(int));
bool easysdlHasExited();

void waitExit();

#define coord(x, y) (unsigned int)(easysdlScale * ((x) + easysdlOffsetX)), (unsigned int)(easysdlScale * (-(y) + easysdlOffsetY))
#define strokePoint(x, y, c) EZ_trace_point(coord(x, y), c.r, c.g, c.b, c.a)
#define strokeLine(x1, y1, x2, y2, c) EZ_trace_segment(coord(x1, y1), coord(x2, y2), c.r, c.g, c.b, c.a)

static double easysdlScale = 1.0;
static double easysdlOffsetX = 0.0;
static double easysdlOffsetY = 0.0;

static bool easysdlExited = false;

#endif
