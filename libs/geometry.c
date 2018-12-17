#include "geometry.h"

// Vector methods

Vector Vector_new(const size_t dimension, double* values) {
  Vector v = (Vector)malloc(sizeof(struct Vector));
  size_t n;
  v->dimension = dimension;
  v->values = (double*)malloc(sizeof(double) * dimension);
  for (n = 0; n < dimension; n++) {
    v->values[n] = values[n];
  }
}

Vector Vector_new2D(const double x, const double y) {
  Vector v = (Vector)malloc(sizeof(struct Vector));
  v->dimension = 2;
  v->values = (double*)malloc(sizeof(double) * 2);
  v->values[0] = x;
  v->values[1] = y;
  return v;
}

Vector Vector_new3D(const double x, const double y, const double z) {
  Vector v = (Vector)malloc(sizeof(struct Vector));
  v->dimension = 3;
  v->values = (double*)malloc(sizeof(double) * 3);
  v->values[0] = x;
  v->values[1] = y;
  v->values[2] = z;
  return v;
}

void Vector_destroy(Vector v) {
  free(v->values);
  free(v);
}

Vector Vector_copy(Vector v) {
  return Vector_new(v->dimension, v->values);
}

void Vector_print(Vector v) {
  size_t n;
  printf("(");
  for (n = 0; n < v->dimension; n++) {
    printf("%.0lf", n, v->values[n]);
    if (n != v->dimension - 1) printf("; ");
  }
  printf(")");
}

double Vector_dot_product(Vector a, Vector b) {
  if (a->dimension == b->dimension) {
    double res = 0;
    size_t n;
    for (n = 0; n < a->dimension; n++) {
      res += a->values[n] * b->values[n];
    }
    return res;
  }
  else {
    printf("Invalid vector dimension: A is %d and B is %d\n", a->dimension, b->dimension);
    return 0;
  }
}

double Vector_cross_product(Vector a, Vector b) {
  if (a->dimension == b->dimension) {
    double sum = 0;
    size_t n, o;
    for (n = 0; n < a->dimension; n++) {
      for (o = 0; o < b->dimension; o++) {
        if (n != o) {
          sum += a->values[n] * b->values[o];
        }
      }
    }
    return sum;
  }
  else {
    printf("Invalid vector dimension: A is %d and B is %d\n", a->dimension, b->dimension);
    return 0;
  }
}

bool Vector_collinear(Vector a, Vector b) {
  if (a->dimension == b->dimension && a->dimension > 1) {
    if (a->values[0] == 0) {
      size_t n;
      for (n = 1; n < a->dimension; n++) {
        if (a->values[n] != 0) {
          return false;
        }
      }
      return true;
    }
    if (b->values[0] == 0) {
      size_t n;
      for (n = 1; n < b->dimension; n++) {
        if (b->values[n] != 0) {
          return false;
        }
      }
      return true;
    }
    size_t n;
    double r = a->values[0] / b->values[0];
    for (n = 1; n < a->dimension; n++) {
      if (a->values[n] / b->values[n] != r) {
        return false;
      }
    }
    return true;
  }
  else {
    printf("Invalid vector dimension: A is %d and B is %d\n", a->dimension, b->dimension);
    return 0;
  }
}

bool Vector_orthogonal(Vector a, Vector b) {
  double p = Vector_dot_product(a, b);
  return p > -__DBL_EPSILON__ && p < __DBL_EPSILON__;
}

void Vector_rotate2D(Vector v, double theta) {
  if (v->dimension == 2) {
    double x = v->values[0];
    double y = v->values[1];
    double theta_cos = cos(theta);
    double theta_sin = sin(theta);
    v->values[0] = x * theta_cos - y * theta_sin;
    v->values[1] = y * theta_cos + x * theta_sin;
  }
  else {
    printf("Invalid vector dimension for Vector_rotate2D: vector is %d\n", v->dimension);
  }
}

// Point methods

Point Point_new(const size_t dimension, double* coordinates) {
  Point p = (Point)malloc(sizeof(struct Point));
  size_t n;
  p->dimension = dimension;
  p->coordinates = (double*)malloc(sizeof(double) * 2);
  for (n = 0; n < dimension; n++) {
    p->coordinates[n] = coordinates[n];
  }
  return p;
}

Point Point_new2D(const double x, const double y) {
  Point p = (Point)malloc(sizeof(struct Point));
  p->dimension = 2;
  p->coordinates = (double*)malloc(sizeof(double) * 2);
  p->coordinates[0] = x;
  p->coordinates[1] = y;
  return p;
}

Point Point_newFromComplex(const Complex* c) {
  Point p = (Point)malloc(sizeof(struct Point));
  p->dimension = 2;
  p->coordinates = (double*)malloc(sizeof(double) * 2);
  p->coordinates[0] = c->real;
  p->coordinates[1] = c->imag;
  return p;
}

Point Point_new3D(const double x, const double y, const double z) {
  Point p = (Point)malloc(sizeof(struct Point));
  p->dimension = 3;
  p->coordinates = (double*)malloc(sizeof(double) * 3);
  p->coordinates[0] = x;
  p->coordinates[1] = y;
  p->coordinates[2] = z;
  return p;
}

void Point_destroy(Point p) {
  free(p->coordinates);
  free(p);
}

Point Point_copy(Point p) {
  return Point_new(p->dimension, p->coordinates);
}

void Point_print(Point p) {
  size_t n;
  printf("(");
  for (n = 0; n < p->dimension; n++) {
    printf("%.0lf", n, p->coordinates[n]);
    if (n != p->dimension - 1) printf("; ");
  }
  printf(")");
}

void Point_translate(Point p, Vector v) {
  if (p->dimension == v->dimension) {
    size_t n;
    for (n = 0; n < p->dimension; n++) {
      p->coordinates[n] += v->values[n];
    }
  }
  else {
    printf("Invalid point/vector dimension for Point_translate: A (point) is %d and B (vector) is %d\n", p->dimension, v->dimension);
  }
}

static Poly Poly_null;

// Poly methods

Poly Poly_new(const size_t dimension, const size_t n_points, Point* points) {
  Poly poly = (Poly)malloc(sizeof(struct Poly));
  size_t n;
  poly->dimension = dimension;
  poly->n_points = n_points;
  poly->points = (Point*)malloc(sizeof(Point) * n_points);
  for (n = 0; n < dimension; n++) {
    if (points[n]->dimension != dimension) {
      printf("Invalid point dimension for Poly_new: point #%d is %d, while Poly is %d\n", n, points[n]->dimension, dimension);
      return Poly_null;
    }
    poly->points[n] = points[n];
  }
  return poly;
}

Poly Poly_empty(const size_t dimension) {
  Poly poly = (Poly)malloc(sizeof(struct Poly));
  poly->dimension = dimension;
  poly->n_points = 0;
  return poly;
}

Poly Poly_newSegment(Point a, Point b) {
  if (a->dimension != b->dimension) {
    printf("Invalid point dimensions for Poly_newSegment: A is %d while B is %d\n", a->dimension, b->dimension);
    return Poly_null;
  }
  Poly poly = (Poly)malloc(sizeof(struct Poly));
  poly->dimension = a->dimension;
  poly->n_points = 2;
  poly->points = (Point*)malloc(sizeof(Point) * 2);
  poly->points[0] = a;
  poly->points[1] = b;
  return poly;
}

Poly Poly_newTriangle(Point a, Point b, Point c) {
  if (a->dimension != b->dimension || b->dimension != c->dimension) {
    printf("Invalid point dimensions for Poly_newTriangle: A is %d, B is %d while C is %d\n", a->dimension, b->dimension, c->dimension);
    return Poly_null;
  }
  Poly poly = (Poly)malloc(sizeof(struct Poly));
  poly->dimension = a->dimension;
  poly->n_points = 3;
  poly->points = (Point*)malloc(sizeof(Point) * 3);
  poly->points[0] = a;
  poly->points[1] = b;
  poly->points[2] = c;
  return poly;
}

Poly Poly_newQuad(Point a, Point b, Point c, Point d) {
  if (a->dimension != b->dimension || b->dimension != c->dimension || c->dimension != d->dimension) {
    printf("Invalid point dimensions for Poly_newQuad: A is %d, B is %d, C is %d while D is %d\n", a->dimension, b->dimension, c->dimension, d->dimension);
    return Poly_null;
  }
  Poly poly = (Poly)malloc(sizeof(struct Poly));
  poly->dimension = a->dimension;
  poly->n_points = 4;
  poly->points = (Point*)malloc(sizeof(Point) * 4);
  poly->points[0] = a;
  poly->points[1] = b;
  poly->points[2] = c;
  poly->points[3] = d;
  return poly;
}

void Poly_destroy(Poly p) {
  free(p->points);
  free(p);
}

void Poly_destroyPoints(Poly p) {
  size_t n;
  for (n = 0; n < p->dimension; n++) {
    Point_destroy(p->points[n]);
  }
  free(p->points);
  p->n_points = 0;
}

void Poly_print(Poly p) {
  size_t n;
  printf("(");
  for (n = 0; n < p->n_points; n++) {
    Point_print(p->points[n]);
    if (n != p->n_points - 1) printf(", ");
  }
  printf(")");
}

void Poly_appendPoint(Poly poly, Point point) {
  if (poly->dimension != point->dimension) {
    printf("Invalid dimensions for Poly_appendPoint: poly is %d, point is %d\n", poly->dimension, point->dimension);
    return;
  }
  
}
