#include <stdio.h>
#include <stdlib.h>

#define BOARDX 12
#define BOARDY 12

typedef struct _RENDER_BLOCK {
    char startPosition;
    char actionPosition;
    char endPosition;
} RENDER_BLOCK;

typedef struct _BLOCK {
    int x;
    int y;
    RENDER_BLOCK render_block;
} BLOCK;

typedef struct _BOARD {
    int xSize;
    int ySize;
    BLOCK **board;
} BOARD;

int main(void) {
    BOARD board;
    board.xSize = BOARDX;
    board.ySize = BOARDY;
    board.board = malloc((board.xSize * sizeof(BLOCK)));
    for (int i = 0; i < board.xSize; ++i) {
        board.board[i] = malloc(board.ySize * sizeof(BLOCK));
    }

    for (int i = 0; i < board.xSize; ++i) {
        for (int j = 0; j < board.ySize; ++j) {
            BLOCK block;
            block.render_block.startPosition = '[';
            block.render_block.actionPosition = ' ';
            block.render_block.endPosition = ']';
            block.x = i;
            block.y = j;
            board.board[i][j] = block;
        }
    }

    for (int i = 0; i < board.xSize; ++i) {
        for (int j = 0; j < board.ySize; ++j) {
            printf("%c%c%c", board.board[i][j].render_block.startPosition, board.board[i][j].render_block.actionPosition, board.board[i][j].render_block.endPosition);
        }
        printf("\n");
    }


}
