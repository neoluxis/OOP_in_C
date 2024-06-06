#include <stdio.h>
#include "Complex.h"
#include "Animal.h"
#include "Dog.h"
#include "Parent.h"
#include "Alien.h"
#include "Child.h"

void animal_say(struct Animal *anm) {
  anm->say(anm);
}

int main() {
//  struct Animal c = Animal.new(3);
//  struct Dog dog = Dog.new(5, "Bark");
//  animal_say(&c);
//  animal_say(&dog.Animal);

  struct Parent parent = Parent.new(3);
  struct Child child = Child.new(5);
  // call public fields
  printf("parent.public_var: %d\n", parent.public_var);
  parent.public_func(&parent);
  parent.public_var = 5;
  parent.print(&parent);
//  parent.private_func(&parent); // 报错
  parent.private_var_setter(&parent, 10);
  parent.print(&parent);

  // child
  printf("child.public_var: %d\n", child.parent.public_var);
  child.parent.public_func(&child.parent);
  return 0;
}
