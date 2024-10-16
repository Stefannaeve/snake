#include <stdio.h>

typedef struct _BLOCK {
    int x;
    int y;
} BLOCK;

typedef struct _BOARD {
    int xSize;
    int ySize;
    BLOCK board[][];
} BOARD;

typedef struct _RENDER_BLOCK {

} RENDER_BLOCK;

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
