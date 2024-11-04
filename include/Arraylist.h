#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "main.h"

#define INITIAL_SIZE 8

typedef struct _NODE {
    int positionParentNodeX;
    int positionParentNodeY;
    int positionX;
    int positionY;
} NODE;

typedef struct _ARRAYLIST {
    int capacity;
    int size;
    BLOCK **blocks;
} ARRAYLIST;

ARRAYLIST createList();
void addBlock(ARRAYLIST *arraylist, BLOCK *block);

#endif //ARRAYLIST_H
