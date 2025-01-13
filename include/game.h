#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include<unistd.h>
#include <string.h>
#include "../include/SNLogger.h"
#include <time.h>
#include <bits/pthreadtypes.h>

#include "Arraylist.h"
#include "block.h"

int game();

#define BOARD_X_LENGTH 14
#define BOARD_Y_LENGTH 14
#define INITIAL_SNAKE_LENGTH 4
#define INITIAL_SNAKE_XPOSITION 6
#define INITIAL_SNAKE_YPOSITION 4

#define SPEED 10

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define ERROR -1
#define PASS 0

#define SNAKE_HEAD '@'
#define SNAKE_BODY '='
#define SNAKE_TAIL '.'
#define EMPTY_ ' '
#define APPLE_ 'x'
#define WALL_ '%'
#define POINT 'o'
#define X_ 'x'

typedef struct _BOARD {
    int xSize;
    int ySize;
    BLOCK **board;
} BOARD;

#endif //GAME_H
