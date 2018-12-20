#include "easysdl.h"

void Point_draw(const Point p, Color c) {
  if (p->dimension != 2) {
    printf("Point_draw: point dimension should be equal to 2, p is %d\n", p->dimension);
    return;
  }
  strokePoint(p->coordinates[0], p->coordinates[1], c);
}

void Poly_stroke(const Poly p, Color c) {
  if (p->dimension != 2) {
    printf("Poly_stroke: poly dimension should be equal to 2, p is %d\n", p->dimension);
    return;
  }
  if (p->n_points == 0) {
    printf("Poly_stroke: poly has no point\n");
    return;
  }
  size_t n;
  double x = p->points[0]->coordinates[0];
  double y = p->points[0]->coordinates[1];
  for (n = 1; n < p->n_points; n++) {
    strokeLine(x, y, p->points[n]->coordinates[0], p->points[n]->coordinates[1], c);
    x = p->points[n]->coordinates[0];
    y = p->points[n]->coordinates[1];
  }
  if (p->n_points > 2) {
    strokeLine(x, y, p->points[0]->coordinates[0], p->points[0]->coordinates[1], c);
  }
}

void setEZSDLScale(double newScale) {
  easysdlScale = newScale;
}

void setEZSDLOffset(double x, double y) {
  easysdlOffsetX = x;
  easysdlOffsetY = y;
}

void centerEZSDLOffset(double width, double height) {
  easysdlOffsetX = width / easysdlScale / 2;
  easysdlOffsetY = height / easysdlScale / 2;
}

double getEZMouseX() {
  return (double)EZ_souris_x() / easysdlScale - easysdlOffsetX;
}

double getEZMouseY() {
  return -((double)EZ_souris_y() / easysdlScale - easysdlOffsetY);
}

bool easysdlHasExited() {
  return easysdlExited;
}

bool fetchEvents(void (*handler)(int)) {
  int evt = 0;
  bool res = false;
  while (EZ_recupere_evenement_continu(&evt)) {
    res = true;
    if (evt == EZ_EXIT) {
      easysdlExited = true;
    }
    (*handler)(evt);
  }
  return res;
}

void waitExit() {
  bool loop = true;
  while (loop) {
    EZ_attendre(20);
    int evt;
    while (EZ_recupere_evenement_continu(&evt)) {
      if (evt == EZ_EXIT) loop = false;
    }
  }
}
