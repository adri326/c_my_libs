#ifndef MY_LIBS_EASYSDL_H
#define MY_LIBS_EASYSDL_H

#include <stdlib.h>
#include <easysdl.h>
#include "geometry.h"
#include "color.h"

#if defined(EASYSDL_VERSION_PATCH) && defined(EASYSDL_VERSION_MINOR) && defined(EASYSDL_VERSION_PATCH)
#else
#error "No EASYSDL_VERSION defined or it has been missdefined: EASYSDL_VERSION_MAJOR, EASYSDL_VERSION_MINOR and EASYSDL_VERSION_PATCH should be defined"
#endif

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

#define coordX(x) (int)(easysdlScale * ((x) + easysdlOffsetX))
#define coordY(y) (int)(easysdlScale * (-(y) + easysdlOffsetY))
#define coord(x, y) coordX(x), coordY(y)

#define uncoordX(x) ((double)(x) / easysdlScale - easysdlOffsetX)
#define uncoordY(y) -((double)(y) / easysdlScale - easysdlOffsetY)
#define uncoord(x, y) uncoordX(x), uncoordY(y)

#define strokePoint(x, y, c) EZ_trace_point(coord(x, y), c.r, c.g, c.b, c.a)
#define strokeLine(x1, y1, x2, y2, c) EZ_trace_segment(coord(x1, y1), coord(x2, y2), c.r, c.g, c.b, c.a)

static double easysdlScale = 1.0;
static double easysdlOffsetX = 0.0;
static double easysdlOffsetY = 0.0;

static bool easysdlExited = false;

#define KEY_ARROW 0x40000000
#define KEY_ARROW_UP (KEY_ARROW | 0x52)
#define KEY_ARROW_LEFT (KEY_ARROW | 0x50)
#define KEY_ARROW_RIGHT (KEY_ARROW | 0x4f)
#define KEY_ARROW_DOWN (KEY_ARROW | 0x51)
#define KEY_SHIFT (KEY_ARROW | 0xe1)

struct Keymap {
  size_t n_keys;
  int** raw;
  size_t* n_binds;
  bool** pressed;
};

typedef struct Keymap* Keymap;

// creates a new Keymap instance
Keymap Keymap_new();
// destroys a Keymap instance
void Keymap_destroy(Keymap km);
// adds a key entry to a Keymap instance and returns its indexs
int Keymap_addKey(Keymap km);
// binds a key ID to a key entry
void Keymap_bindKey(Keymap km, const int index, const int raw);
// unbinds a key ID to a key entry
void Keymap_unbindKey(Keymap km, const int index, const int raw);
// checks whether or a not a key entry has the `raw` key ID bound to it
bool Keymap_hasBoundKey(Keymap km, const int index, const int raw);
// propagates a key ID into a Keymap instance
void Keymap_update(Keymap km, const int key, const bool down);
// returns whether or not a key entry has any pressed key
bool Keymap_pressed(Keymap km, const int index);

#endif
