//
// Created by Administrator on 2024/6/6.
//

#include "Animal.h"
#include <stdio.h>

static void say(struct Animal *this) {
    printf("Im an animal, age: %d\n", this->age);
}

static struct Animal Animal_new(int age) {
    return (struct Animal) {
        .age = age,
        .say = say,
    };
}

const struct AnimalClass Animal = {
    .new = &Animal_new,
};
