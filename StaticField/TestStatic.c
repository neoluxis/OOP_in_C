//
// Created by Administrator on 2024/6/7.
//

#include "TestStatic.h"

static struct TestStatic new(int instance_var) {
  struct TestStatic testStatic = {
      .instance_var = instance_var,
  };
  TestStatic.static_var++;
  return testStatic;
}

struct TestStaticClass TestStatic = {
    .new = &new,
    .static_var = 0,
};
