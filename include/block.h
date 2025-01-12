//
// Created by stefan on 1/11/25.
//

#ifndef BLOCK_H
#define BLOCK_H

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

#endif //BLOCK_H
