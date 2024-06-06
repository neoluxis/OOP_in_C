//
// Created by Administrator on 2024/6/7.
//

#include "Child.h"

static struct Child new(int public_var) {
  struct Child child = {
      .parent = Parent.new(public_var),
  };
  return child;
}

const struct ChildClass Child = {
    .new = &new,
};
