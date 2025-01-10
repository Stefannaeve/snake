#include "../include/game.h"
#include "../include/introScreen.h"
#include <string.h>

void enterUserName();

int introScreen() {
    int row, col;
    int pixelCount;
    int finishedRows = 0, finishedColumns = 0, currentPrints = 0;

    int howManyRowsTop = 0;
    int howManyColumnsLeft = 0;
    int howManyColumnsRight = 0;
    int howManyRowsBottom = 0;
    int howManyRowsTopAndBottom = 0;

    bool rowsDevisable;
    bool colsDevisable;

    getmaxyx(stdscr, row, col);
    char character = ':';
    char sideCharacter = '-';
    while (1) {
        // We hit the point in the beginning screen where we want to stop
        // row / 4 * 3 < finishedrows
            // row is the width of the screen
            // we divide it by 4 to find the quarter of the screen
            // we multiply that by three to find the position of the last quarter
            // we check if the position of the last quarter is less that the finished rows
                // If that is the case, we stop the program, as the while loop is entrenching upon the last quarter in the middle
        // col / 4 * 3 < finishedCols
            // same as row
        // !(finishedColumns % 2) && !(finishedRows % 2)
            // ensures that we are at the right iteration for the right position of rows and cols
        if (((row / 4) * 3 < finishedRows || (col / 4) * 3 < finishedColumns) && (!(finishedColumns % 2) && !(finishedRows % 2))) {
            usleep(30000);
            refresh();
            break;
        }

        // next two if statements is only for the beginning of the while loop
        if (finishedRows == 0) {
            attron(COLOR_PAIR(1));
            for (int i = 0; i < col - finishedColumns; ++i) {
                mvaddch(0, i, character);
                refresh();
                usleep(SPEED);
            }
            finishedRows++;
        }
        if (finishedColumns == 0) {
            attron(COLOR_PAIR(2));
            for (int i = 0; i < row - finishedRows; ++i) {
                mvaddch(i+1, col-1, sideCharacter);
                refresh();
                usleep(SPEED*5);
            }
            finishedColumns++;
        }

        // We update the rows devisable every if statement, to find the right modulo variable for the rows and cols
        rowsDevisable = finishedRows % 2;
        colsDevisable = finishedColumns % 2;

        // TOP
        if (!rowsDevisable && !colsDevisable) {
            howManyRowsTop = finishedRows / 2;
            howManyColumnsLeft = finishedColumns / 2;
            attron(COLOR_PAIR(1));

            for (int i = 0; i < col - finishedColumns; ++i) {
                mvaddch(howManyRowsTop, i+howManyColumnsLeft, character);
                refresh();
                usleep(SPEED);
            }
            finishedRows++;
        }

        rowsDevisable = finishedRows % 2;
        colsDevisable = finishedColumns % 2;

        // LEFT
        if (!rowsDevisable && colsDevisable) {
            howManyColumnsLeft = finishedColumns / 2;
            howManyRowsTopAndBottom = finishedRows / 2;
            attron(COLOR_PAIR(4));

            for (int i = row - howManyRowsTopAndBottom; i > howManyRowsTopAndBottom; --i) {
                mvaddch(i-1, howManyColumnsLeft, sideCharacter);
                refresh();
                usleep(SPEED*5);
            }
            finishedColumns++;
        }

        rowsDevisable = finishedRows % 2;
        colsDevisable = finishedColumns % 2;

        // BOTTOM
        if (rowsDevisable && colsDevisable) {
            howManyRowsBottom = finishedRows / 2;
            howManyColumnsLeft = finishedColumns / 2;
            howManyColumnsRight = finishedRows / 2 + 1;
            attron(COLOR_PAIR(3));

            for (int i = col - howManyColumnsRight; i > howManyColumnsLeft - 1; --i) {
                mvaddch(row-howManyRowsBottom-1, i, character);
                refresh();
                usleep(SPEED);
            }
            finishedRows++;
        }

        rowsDevisable = finishedRows % 2;
        colsDevisable = finishedColumns % 2;

        // RIGHT
        if (rowsDevisable && !colsDevisable) {
            howManyColumnsRight = finishedColumns / 2;
            howManyRowsTop = finishedRows / 2 + 1;
            attron(COLOR_PAIR(2));

            for (int i = 0; i < row - finishedRows; ++i) {
                mvaddch(i+howManyRowsTop, col-howManyColumnsRight-1, sideCharacter);
                refresh();
                usleep(SPEED*5);
            }
            finishedColumns++;
        }
    }

    enterUserName(finishedRows, finishedColumns);

    endwin();

    return 0;
}

void enterUserName() {

    int row, col, rowsDevisable, changeForCentering = 0;
    char askUserName[] = "Enter your username: ";
    char *title = "S N A K E   ";
    char titleWithSnake[17] = {0};
    char snakeBody[5];
    snakeBody[0] = SNAKE_TAIL;
    snakeBody[1] = SNAKE_BODY;
    snakeBody[2] = SNAKE_BODY;
    snakeBody[3] = SNAKE_HEAD;
    snakeBody[4] = '\0';
    strncpy(titleWithSnake, title, 12);
    strncat(titleWithSnake, snakeBody, 4);
    titleWithSnake[16] = '\0';
    char userName[10];

    getmaxyx(stdscr, row, col);

    rowsDevisable = row % 2;

    // Checks if the rows are devisable by two or not
    // This is to change the position to the upper part
    // of the middle of screen in the case of an even number
    if (!rowsDevisable) {
        changeForCentering = 1;
    }

    mvprintw(row / 2 - changeForCentering, (col - strlen(title)) / 2, "%s", titleWithSnake);

    getch();

    getmaxyx(stdscr, row, col);
    echo();

    int value = row / 2 -changeForCentering;

    mvprintw(row / 2 - changeForCentering, (col - strlen(askUserName)) / 2, "%s", askUserName);
    getnstr(userName, 10);
    mvprintw(row / 2+1 - changeForCentering, (col - strlen(userName)) / 2, "Username: %s", userName);
    getch();

}
