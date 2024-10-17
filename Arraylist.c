#include "Arraylist.h"

#include <stdlib.h>

ARRAYLIST createList() {
    ARRAYLIST arraylist;
    arraylist.capacity = INITIAL_SIZE;
    arraylist.size = 0;
    arraylist.nodes = calloc(INITIAL_SIZE, sizeof(NODE));
    return arraylist;
}

void addBlock(ARRAYLIST *arraylist, NODE *block) {
    if (arraylist->size < arraylist->capacity) {
        arraylist->nodes[arraylist->size] = *block;
        arraylist->size++;
    } else {
        NODE *newArray = calloc(arraylist->capacity*2, sizeof(NODE));
        arraylist->capacity = arraylist->capacity*2;
        for (int i = 0; i < arraylist->size; ++i) {
            newArray[i] = arraylist->nodes[i];
        }
        newArray[arraylist->size] = *block;
        arraylist->size++;

        free(arraylist->nodes);
        arraylist->nodes = newArray;
    }
}