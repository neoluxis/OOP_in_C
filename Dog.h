//
// Created by Administrator on 2024/6/6.
//

#ifndef C_DOG_H
#define C_DOG_H
#include "Animal.h"
#include "stddef.h"

struct Dog {
  struct Animal Animal;
  char*name;
};

extern const struct DogClass {
  struct Dog (*new)(int age, char*name);
} Dog;
#endif //C_DOG_H
