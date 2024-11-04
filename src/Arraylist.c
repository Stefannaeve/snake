#include "../include/Arraylist.h"

#include <stdlib.h>

ARRAYLIST createList() {
    ARRAYLIST arraylist;
    arraylist.capacity = INITIAL_SIZE;
    arraylist.size = 0;
    arraylist.blocks = calloc(INITIAL_SIZE, sizeof(BLOCK));
    return arraylist;
}

void addBlock(ARRAYLIST *arraylist, BLOCK *block) {
    if (arraylist->size < arraylist->capacity) {
        arraylist->blocks[arraylist->size] = block;
        arraylist->size++;
    } else {
        BLOCK **newArray = calloc(arraylist->capacity*2, sizeof(BLOCK));
        arraylist->capacity = arraylist->capacity*2;
        for (int i = 0; i < arraylist->size; ++i) {
            newArray[i] = arraylist->blocks[i];
        }
        newArray[arraylist->size] = block;
        arraylist->size++;

        free(arraylist->blocks);
        arraylist->blocks = newArray;
    }
}