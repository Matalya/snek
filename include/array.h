#pragma once
#include <stddef.h>
#include "maybe.h"
#define NO_FUCK_YOU NULL

typedef struct {
    size_t size;
    int* address;
} Array;

//Initializes array
Array createArray();
int index_overflows(Array array, size_t index);
MaybeInt tryGetElement(Array array, size_t index);

//Fetch an element from index
int getElement(Array array, size_t index);

//Overwrite element at index
int setElement(Array array, size_t index, int value);
void resizeArray(Array* array, size_t size);

//Add element to tail
int addElement(Array* array, int element);

//Add element to index and move everything to the right one space over
int shoveElement(Array* array, size_t index, int element);

//Remove element(s) from tail
int popElement(Array array, size_t amount);

//Remove element from index, everything falls back into place
int removeElement(Array array, size_t index);
MaybeSize_t tryFindElement(Array array, int value);

//Return the instance of the value
size_t findElement(Array array, int value);
Array cloneArray(Array array);
void resetArray(Array array);
void printArray(Array array);