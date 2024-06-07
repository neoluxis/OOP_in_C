//
// Created by Administrator on 2024/6/7.
//

#include "Vehicle.h"

static struct Vehicle new() {
  printf("Vehicle.new()\n");
  struct Vehicle vehicle = {
  };
  return vehicle;
} // 永远不能够被调用了

const struct VehicleClass Vehicle = {
    .new = NULL,
};
