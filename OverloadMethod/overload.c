//
// Created by Administrator on 2024/6/7.
//

#include "overload.h"
#include "stdio.h"

static void overloaded_1(struct Overload *this, int val) {
  printf("overloaded_1: %d\n", val);
}

static void overloaded_2(struct Overload *this, int val1, int val2) {
  printf("overloaded_2: %d, %d\n", val1, val2);
}

static void overloaded_3(struct Overload *this, float val1) {
  printf("overloaded_3: %.3f\n", val1);
}

static void overloaded(struct Overload *this, int typeval, ...) {
  va_list args;
  va_start(args, typeval);
  switch (typeval) {
    case 1:
      overloaded_1(this, va_arg(args, int));
      break;
    case 2:
      overloaded_2(this, va_arg(args, int), va_arg(args, int));
      break;
    case 3:
      overloaded_3(this, va_arg(args, double));
      break;
    default:
      printf("Unknown typeval: %d\n", typeval);
  }
  va_end(args);
}

static struct Overload new() {
  struct Overload overload = {
      .overloaded = &overloaded,
  };
  return overload;
}

const struct OverloadClass Overload = {
    .new = &new,
};