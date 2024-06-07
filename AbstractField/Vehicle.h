//
// Created by Administrator on 2024/6/7.
//

#ifndef C_VEHICLE_H
#define C_VEHICLE_H

#include "stdio.h"

struct Vehicle {
  void (*run)(struct Vehicle *this);
};

extern const struct VehicleClass {
  struct Vehicle (*new)(); // 不需要构造函数，构造函数绑定为 NULL 即可禁止调用
} Vehicle;

#endif //C_VEHICLE_H
