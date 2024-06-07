//
// Created by Administrator on 2024/6/6.
//

#ifndef C_COMPLEX_H
#define C_COMPLEX_H

struct Complex {
  double real;
  double imag;
  double (*abs)(struct Complex *this);
};

extern const struct ComplexClass {
  struct Complex (*new)(double real, double imag);
} Complex;

#endif //C_COMPLEX_H
