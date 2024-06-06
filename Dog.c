//
// Created by Administrator on 2024/6/6.
//

#include "Dog.h"
#include "stdio.h"

static void say(struct Animal *anml) {
  struct Dog *this = (void *)anml - offsetof(struct Dog, Animal);
  printf("%d-year-old dog named %s barks\n", this->Animal.age, this->name);
}

static struct Dog Dog_new(int age, char *name) {
    struct Dog dog = {
        .Animal = Animal.new(age),
        .name = name,
    };
    dog.Animal.say = say;
    return dog;
}

const struct DogClass Dog = {
    .new = &Dog_new,
};
