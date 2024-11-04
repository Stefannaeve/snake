#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/main.h"
#include "../include/Arraylist.h"
#include "../include/introScreen.h"

void renderBoard(BOARD *board, int row, int col);
void printBlock(BLOCK *block);

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

    logDebug("Why doesnt this work goddangit");

    for (int i = 0; i < board.xSize; ++i) {
        for (int j = 0; j < board.ySize; ++j) {
            BLOCK block;
            block.blockType = EMPTY;
            block.x = i;
            block.y = j;
            board.board[i][j] = block;
        }
    }

    renderBoard(&board, row, col);

    getch();

    for (int i = 0; i < board.ySize; ++i) {
        for (int j = 0; j < board.xSize; ++j) {
            BLOCK block = board.board[i][j];
            printBlock(&block);
            refresh();
            usleep(10000);
        }
    }

    getch();

    ARRAYLIST snake = createList();
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i) {
        BLOCK *block = &board.board[INITIAL_SNAKE_XPOSITION][INITIAL_SNAKE_YPOSITION+INITIAL_SNAKE_LENGTH-i];
        if (i == 0) {
            block->blockType = SNAKEHEAD;
        } else if (i == INITIAL_SNAKE_LENGTH-1){
            block->blockType = SNAKETAIL;
        } else {
            block->blockType = SNAKEBODY;
        }
        snake.blocks[i] = block;
        printBlock(block);
        refresh();
        usleep(500000);
    }

    getch();

    endwin();

    return 0;
}

void printBlock(BLOCK *block){
    char type;
    switch(block->blockType) {
        case SNAKEHEAD:
            type = SNAKE_HEAD;
            break;
        case SNAKEBODY:
            type = SNAKE_BODY;
            break;
        case SNAKETAIL:
            type = SNAKE_TAIL;
            break;
        case EMPTY:
            type = EMPTY_;
            break;
        case APPLE:
            type = APPLE_;
            break;
        case WALL:
            type = WALL_;
            break;
        case X:
            type = X_;
            }
    mvprintw(block->actionPositionMetaPositionY, block->actionPositionMetaPositionX, "%c", type);
}

void renderBoard(BOARD *board, int row, int col) {
    int y = board->ySize / 2;
    int x = (board->xSize / 2)*3;
    int xMiddle = col / 2;
    int yMiddle = row / 2;
    for (int i = 0; i < board->ySize; ++i) {
        for (int j = 0; j < board->xSize; ++j) {
            //printf("%c%c%c", board->board[i][j].render_block.startPosition, board->board[i][j].render_block.actionPosition, board->board[i][j].render_block.endPosition);
            mvprintw(yMiddle-y + i, xMiddle-x + j*3, "[");
            mvprintw(yMiddle-y + i, xMiddle-x + j*3+1, "x");
            mvprintw(yMiddle-y + i, xMiddle-x + j*3+2, "]");

            board->board[i][j].actionPositionMetaPositionY = yMiddle-y + i;
            board->board[i][j].actionPositionMetaPositionX = xMiddle-x + j*3+1;

            refresh();

            usleep(10000);
        }
        printf("\n");
    }
}
