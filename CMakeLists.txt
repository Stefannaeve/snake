cmake_minimum_required(VERSION 3.29)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(snake src/main.c
        src/Arraylist.c
        include/main.h
        include/Arraylist.h
        src/introScreen.c
        include/introScreen.h
        src/SNLogger.c
        include/SNLogger.h
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(snake ${CURSES_LIBRARIES})