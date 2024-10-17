cmake_minimum_required(VERSION 3.29)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(snake main.c
        Arraylist.c
        main.h
        Arraylist.h)
