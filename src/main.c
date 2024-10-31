#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/main.h"
#include "../include/Arraylist.h"
#include "../include/introScreen.h"

void renderBoard(BOARD *board, int row, int col);

int main(void) {
    BOARD board;
    int row, col;

    initscr();
    start_color();
    //raw();
    keypad(stdscr, TRUE);
    noecho();

    getmaxyx(stdscr, row, col);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);

    //init_pair(1, COLOR_RED, COLOR_RED);
    //init_pair(2, COLOR_GREEN, COLOR_GREEN);
    //init_pair(3, COLOR_CYAN, COLOR_CYAN);
    //init_pair(4, COLOR_BLUE, COLOR_BLUE);

    //attron(A_REVERSE | A_BLINK);
    introScreen();
    clear();

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
            block.render_block.actionPosition = 'x';
            block.render_block.endPosition = ']';
            block.x = i;
            block.y = j;
            board.board[i][j] = block;
        }
    }

    renderBoard(&board, row, col);

    getch();

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

    for (int i = 0; i < board.ySize; ++i) {
        for (int j = 0; j < board.xSize; ++j) {
            BLOCK block = board.board[i][j];
            mvprintw(block.actionPositionMetaPositionY, block.actionPositionMetaPositionX, " ");
            refresh();
            usleep(10000);
        }
    }

    getch();

    endwin();

    return 0;
}

void renderBoard(BOARD *board, int row, int col) {
    int y = board->ySize / 2;
    int x = (board->xSize / 2)*3;
    int xMiddle = col / 2;
    int yMiddle = row / 2;
    logDebug("Row: %d, Col: %d, y: %d, x: %d", row, col, y, x);
    for (int i = 0; i < board->ySize; ++i) {
        for (int j = 0; j < board->xSize; ++j) {
            //printf("%c%c%c", board->board[i][j].render_block.startPosition, board->board[i][j].render_block.actionPosition, board->board[i][j].render_block.endPosition);
            logDebug("StartPosition: %d, actionPosition: %d, endPosition: %d", xMiddle-x + j*3, xMiddle-x + j*3+1, xMiddle-x + j*3+2);
            mvprintw(yMiddle-y + i, xMiddle-x + j*3, "%c", board->board[i][j].render_block.startPosition);
            mvprintw(yMiddle-y + i, xMiddle-x + j*3+1, "%c", board->board[i][j].render_block.actionPosition);
            mvprintw(yMiddle-y + i, xMiddle-x + j*3+2, "%c", board->board[i][j].render_block.endPosition);

            board->board[i][j].actionPositionMetaPositionY = yMiddle-y + i;
            board->board[i][j].actionPositionMetaPositionX = xMiddle-x + j*3+1;

            refresh();

            usleep(10000);
        }
        printf("\n");
    }
}
