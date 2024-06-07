//
// Created by Administrator on 2024/6/7.
//

#include "Car.h"

static void run(struct Vehicle *this) {
  struct Car *car = (void *) this - offsetof(struct Car, super);
  printf("Car.run()\n");
  printf("public_var: %d\n", car->public_var);
}

static struct Car new(int public_var) {
  struct Vehicle vehicle = {
      .run = &run,
  };
  struct Car car = {
      .super = vehicle,
      .public_var = public_var,
  };
  return car;
}

const struct CarClass Car = {
    .new = &new,
};
