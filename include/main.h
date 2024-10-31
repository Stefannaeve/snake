#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include<unistd.h>
#include <string.h>
#include "../include/SNLogger.h"
#include <time.h>

#define BOARD_X_LENGTH 12
#define BOARD_Y_LENGTH 12
#define INITIAL_SNAKE_LENGTH 4
#define INITIAL_SNAKE_XPOSITION 6
#define INITIAL_SNAKE_YPOSITION 4

#define SNAKE_HEAD '@'
#define SNAKE_BODY '='
#define POINT 'o'

typedef struct _RENDER_BLOCK {
    char startPosition;
    char actionPosition;
    char endPosition;
} RENDER_BLOCK;

typedef struct _BLOCK {
    int x;
    int y;
    int actionPositionMetaPositionX;
    int actionPositionMetaPositionY;
    RENDER_BLOCK render_block;
} BLOCK;

typedef struct _BOARD {
    int xSize;
    int ySize;
    BLOCK **board;
} BOARD;

#endif //MAIN_H
