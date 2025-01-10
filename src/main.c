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

    // Initialize the board
    board.xSize = BOARD_X_LENGTH;
    board.ySize = BOARD_Y_LENGTH;
    board.board = malloc((board.xSize * sizeof(BLOCK)));
    for (int i = 0; i < board.xSize; ++i) {
        board.board[i] = malloc(board.ySize * sizeof(BLOCK));
    }

    logInfo("Assign empty blocks");
    // Assign empty block to every node in board
    for (int i = 0; i < board.xSize; ++i) {
        for (int j = 0; j < board.ySize; ++j) {
            BLOCK block;
            block.blockType = EMPTY;
            block.x = i;
            block.y = j;
            board.board[i][j] = block;
        }
    }

    logInfo("Render board");
    // Render the board, including the board pieces not for playing
    renderBoard(&board, row, col);

    getch();

    logInfo("Change action positions to x");
    // change all the action positions from 'x' to ' '
    for (int i = 0; i < board.ySize; ++i) {
        for (int j = 0; j < board.xSize; ++j) {
            BLOCK block = board.board[i][j];
            printBlock(&block);
            refresh();
            usleep(10000);
        }
    }

    getch();

    logInfo("Add top and bottom walls");
    // Add top and bottom walls
    for (int i = 0; i < board.xSize; ++i) {
        logDebug("Boards type: %d", board.board[0][i].blockType);
        board.board[0][i].blockType = WALL;
        board.board[board.ySize-1][i].blockType = WALL;

        logDebug("board y size: %d", board.ySize);
        logDebug("i: %d", i);


        printBlock(&board.board[0][i]);
        printBlock(&board.board[board.ySize-1][i]);
        refresh();
        usleep(10000);
    }

    // Start at 1 pga the top wall already been placed, same with the end condition
    for (int i = 1; i < board.ySize; ++i) {
        board.board[i][0].blockType = WALL;
        board.board[i][board.xSize-1].blockType = WALL;

        printBlock(&board.board[i][0]);
        printBlock(&board.board[i][board.xSize-1]);
        refresh();
        usleep(50000);
    }

    // Creating the actual snake
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
