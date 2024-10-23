#ifndef ARRAYLIST_H
#define ARRAYLIST_H

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
    NODE *nodes;
} ARRAYLIST;

ARRAYLIST createList();
void addBlock(ARRAYLIST *arraylist, NODE *block);

#endif //ARRAYLIST_H
