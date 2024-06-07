//
// Created by Administrator on 2024/6/7.
//

#ifndef C_CAR_H
#define C_CAR_H

#include "Vehicle.h"
#include "stddef.h"

struct Car {
  struct Vehicle super;
  int public_var;
};

extern const struct CarClass {
  struct Car (*new)(int public_var);
} Car;

#endif //C_CAR_H
