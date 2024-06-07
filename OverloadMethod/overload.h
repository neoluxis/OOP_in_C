//
// Created by Administrator on 2024/6/7.
//

#ifndef C_OVERLOAD_H
#define C_OVERLOAD_H

#include "stdarg.h"

struct Overload {
  void (*overloaded)(struct Overload *this, int typeval, ...);
};

extern const struct OverloadClass {
  struct Overload (*new)();
} Overload;

#endif //C_OVERLOAD_H
