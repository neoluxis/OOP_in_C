//
// Created by Administrator on 2024/6/7.
//

#ifndef C_PARENT_H
#define C_PARENT_H

struct Parent {
  int public_var;
  void (*public_func)(struct Parent *this);

  void (*private_var_setter)(struct Parent *this, int private_var);

  int (*private_var_getter)(struct Parent *this);

  void (*print)(struct Parent *this);
};

extern const struct ParentClass {
  struct Parent (*new)(int public_var);
} Parent;

#endif //C_PARENT_H
