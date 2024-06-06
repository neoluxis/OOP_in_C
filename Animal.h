//
// Created by Administrator on 2024/6/6.
//

#ifndef C_ANIMAL_H
#define C_ANIMAL_H

struct Animal {
  int age;
  void (*say)(struct Animal *self);
};

extern const struct AnimalClass {
  struct Animal (*new)(int age);
} Animal;

#endif //C_ANIMAL_H
