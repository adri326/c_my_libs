#include "complex.h"

Complex Complex_new(const double real, const double imag) {
  Complex c;
  c.real = real;
  c.imag = imag;
  return c;
}

Complex Complex_copy(const Complex* c) {
  Complex d;
  d.real = c->real;
  d.imag = c->imag;
  return d;
}

Complex Complex_conj(const Complex* c) {
  Complex d;
  d.real = c->real;
  d.imag = -c->imag;
  return d;
}

void Complex_add(Complex* c, const Complex* d) {
  c->real += d->real;
  c->imag += d->imag;
}

void Complex_sub(Complex* c, const Complex* d) {
  c->real -= d->real;
  c->imag -= d->imag;
}

void Complex_mult(Complex* c, const Complex* d) {
  double tmp = c->real;
  c->real = c->real * d->real - c->imag * d->imag;
  c->imag = c->imag * d->real + tmp * d->imag;
}

void Complex_div(Complex* c, const Complex* d) {
  double a = Complex_abs_square(d);
  double real = c->real;
  c->real = (c->real * d->real + c->imag * d->imag) / a;
  c->imag = (c->imag * d->real - c->real * d->imag) / a;
}

bool Complex_equal(Complex* c, const Complex* d) {
  return c->real == d->real && c->imag == d->imag;
}

double Complex_abs(const Complex* c) {

  return sqrt(c->real * c->real + c->imag * c->imag);
}

double Complex_abs_square(const Complex* c) {
  return c->real * c->real + c->imag * c->imag;
}

double Complex_arg(Complex* c) {
  if (c->real > 0.) {
    return atan(c->imag / c->real);
  }
  else if (c->real == 0) {
    if (c->imag > 0) {
      return M_PI / 2;
    }
    else {
      return M_PI * 3 / 2;
    }
  }
  else {
    return atan(c->imag / c->real) + M_PI;
  }
}

void Complex_pow(Complex* c, const Complex* d) {
  if (d->imag != 0) {
    double r = d->real * Complex_arg(c);
    double s = Complex_abs_square(c);
    double real = cos(r + d->imag / 2 * log(s));
    double imag = sin(r + d->imag / 2 * log(s));
    double mult = exp(-d->imag * Complex_arg(c)) * pow(s, d->real / 2);
    c->real = real * mult;
    c->imag = imag * mult;
  }
  else {
    double r = pow(Complex_abs(c), d->real);
    double a = Complex_arg(c);
    c->real = r * cos(d->real * a);
    c->imag = r * sin(d->real * a);
  }
}

void Complex_sin(Complex* c) {
  Complex e1 = Complex_new(M_E, 0);
  Complex e2 = Complex_copy(&e1);
  Complex d = Complex_new(0, 0);
  Complex_sub(&d, c);
  Complex_pow(&e1, c);
  Complex_pow(&e1, &d);
  c->real = (e1.imag - e2.imag) / 2;
  c->imag = (e1.real - e2.real) / -2;
}

void Complex_cos(Complex* c) {
  Complex e1 = Complex_new(M_E, 0);
  Complex e2 = Complex_copy(&e1);
  Complex d = Complex_new(0, 0);
  Complex_sub(&d, c);
  Complex_pow(&e1, c);
  Complex_pow(&e1, &d);
  c->real = (e1.imag + e2.imag) / 2;
  c->imag = (e1.real + e2.real) / -2;
}

void Complex_tan(Complex* c) {
  Complex s = Complex_copy(c);
  Complex t = Complex_copy(c);
  Complex_sin(&s);
  Complex_cos(&t);
  Complex_div(&s, &t);
  c->real = s.real;
  c->imag = s.imag;
}

void Complex_sinh(Complex* c) {
  Complex e1 = Complex_new(M_E, 0);
  Complex e2 = Complex_copy(&e1);
  Complex d = Complex_new(0, 0);
  Complex_sub(&d, c);
  Complex_pow(&e1, c);
  Complex_pow(&e1, &d);
  c->real = (e1.real - e2.real) / 2;
  c->imag = (e1.imag - e2.imag) / 2;
}

void Complex_cosh(Complex* c) {
  Complex e1 = Complex_new(M_E, 0);
  Complex e2 = Complex_copy(&e1);
  Complex d = Complex_new(0, 0);
  Complex_sub(&d, c);
  Complex_pow(&e1, c);
  Complex_pow(&e1, &d);
  c->real = (e1.real + e2.real) / 2;
  c->imag = (e1.imag + e2.imag) / 2;
}

void Complex_tanh(Complex* c) {
  Complex s = Complex_copy(c);
  Complex t = Complex_copy(c);
  Complex_sinh(&s);
  Complex_cosh(&t);
  Complex_div(&s, &t);
  c->real = s.real;
  c->imag = s.imag;
}

void Complex_print(Complex* c) {
  if (c->imag == 0) {
    printf("%f", c->real);
  }
  else if (c->real == 0) {
    printf("%f*i", c->imag);
  }
  else {
    printf("%f + %f*i", c->real, c->imag);
  }
}
