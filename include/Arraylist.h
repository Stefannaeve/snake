#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "block.h"

#define INITIAL_SIZE 8

typedef struct _ARRAYLIST {
    int capacity;
    int size;
    BLOCK **blocks;
} ARRAYLIST;

void createList();
void addBlock(ARRAYLIST *arraylist, BLOCK *block);

#endif //ARRAYLIST_H
