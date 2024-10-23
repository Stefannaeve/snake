#include "../include/main.h"


void forLoop(int rows, int cols, int total, char character);
void enterUserName();

int introScreen() {
    int row, col;
    int pixelCount;
    int finishedRows = 0, finishedColumns = 0, currentPrints = 0;
    char *snake = "S N A K E   ~~~:";

    int howManyRowsTop = 0;
    int howManyColumnsLeft = 0;
    int howManyColumnsRight = 0;
    int howManyRowsBottom = 0;
    int howManyRowsTopAndBottom = 0;

    bool rowsDevisable;
    bool colsDevisable;

    getmaxyx(stdscr, row, col);
    pixelCount = row * col;
    char character = ':';
    char sideCharacter = '-';
    int status = 0;
    while (1) {
        if (((row / 4) * 3 < finishedRows || (col / 4) * 3 < finishedColumns) && (!(finishedColumns % 2) && !(finishedRows % 2))) {
            usleep(30000);
            refresh();
            mvprintw(row / 2, (col - strlen(snake)) / 2, "%s", snake);
            break;
        }

        if (finishedRows == 0) {
            attron(COLOR_PAIR(1));
            for (int i = 0; i < col - finishedColumns; ++i) {
                mvaddch(0, i, character);
                refresh();
                usleep(2000);
            }
            finishedRows++;
        }
        if (finishedColumns == 0) {
            attron(COLOR_PAIR(2));
            for (int i = 0; i < row - finishedRows; ++i) {
                mvaddch(i+1, col-1, sideCharacter);
                refresh();
                usleep(10000);
            }
            finishedColumns++;
        }

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
                usleep(2000);
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
                usleep(10000);
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
                usleep(2000);
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
                usleep(10000);
            }
            finishedColumns++;
        }
    }

    getch();

    enterUserName();

    endwin();

    return 0;
}

void forLoop(int rows, int cols, int total, char character) {
    for (int i = 0; i < total; i++) {
        mvaddch(rows, cols, character);
        refresh();
    }
}

void enterUserName() {

    int row, col;

    getmaxyx(stdscr, row, col);
    echo();

    char mesg[] = "Enter your username: ";
    char str[10];

    mvprintw(row / 2, (col - strlen(mesg)) / 2, "%s", mesg);
    getnstr(str, 10);
    mvprintw(row / 2+2, (col - strlen(str)) / 2, "Username: %s", str);
    getch();
    endwin();

}
