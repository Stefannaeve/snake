#include "../include/game.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/introScreen.h"
#include <pthread.h>
#include <fcntl.h>

void renderBoard(BOARD *board, int row, int col);

void printBlock(BLOCK *block);

int initializeBoard(BOARD *board);

int populateBoardWithEmptyBlocks(BOARD *board);

void addWallsToBoard(BOARD *board);

void creatingSnake(ARRAYLIST *snake, BOARD *board);

void gameLoop(ARRAYLIST *snake, BOARD *board);

void clientLoop(unsigned int *clientPosition);

void moveSnake(ARRAYLIST *snake, unsigned int *clientPosition, BOARD *board);

int game() {
    BOARD board;
    int row, col, iStatus = 0;

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
    iStatus = initializeBoard(&board);
    if (iStatus != PASS) {
        printf("Error: %d", iStatus);
        logError("Error in initializeBoard function");
        return iStatus;
    }

    logInfo("Assign empty blocks");
    // Assign empty block to every node in board
    populateBoardWithEmptyBlocks(&board);

    logInfo("Render board");
    // Render the board, including the board pieces not for playing, actionPosition as 'x'
    renderBoard(&board, row, col);

    getch();

    logInfo("Change action positions to x");
    // change all the action positions from 'x' to ' '
    for (int i = 0; i < board.ySize; ++i) {
        for (int j = 0; j < board.xSize; ++j) {
            BLOCK block = board.board[i][j];
            printBlock(&block);
            usleep(SPEED * 10);
        }
    }

    getch();

    logInfo("Add top and bottom walls");
    // Add top and bottom walls
    addWallsToBoard(&board);

    // Creating the actual snake
    ARRAYLIST snakeObject;
    ARRAYLIST *snake = &snakeObject;

    createList(snake);
    creatingSnake(snake, &board);
    getch();

    gameLoop(snake, &board);

    endwin();

    return 0;
}

void gameLoop(ARRAYLIST *snake, BOARD *board) {
    unsigned int clientPosition = 0;
    int done = 1;

    halfdelay(10);

    while (1) {
        clientLoop(&clientPosition);
        moveSnake(snake, &clientPosition, board);
    }
}

void clientLoop(unsigned int *clientPosition) {
    logDebug("10");

    char validKeys[] = {'W', 'A', 'S', 'D', 'w', 'a', 's', 'd'};

    int currentButton = 0;
    logDebug("Before fgetc");
    currentButton = fgetc(stdin);
    logDebug("After fgetc -> currentButton = %d", currentButton);


    if (currentButton != ERR) {
        logDebug("11,2");
        for (int i = 0; i < sizeof(validKeys); i++) {
            logDebug("12%d", i);
            if (currentButton == validKeys[i]) {
                logDebug("13%d", i);
                *clientPosition = currentButton;
                break;
            }
        }
    } else {
    }
}

void moveSnake(ARRAYLIST *snake, unsigned int *clientPosition, BOARD *board) {
    logDebug("20");

    const int sizeOfSnake = snake->size;
    unsigned int currentPosition = UP;

    int newYPosition = 0;
    int newXPosition = 0;
    int formerYPosition = 0;
    int formerXPosition = 0;

    usleep(300000);
    currentPosition = *clientPosition;

    switch (currentPosition) {
        case UP:
            newYPosition = snake->blocks[0]->y;
            newXPosition = snake->blocks[0]->x - 1;
            break;
        case DOWN:
            newYPosition = snake->blocks[0]->y;
            newXPosition = snake->blocks[0]->x + 1;
            break;
        case LEFT:
            newYPosition = snake->blocks[0]->y - 1;
            newXPosition = snake->blocks[0]->x;
            break;
        case RIGHT:
            newYPosition = snake->blocks[0]->y + 1;
            newXPosition = snake->blocks[0]->x;
            break;
        default:
            newYPosition = snake->blocks[0]->y;
            newXPosition = snake->blocks[0]->x - 1;
            break;
    }

    for (int i = 0; i < sizeOfSnake; i++) {
        logDebug("21");
        // SET FORMER POSITIONS TO THE CURRENT NODE POSITION
        formerYPosition = snake->blocks[i]->y;
        formerXPosition = snake->blocks[i]->x;

        //SET CURRENT POINTER TO THE NEW MEMORY PLACE, ADD RIGHT BLOCKTYPE
        snake->blocks[i] = &board->board[newXPosition][newYPosition];
        if (i < 1) {
            snake->blocks[i]->blockType = SNAKEHEAD;
        } else if (i == sizeOfSnake - 1) {
            snake->blocks[i]->blockType = SNAKETAIL;
        } else {
            snake->blocks[i]->blockType = SNAKEBODY;
        }

        // SET NEW POSITION TO THE ORIGINAL CURRENT NODE POSITIONS
        newYPosition = formerYPosition;
        newXPosition = formerXPosition;

        printBlock(snake->blocks[i]);

        // SET EMPTY SPACE WHERE THE SNAKE LEFT FROM, IF NOT ELONGATED BY APPLE
        if (i == sizeOfSnake - 1) {
            board->board[formerXPosition][formerYPosition].blockType = EMPTY;
            printBlock(&board->board[formerXPosition][formerYPosition]);
        }
    }
}

void printBlock(BLOCK *block) {
    char type;
    switch (block->blockType) {
        case SNAKEHEAD:
            type = SNAKE_HEAD;
            attron(COLOR_PAIR(3));
            break;
        case SNAKEBODY:
            type = SNAKE_BODY;
            attron(COLOR_PAIR(3));
            break;
        case SNAKETAIL:
            type = SNAKE_TAIL;
            attron(COLOR_PAIR(3));
            break;
        case EMPTY:
            type = EMPTY_;
            break;
        case APPLE:
            type = APPLE_;
            attron(COLOR_PAIR(2));
            break;
        case WALL:
            type = WALL_;
            attron(COLOR_PAIR(4));
            break;
        case X:
            type = X_;
    }

    mvprintw(block->actionPositionMetaPositionY, block->actionPositionMetaPositionX, "%c", type);
    refresh();
}

void renderBoard(BOARD *board, int row, int col) {
    int y = board->ySize / 2;
    int x = (board->xSize / 2) * 3;
    int xMiddle = col / 2;
    int yMiddle = row / 2;
    for (int i = 0; i < board->ySize; ++i) {
        for (int j = 0; j < board->xSize; ++j) {
            //printf("%c%c%c", board->board[i][j].render_block.startPosition, board->board[i][j].render_block.actionPosition, board->board[i][j].render_block.endPosition);
            mvprintw(yMiddle - y + i, xMiddle - x + j * 3, "[");
            mvprintw(yMiddle - y + i, xMiddle - x + j * 3 + 1, "x");
            mvprintw(yMiddle - y + i, xMiddle - x + j * 3 + 2, "]");

            board->board[i][j].actionPositionMetaPositionY = yMiddle - y + i;
            board->board[i][j].actionPositionMetaPositionX = xMiddle - x + j * 3 + 1;

            refresh();

            usleep(SPEED * 10);
        }
        printf("\n");
    }
}

int initializeBoard(BOARD *board) {
    board->xSize = BOARD_X_LENGTH;
    board->ySize = BOARD_Y_LENGTH;
    board->board = malloc((board->xSize * sizeof(BLOCK)));
    if (board->board == NULL) {
        printf("Error allocating memory");
        logError("Error allocating memory");
        return ERROR;
    }
    for (int i = 0; i < board->xSize; ++i) {
        board->board[i] = malloc(board->ySize * sizeof(BLOCK));
        if (board->board[i] == NULL) {
            printf("Error allocating memory");
            logError("Error allocating memory");
            return ERROR;
        }
    }

    return PASS;
}

int populateBoardWithEmptyBlocks(BOARD *board) {
    for (int i = 0; i < board->xSize; ++i) {
        for (int j = 0; j < board->ySize; ++j) {
            BLOCK block;
            block.blockType = EMPTY;
            block.x = i;
            block.y = j;
            board->board[i][j] = block;
        }
    }
    return PASS;
}

void addWallsToBoard(BOARD *board) {
    for (int i = 0; i < board->xSize; ++i) {
        board->board[0][i].blockType = WALL;
        board->board[board->ySize - 1][i].blockType = WALL;

        printBlock(&board->board[0][i]);
        printBlock(&board->board[board->ySize - 1][i]);
        usleep(SPEED * 10);
    }

    // Start at 1 pga the top wall already been placed, same with the end condition
    for (int i = 1; i < board->ySize; ++i) {
        board->board[i][0].blockType = WALL;
        board->board[i][board->xSize - 1].blockType = WALL;

        printBlock(&board->board[i][0]);
        printBlock(&board->board[i][board->xSize - 1]);
        usleep(SPEED * 50);
    }
}

void creatingSnake(ARRAYLIST *snake, BOARD *board) {
    snake->size = INITIAL_SNAKE_LENGTH;
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i) {
        BLOCK *block = &board->board[INITIAL_SNAKE_XPOSITION][INITIAL_SNAKE_YPOSITION + INITIAL_SNAKE_LENGTH - i];
        if (i == 0) {
            block->blockType = SNAKEHEAD;
        } else if (i == INITIAL_SNAKE_LENGTH - 1) {
            block->blockType = SNAKETAIL;
        } else {
            block->blockType = SNAKEBODY;
        }
        snake->blocks[i] = block;
        printBlock(block);
        usleep(SPEED * 500);
    }
}
