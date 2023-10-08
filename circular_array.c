#include <stdio.h>
#include "circular_array.h"

bool is_circ_full(Circle* circle) {
    return circle->head == (circle->tail + 1) % circle->capacity;
}

//All empty circles are initialized with head and tail = -1.
bool is_circ_empty(Circle* circle) {
    return circle->head == -1;
}

//Initializes a circle and returns a pointer to it.
Circle* initCircle(size_t size) {
    Circle* circle = malloc(sizeof(Circle));
    circle->array = malloc(sizeof(coords) * size);
    circle->head = circle->tail = -1;
    circle->capacity = size;
    circle->length = 0;
    return circle;
}

//Prints the contents together with markers for head and tail.
void printCircle(Circle* circle) {
    int cap = circle->capacity;
    coords* array = circle->array;
    int head = circle->head;
    int tail = circle->tail;
    printf("[");
    for (int i = 0; i < cap; i++) {
        if (is_circ_empty(circle)) {
            break;
        }
        if (i == head) {
            printf("<");
        }
        printf("%d, %d", array[i].x, array[i].y);
        if (i == tail) {
            printf(">");
        }
        if (i + 1 < cap) {
            printf(", ");
        }
    }
    printf("]\n");
}

//Specialized function that doubles the size of the circle.
//
//Returns a pointer to a new array and frees the old one.
Circle* doubleCircleCapacity(Circle* circle) {
    Circle* newCircle = initCircle(circle->capacity * 2);

    if (!is_circ_empty(circle)) {
        int copyFrom = circle->head;
        int copyTo = 0;

        do {
            newCircle->array[copyTo++] = circle->array[copyFrom];
            copyFrom = (copyFrom + 1) % circle->capacity;
        } while (copyFrom != circle->head);

        newCircle->head = 0;
        newCircle->tail = circle->capacity - 1;
    }

    free(circle);
    return newCircle;
}

//Restarts the array of the circle be freeing it and
//
//reallocating it somewhere else, while setting head
//
//and tail to -1 to signify that the array is empty.
void nukeCircle(Circle* circle) {
    free(circle->array);
    circle->array = malloc(sizeof(int));
    circle->head = circle->tail = -1;
    circle->length = 0;
}

//Restarts the function by setting head and tail to -1
//
//to signify that it's empty and allow enqueues to
//
//overwrite it.
void emptyCircle(Circle* circle) {
    circle->head = circle->tail = -1;
    circle->length = 0;
}

//Adds an item according to the FIFO principle.
//
//If full, the circle is replaced for one double its size
//
//And returned back.
Circle* enqueueItemSafe(Circle* circle, coords value) {
    if (is_circ_full(circle)) {
        circle = doubleCircleCapacity(circle);
    } else if (is_circ_empty(circle)) {
        circle->head++;
    }
    circle->tail = (circle->tail + 1) % circle->capacity;
    circle->array[circle->tail] = value;
    circle->length++;
    return circle;
}

//Adds an item according to the FIFO principle.
//
//If full, it'll simply overwrite the last item.
void enqueueItem(Circle* circle, coords value) {
    if (is_circ_full(circle) || is_circ_empty(circle)) {
        circle->head++;
    }
    circle->tail = (circle->tail + 1) % circle->capacity;
    circle->array[circle->tail] = value;
    circle->length++;
}

//Returns the first element of the circle. Contains no
//
//error handling.
coords peekCircle(Circle* circle) {
    return circle->array[circle->head];
}


//Eliminates an item according to the FIFO
//
//principle. Returns a 0 if failure, 1 if success.
bool dequeueItem(Circle* circle) {
    if (is_circ_empty(circle)) {
        return false;
    }
    if (circle->head == circle->tail) {
        emptyCircle(circle);
    } else {
        circle->head = (circle->head + 1) % circle->capacity;
        circle->length--;
    }
    return true;
}
//Sister function to dequeue item. It returns the dequeued
//
//item. Has no error handling cuz I can't be bothered anymore.
coords ripLastItemOff(Circle* circle) {
    coords item = circle->array[circle->head];
    circle->head = (circle->head + 1) % circle->capacity;
    circle->length--;
    return item;
}

//Raw print array function. Prints the content of the allocation.
void printArray(Circle* circle) {
    printf("[");
    for (int i = 0; i < circle->capacity; i++) {
        printf("%d, %d", circle->array[i].x, circle->array[i].y);
        if (i < circle->capacity - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

//Sister function to peekCircle(). Prints the tail with its index.
void printTail(Circle* circle) {
    coords item = circle->array[circle->tail];
    int x = item.x;
    int y = item.y;
    printf("%d: %d, %c", circle->tail, x, y);
}