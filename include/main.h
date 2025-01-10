#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include<unistd.h>
#include <string.h>
#include "../include/SNLogger.h"
#include <time.h>

#define BOARD_X_LENGTH 14
#define BOARD_Y_LENGTH 14
#define INITIAL_SNAKE_LENGTH 4
#define INITIAL_SNAKE_XPOSITION 6
#define INITIAL_SNAKE_YPOSITION 4

#define SNAKE_HEAD '@'
#define SNAKE_BODY '='
#define SNAKE_TAIL '.'
#define EMPTY_ ' '
#define APPLE_ 'x'
#define WALL_ '%'
#define POINT 'o'
#define X_ 'x'

typedef enum _BLOCK_TYPE {
    SNAKEHEAD,
    SNAKEBODY,
    SNAKETAIL,
    EMPTY,
    APPLE,
    WALL,
    X

} BLOCK_TYPE;

typedef struct _RENDER_BLOCK {
    char startPosition;
    char actionPosition;
    char endPosition;
} RENDER_BLOCK;

typedef struct _BLOCK {
    BLOCK_TYPE blockType;
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
