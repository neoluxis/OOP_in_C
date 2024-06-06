cmake_minimum_required(VERSION 3.27)
project(C C)

set(CMAKE_C_STANDARD 11)

add_executable(C main.c
        Complex.h
        Complex.c
        Animal.c
        Animal.h
        Dog.c
        Dog.h
)
