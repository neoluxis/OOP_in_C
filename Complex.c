//
// Created by Administrator on 2024/6/6.
//

#include "Complex.h"
#include "math.h"

static double c_abs(struct Complex *this) {
    return sqrt(this->real * this->real + this->imag * this->imag);
}

static struct Complex Complex_new(double real, double imag) {
    return (struct Complex) {
        .real = real,
        .imag = imag,
        .abs = c_abs,
    };
}

const struct ComplexClass Complex = {
    .new = &Complex_new,
};
