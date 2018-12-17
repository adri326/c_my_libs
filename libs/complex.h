#ifndef MY_LIBS_COMPLEX_H
#define MY_LIBS_COMPLEX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct Complex {
  double real;
  double imag;
};

typedef struct Complex Complex;

Complex Complex_new(const double real, const double imag);
Complex Complex_copy(const Complex* c);
double Complex_abs(const Complex* c);
double Complex_abs_square(const Complex* c);
double Complex_arg(Complex* c);
void Complex_add(Complex* c, const Complex* d);
void Complex_print(Complex* c);
void Complex_sub(Complex* c, const Complex* d);
void Complex_mult(Complex* c, const Complex* d);
void Complex_div(Complex* c, const Complex* d);
bool Complex_equal(Complex* c, const Complex* d);
void Complex_pow(Complex* c, const Complex* d);
void Complex_sin(Complex* c);
void Complex_cos(Complex* c);
void Complex_tan(Complex* c);
void Complex_sinh(Complex* c);
void Complex_cosh(Complex* c);
void Complex_tanh(Complex* c);

#endif
