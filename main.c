#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "Arraylist.h"

void renderBoard(BOARD *board);

int main(void) {
    BOARD board;
    board.xSize = BOARD_X_LENGTH;
    board.ySize = BOARD_Y_LENGTH;
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

    renderBoard(&board);

    sleep(1);
    printf("Hello\n");

    ARRAYLIST snake = createList();
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i) {
        if (i == 0) {
            BLOCK *block = &board.board[INITIAL_SNAKE_XPOSITION][INITIAL_SNAKE_YPOSITION+INITIAL_SNAKE_LENGTH-i];
            block->render_block.actionPosition = SNAKE_HEAD;
            snake.nodes[i].positionX = block->x;
            snake.nodes[i].positionY = block->y;
            snake.nodes[i].positionParentNodeX = 0;
            snake.nodes[i].positionParentNodeY = 0;
        } else {
            BLOCK *block = &board.board[INITIAL_SNAKE_XPOSITION][INITIAL_SNAKE_YPOSITION+INITIAL_SNAKE_LENGTH-i];
            const BLOCK *formerBlock = &board.board[INITIAL_SNAKE_XPOSITION][INITIAL_SNAKE_YPOSITION+INITIAL_SNAKE_LENGTH-i-1];
            block->render_block.actionPosition = SNAKE_BODY;
            snake.nodes[i].positionX = block->x;
            snake.nodes[i].positionY = block->y;
            snake.nodes[i].positionParentNodeX = formerBlock->x;
            snake.nodes[i].positionParentNodeY = formerBlock->y;
        }
    }

    renderBoard(&board);

}

void renderBoard(BOARD *board) {
    for (int i = 0; i < board->xSize; ++i) {
        for (int j = 0; j < board->ySize; ++j) {
            printf("%c%c%c", board->board[i][j].render_block.startPosition, board->board[i][j].render_block.actionPosition, board->board[i][j].render_block.endPosition);
        }
        printf("\n");
    }
}
