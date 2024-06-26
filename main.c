#include <stdio.h>
#include "Classes/Complex.h"
#include "Inheritance/Animal.h"
#include "Inheritance/Dog.h"
#include "Parent.h"
#include "Alien.h"
#include "Child.h"
#include "TestStatic.h"
#include "overload.h"
#include "Car.h"
#include "Vehicle.h"
#include "MockPackage/Pack1/pack1.h"
#include "MockPackage/Pack2/pack2.h"

void animal_say(struct Animal *anm) {
    anm->say(anm);
}

void test_inheritance() {
    struct Animal c = Animal.new(3);
    struct Dog dog = Dog.new(5, "Bark");
    animal_say(&c);
    animal_say(&dog.Animal);
}

void test_access_control() {
    struct Parent parent = Parent.new(3);
    struct Child child = Child.new(5);
    // call public fields
    printf("super.public_var: %d\n", parent.public_var);
    parent.public_func(&parent);
    parent.public_var = 5;
    parent.print(&parent);
    //  super.private_func(&super); // 报错
    parent.private_var_setter(&parent, 10);
    parent.print(&parent);

    // child
    printf("child.public_var: %d\n", child.parent.public_var);
    child.parent.public_func(&child.parent);
}

void test_static_field() {
    struct TestStatic t1 = TestStatic.new(3);
    printf("t1.instance_var: %d\n", t1.instance_var);
    printf("TestStatic.static_var: %d\n", TestStatic.static_var);
    struct TestStatic t2 = TestStatic.new(5);
    printf("t2.instance_var: %d\n", t2.instance_var);
    printf("TestStatic.static_var: %d\n", TestStatic.static_var);
}

void test_overload() {
    struct Overload o = Overload.new();
    o.overloaded(&o, 1, 3);
    o.overloaded(&o, 2, 3, 4);
    o.overloaded(&o, 3, 3.14);
}

void test_abstract() {
    printf("测试抽象类\n");
    // struct Vehicle v = Vehicle.new(4); // 会报错
    struct Car c = Car.new(4);
    c.super.run(&c.super);
}

int main() {
    printf("File: %s", __FILE__);
    return 0;
}
