//
// Created by Administrator on 2024/6/7.
//

#ifndef C_CHILD_H
#define C_CHILD_H

#include "stdio.h"
#include "Parent.h"

struct Child {
  struct Parent parent;
};

extern const struct ChildClass {
  struct Child (*new)(int public_var);
} Child;

#endif //C_CHILD_H
