#include "../include/main.h"
#include "../include/game.h"


int main(int argc, char *argv[]) {
    int iStatus = 0;

    if (argc > 1) {
        printf("No arguments for this project");
        return 0;
    }

    iStatus = game();
    if (iStatus != 0) {
        printf("Error: %d\n", iStatus);
        return iStatus;
    }

    return 0;
}
