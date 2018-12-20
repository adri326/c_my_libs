#ifndef MY_LIBS_GEOMETRY_H
#define MY_LIBS_GEOMETRY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "complex.h"

struct Vector {
  size_t dimension;
  double* values;
};

typedef struct Vector* Vector;


struct Point {
  size_t dimension;
  double* coordinates;
};

typedef struct Point* Point;


struct Poly {
  size_t dimension;
  size_t n_points;
  Point* points;
};

typedef struct Poly* Poly;

// Vector methods

// creates a new Vector, copying the values from the `values` argument withing the fields of the new, n-dimension Vector
Vector Vector_new(const size_t dimension, double* values);
// creates a new 2D Vector, copying `x` and `y` in its fields
Vector Vector_new2D(const double x, const double y);
// creates a new 3D Vector, copying `x`, `y` and `z` in its fields
Vector Vector_new3D(const double x, const double y, const double z);
// creates a new n-D Vector from two n-D points
Vector Vector_newFromPoints(Point a, Point b);
// destroys a Vector and its `values` array
void Vector_destroy(Vector v);
// copies all the fields of `v` into a new Vector instance
Vector Vector_copy(Vector v);
// prints out a Vector, in the `(x; y; ...; ω)` form
void Vector_print(Vector v);
// returns the dot product of two vectors `a` and `b`; they need to have the same dimension
double Vector_dotProduct(Vector a, Vector b);
// returns the cross product of two vectors `a` and `b`; they need to have the same dimension
double Vector_crossProduct(Vector a, Vector b);
// returns whether or not two vectors, `a` and `b`, are collinear; they need to have the same dimension
bool Vector_collinear(Vector a, Vector b);
// returns whether or not two vectors, `a` and `b`, are orthogonal; they need to have the same dimension
bool Vector_orthogonal(Vector a, Vector b);
// rotates a vector `v` by `theta`; `v` has to be 2D; modifies `v`
void Vector_rotate2D(Vector v, double theta);
// returns the length of a vector
double Vector_length(Vector v);

// Point methods

// creates a new Point, copying the values from the `coordinates` argument withing the coordinates of the new, n-dimension Point
Point Point_new(const size_t dimension, double* coordinates);
// creates a new, 2-dimensional, point; `x` and `y` are copied in its coordinates array
Point Point_new2D(const double x, const double y);
// creates a new, 2-dimensional point from a complex number; the real and imaginary parts are copied into the `x` and `y` coordinates
Point Point_newFromComplex(const Complex* c);
// creates a new, 3-dimensional, point; `x`, `y` and `z` are copied in its coordinates array
Point Point_new3D(const double x, const double y, const double z);
// destroys a point instance and its coordinates array
void Point_destroy(Point p);
// copies all the fields of `p` into a new Point instance
Point Point_copy(Point p);
// prints out a Point, in the `(x; y; ...; ω)` form
void Point_print(Point p);
// translates a point `p` by the vector `v`; they need to have the same dimension; modifies `p`
void Point_translate(Point p, Vector v);
// gives the distance between two points
double Point_distance(Point a, Point b);

// Poly methods

// creates a new Poly, being a `dimension`-dimensional polygon with `n_points` points; copies the Point pointers
Poly Poly_new(const size_t dimension, const size_t n_points, Point* points);
// creates a new, empty Poly
Poly Poly_newSegment(Point a, Point b);
// creates a segment Poly, using the dimension of the two input points; `a` and `b` must have the same dimension
Poly Poly_newSegment(Point a, Point b);
// creates a triangle Poly, using the dimension of the three input points; `a`, `b` and `c` must have the same dimension
Poly Poly_newTriangle(Point a, Point b, Point c);
// creates a quad Poly, using the dimension of the four input points; `a`, `b`, `c` and `d` must have the same dimension
Poly Poly_newQuad(Point a, Point b, Point c, Point d);
// destroys a Poly instance, not its points
void Poly_destroy(Poly p);
// destroys a Poly's points, not the instance; frees the Poly's `points` array
void Poly_destroyPoints(Poly p);
// does both Poly_destroyPoints and Poly_destroy
void Poly_destroyAll(Poly p);
// prints out a Poly instance in the `((xa; ya; ...), (xb; yb; ...), ...)` form
void Poly_print(Poly p);
// appends a Point to a Poly instance, freeing its old `points` array
void Poly_appendPoint(Poly poly, Point point);
// pops the last Point in the Poly instance, the `points` array is not moved
Point Poly_popPoint(Poly poly);
// returns whether or not two segments intersect each other
bool Poly_segmentsIntersect(Poly a, Poly b);
// returns the perimeter of a polygon
double Poly_perimeter(Poly p);

#endif
