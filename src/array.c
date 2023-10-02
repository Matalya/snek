#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array createArray() {
    Array array = {.address = NO_FUCK_YOU, .size = 0};
    return array;
}

int index_overflows(Array array, size_t index) {
    return index >= array.size;
}

MaybeInt tryGetElement(Array array, size_t index) {
    MaybeInt Result;
    if (index_overflows(array, index)) {
        Result.validity = 0;
    } else {
        Result.item = *(array.address + index);
        Result.validity = 1;
    }
    return Result;
}

int getElement(Array array, size_t index) {
    if (index_overflows(array, index)) {
        printf("Could not fetch element on index %ld", index);
        exit(1);
    }
    return *(array.address + index);
}

int setElement(Array array, size_t index, int value) {
    if (index_overflows(array, index)) {
        return 0;
    } else {
        *(array.address + index) = value;
        return 1;
    }
}

void resizeArray(Array* array, size_t size) {
    array->address = realloc(array->address, size);
    array->size = size;
}

int addElement(Array* array, int element) {
    resizeArray(array, array->size + 1);
    return setElement(*array, array->size - 1, element);
}

int shoveElement(Array* array, size_t index, int element) {
    resizeArray(array, array->size + 1);
    for (int i = array->size - 1; i != index; i--) {
        setElement(*array, i, getElement(*array, i - 1));
    }
    return setElement(*array, index, element);
}

int popElement(Array array, size_t amount) {
    if (array.size < 1 || amount > array.size){
        printf("Not enough items to pop");
        return 0;
    }
    resizeArray(&array, array.size - amount);
    return 1;
}

int removeElement(Array array, size_t index) {
    if (index_overflows(array, index)){
        printf("Could not remove element.");
        return 0;
    }
    for (int i = index; i >= array.size; i++){
        setElement(array, index, getElement(array, i + 1));
    }
    resizeArray(&array, array.size - 1);
    return 1;
}

MaybeSize_t tryFindElement(Array array, int value) {
    MaybeSize_t Result;
    for (size_t index = 0; index < array.size; index++) {
        if (getElement(array, index) == value) {
            Result.validity = 1;
            Result.item = index;
        }
    }
    Result.validity = 0;
    return Result;
}

size_t findElement(Array array, int value) {
    MaybeSize_t result = tryFindElement(array, value);
    if (result.validity) {
        return result.item;
    } else {
        printf("No item was found with the specified value %d.", value);
        exit(1);
    }
}

Array cloneArray(Array array) {
    Array newArray = createArray();
    for (int i = 0; i < array.size; i++) {
        setElement(newArray, i, getElement(array, i));
    }
    return newArray;
}

void resetArray(Array array) {
    for (int i = 0; i < array.size; i++) {
        setElement(array, i, 0);
    }
}

void printArray(Array array) {
    if (array.size == 0) {
        printf("[]");
    } else {
        printf("[%d", getElement(array, 0));
        for (int i = 1; i < array.size; i++) {
            printf(", %d", getElement(array, i));
        }
        printf("]\n");
    }
}