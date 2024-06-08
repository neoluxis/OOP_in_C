# 纯 C 面向对象编程

## 类与实例 (Class and Instance)

Animal.h

```c
struct Animal {
  ...
};

extern const struct AnimalClass {
    struct Animal (*new)(...);
} Animal;
```

Animal.c

```c
#include "Animal.h"

static struct Animal new(...) {
  ...
}

static const struct AnimalClass Animal = {
  .new = &new,
};
```

**注意： 如果在 `.c` 文件中不使用 `static` 关键字把函数定义局限到当前文件，
函数名称重复的时候就会报错**

main.c

```c
#include "Animal.h"

int main() {
struct Animal a = Animal.new(...);
}
```

定义一个常量用于实例化一个对象，然后使用这个 `new()` 方法

## 构造器 (Constructor)

构造器只需要定义补充对应类的 `new()` 方法即可

## 成员和方法 (Member and Method)

成员和方法可以在类的结构体中声明，之后在 `new()` 方法中初始化
Animal.h

```c
struct Animal {
  int age;
  void (*say)(struct Animal *self);
};

extern const struct AnimalClass {
    struct Animal (*new)(int age);
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
    .say = &say,
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

同时方法只在 `.c` 文件中定义，不在头文件中声明，这样方法就只能通过
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

在面相对象程序中，访问权限系统通常有

- 公共 (Public)
- 保护 (Protected)
- 私有 (Private)

由于本人能力有限，只能实现 `Public` 和 `Private` 两种访问权限。
即子类和外部类均无法访问 `Private` 成员或均可以访问 `Public` 成员；
没有实现 子类可以访问，外部类不可访问的 `Protected` 成员。

实现思路如下：

- 在头文件中定义结构体的公共域，假设命名为 `Parent`  
  Parent.c
  ```c
  struct Parent {
    int public_var;
    void (*public_func)(struct Parent *this);
    void (*private_var_setter)(struct Parent *this, int private_var);
    int (*private_var_getter)(struct Parent *this);
    void (*print)(struct Parent *this);
  };
  ```
- 在源文件中定义另一个结构体，命名为 `ParentPriv`。其中先定义全部的公共域，
  接着定义私有域。  
  Parent.c
  ```c
  struct ParentPriv {
    // public field (just copy)
    int public_var;
    void (*public_func)(struct Parent *this);
    void (*private_var_setter)(struct Parent *this, int private_var);
    int (*private_var_getter)(struct Parent *this);
    void (*print)(struct Parent *this);
    
    // private field
    int private_var;
    void (*private_func)(struct Parent *this);
  };
  ```
- 用同样的方法定义 `new()` 方法，但是在返回之前，定义的结构体变量都应该是 `ParentPriv`
- 在返回前，将 `ParentPriv` 类型的变量强制转换为 `Parent` 类型的变量
  ```c
  static struct Parent new(int public_var) {
    struct ParentPriv super = {
        .public_var = public_var,
        .public_func = &public_func,
        .private_var_setter = &private_var_setter,
        .private_var_getter = &private_var_getter,
        .print = &print,
        .private_func = &private_func,
    };
    return *(struct Parent *) &super;
  } 
  ```
- 之后就可以使用 `new()` 方法来实例化一个对象，然后使用对应的
  `Accessor` 和 `Mutator` 来访问私有变量

## 静态域 (Static Field)

静态域可以写在类所对应的 Class 结构体中，可以脱离类的结构体调用。  
Animal.h

```c
struct Animal {
  ...
};

extern const struct AnimalClass {
    struct Animal (*new)(...);
    int static_field;
} Animal;
```

main.c

```c
#include "Animal.h"
int main() {
  Animal.static_field = 10;
  return 0;
}
```

但是这样的方法表明，静态域将只能通过类名调用，而不能通过实例调用。

如果想要让类名和实例均可以调用静态方法，可以分别在两个结构体中定义，然后将其
绑定到同一个函数。静态域不可调用任何非静态域，因此可以在参数列表里面不
列出 `this` 指针。

在这种情况下，静态域可能受到更改，因此类所对应的 Class 结构体不能再定义为 `const` 类型。

TestStatic.h

```c
extern struct TestStaticClass {
  int static_var; // instance counter
  struct TestStatic (*new)(int instance_var);
} TestStatic;
```

本人能力有限，没有实现静态变量在类和实例中均可调用，

所以最好直接通过类名调用静态域。

## 抽象类，抽象方法，接口 (Abstract Class, Abstract Method, Interface)

抽象类和接口的成员函数没有实现，在子类中实现。同时不允许实例化抽象类和接口。

不允许实例化很简单，可以在 `new()` 方法中返回 `NULL` 来表示实例化失败，或
直接不添加 `new()` 方法使之无法被实例化。当然我们要约定只使用 `new()` 初始化，因为
在 C语言中完全可以直接初始化结构体。

在子类的 `new()` 方法中，可以分别实现基类的接口方法，然后手动绑定给基类的
函数指针。

相对应的抽象方法可以直接把对应的函数指针绑定为 `NULL`

抽象类和接口的实现参考 `/AbstractField/` 文件夹

## 方法重载 (Method Overloading)

方法重载是指在同一个类中，可以有多个同名函数，但是参数列表不同。

在 C 语言中，函数重载是不被允许的，因为 C 语言编译时，不会像 C++ 一样
把函数名和参数列表一起编译，而是只编译函数名。因此我们可以把重载的不同版本使用不同的函数名来标记，
之后在同一个函数中对参数进行判断，来决定究竟是调用了哪一个函数。

也就是说，手动指定重载版本是不能够省略的。

参考 `/OverloadMethod/overload.c`,
`/OverloadMethod/overload.h` 文件

## 命名空间 (Namespace)

C语言没有命名空间的概念，可以通过约定的方式实现（虽然比较水）

## 包 (Package)

C 语言无法强制模拟系统级的包机制（就像Java 或 Python），
但是 通过 `__FILE__` 宏可以获取当前文件的路径，进而可以模拟项目内的包机制。

### __FILE__ 宏

`__FILE__` 宏是一个预定义宏，表示当前文件在项目中的路径。

/home/xxx/workspace/OOP_in_C/main.c
```c
#include <stdio.h>
int main() {
  printf("File: %s\n", __FILE__);
  return 0;
}
```
会打印出 `File: /home/xxx/workspace/OOP_in_C/main.c`

/home/xxx/workspace/OOP_in_C/MockPackage/MockPack.c
```c
#include <stdio.h>
int main() {
  printf("File: %s\n", __FILE__);
  return 0;
}
```
则会打印出 `File: /home/xxx/workspace/OOP_in_C/MockPackage/MockPack.c`

通过字符串操作，可以获取到文件相对于项目根目录的路径，进而可以模拟包机制。

- 有一个问题，及时使用这样的方法处理包机制，也仍然不允许同名， 
  而且并不能通过 `包名.类名` 的方式来调用类，只能直接通过类名来调用类。

## 泛型 (Generic)

- [ ] TODO

---

## 总结

- C 语言是一种面向过程的语言，但是通过结构体和函数指针，可以模拟部分面向对象编程的思想
- C 语言的面向对象编程是通过结构体和函数指针来实现的
- 虽然可以实现，但是实际应用中很鸡肋，语言特性并没有对其有很好的支持
- 本人能力有限，实现的面向对象编程只是一个简单的模拟，许多功能都还未能实现，同时
  有些功能只能通过约定的方式实现，并不能在代码中强制实现。

