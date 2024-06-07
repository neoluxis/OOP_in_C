//
// Created by Administrator on 2024/6/7.
//

#ifndef C_TESTSTATIC_H
#define C_TESTSTATIC_H

struct TestStatic {
  int instance_var;
};

extern struct TestStaticClass {
  int static_var; // instance counter
  struct TestStatic (*new)(int instance_var);
} TestStatic;

#endif //C_TESTSTATIC_H
