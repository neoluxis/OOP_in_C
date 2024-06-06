# 纯 C 面向对象编程

## 类与实例 (Class and Instance)

Animal.h

```c
struct Animal {
  ...
};

extern const struct AnimalClass {
    struct Animal (*Complex_new)(...);
} Animal;
```

Animal.c

```c
#include "Animal.h"

static struct Animal new(...) {
  ...
}

static const struct AnimalClass Animal = {
  .Complex_new = &new,
};
```

**注意： 如果在 `.c` 文件中不使用 `static` 定义函数，如果函数名称重复，就会报错**

main.c

```c
#include "Animal.h"

int main() {
struct Animal a = Animal.new(...);
}
```

定义一个常量用于实例化一个对象，然后使用这个 `Complex_new()` 方法

## 构造器 (Constructor)

构造器只需要定义补充对应类的 `Complex_new()` 方法即可

## 成员和方法 (Member and Method)

成员和方法可以在类的结构体中声明，之后在 `Complex_new()` 方法中初始化
Animal.h

```c
struct Animal {
  int age;
  void (*say)(struct Animal *self);
};

extern const struct AnimalClass {
    struct Animal (*Complex_new)(int age);
} Animal;
```

Animal.c

```c
#include "Animal.h"

static void say(struct Animal *self) {
  printf("I am %d years old\n", self->age);
}

static struct Animal new(int age) {
  struct Animal a = {
    .age = age,
    .say = say,
  };
  return a;
}
...
```

main.c

```c
#include "Animal.h"

int main() {
  struct Animal a = Animal.new(10);
  a.say(&a);
}
```

同时方法只在 `.c` 文件中定义，可以不在头文件中声明，方法就只能通过
实例来调用。

## 继承 (Inheritance)

- 基类在子类中作为一个成员变量
  ```c
  struct Dog {
    struct Animal Animal;
    char*name;
  };
  ```

- 子类可以重新覆盖函数指针来重写基类的方法，实现多态
  ```c
  dog.Animal.say = new_say;
  ```

- 当重写的方法被调用的时候，我们确定它是由基类的一个实例调用的，因为方法接受一个
  基类的指针作为参数，所以我们需要使用 `stddef.h` 提供的 `offsetof()` 宏来判断
  基类的实例是否是子类的实例
  ```c
  #include <stddef.h>
  static void new_say(struct Animal *self) {
  struct Dog *this = (void *)self - offsetof(struct Dog, Animal);
  printf("%d-year-old dog named %s barks\n", this->Animal.age, this->name);
  }
  ```

- 显然，这种继承方法允许多继承

## 访问控制 (Access Control)

[//]: # (TODO: 未完成)

## 抽象类，抽象方法，接口 (Abstract Class, Abstract Method, Interface)

## 命名空间 (Namespace)

---

参考链接:

1. [Class in C](https://pvv.ntnu.no/~hakonhal/main.cgi/c/classes/)
