cmake_minimum_required(VERSION 3.27)
project(C C)

set(CMAKE_C_STANDARD 11)

add_executable(C main.c
        Classes/Complex.h
        Classes/Complex.c
        Inheritance/Animal.c
        Inheritance/Animal.h
        Inheritance/Dog.c
        Inheritance/Dog.h
        AccessControl/Parent.c
        AccessControl/Parent.h
        AccessControl/Child.c
        AccessControl/Child.h
        AccessControl/Alien.c
        AccessControl/Alien.h
        StaticField/TestStatic.c
        StaticField/TestStatic.h
        AbstractField/TestAbstract.c
        AbstractField/TestAbstract.h
        OverloadMethod/overload.c
        OverloadMethod/overload.h
)

include_directories(AccessControl Classes Inheritance StaticField AbstractField OverloadMethod)
