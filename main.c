#include <stdio.h>
#include "Complex.h"
#include "Animal.h"
#include "Dog.h"

void animal_say(struct Animal *anm) {
  anm->say(anm);
}

int main() {
  struct Animal c = Animal.new(3);
  struct Dog dog = Dog.new(5, "Bark");
  animal_say(&c);
  animal_say(&dog.Animal);
  return 0;
}
