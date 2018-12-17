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
  unsigned int x = (unsigned int)p->points[0]->coordinates[0];
  unsigned int y = (unsigned int)p->points[0]->coordinates[1];
  for (n = 1; n < p->n_points; n++) {
    strokeLine(x, y, p->points[n]->coordinates[0], p->points[n]->coordinates[1], c);
    x = p->points[n]->coordinates[0];
    y = p->points[n]->coordinates[1];
  }
  if (p->n_points > 0) {
    strokeLine(x, y, p->points[0]->coordinates[0], p->points[0]->coordinates[1], c);
  }
}
