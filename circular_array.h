#pragma once
#include <stdlib.h>
#include <stdbool.h>

//Coordinates type
typedef struct {
    int x;
    int y;
} coords;

//Contains a head and tail int, a size_t length
//
//and a pointer to a (heap-assumed) array.
typedef struct {
    coords* array;
    int head;
    int tail;
    size_t capacity;
    size_t length;
} Circle;

//Converts a given index to a wrapable index.
size_t circIndex(Circle* circle, size_t index);

//When a circle is full, that means that items have
//
//been added until the tail came right by the head.
bool is_circ_full(Circle* circle);

//All empty circles are initialized with head and tail = -1.
bool is_circ_empty(Circle* circle);

//Initializes a circle and returns a pointer to it.
Circle* initCircle(size_t size);

//Prints the contents together with markers for head and tail.
void printCircle(Circle* circle);

//Specialized function that doubles the size of the circle.
//
//Returns a pointer to a new array and frees the old one.
Circle* doubleCircleCapacity(Circle* circle);

//Restarts the array of the circle be freeing it and
//
//reallocating it somewhere else, while setting head
//
//and tail to -1 to signify that the array is empty.
void nukeCircle(Circle* circle);

//Restarts the function by setting head and tail to -1
//
//to signify that it's empty and allow enqueues to
//
//overwrite it.
void emptyCircle(Circle* circle);

//Adds an item according to the FIFO principle.
//
//If full, the circle is replaced for one double its size
//
//And returned back.
Circle* enqueueItemSafe(Circle* circle, coords value);

//Adds an item according to the FIFO principle.
//
//If full, it'll simply overwrite the last item.
void enqueueItem(Circle* circle, coords value);

//Returns the first element of the circle. Contains no
//
//error handling.
coords peekCircle(Circle* circle);


//Eliminates an item according to the FIFO
//
//principle. Returns a 0 if failure, 1 if success.
bool dequeueItem(Circle* circle);
//Sister function to dequeue item. It returns the dequeued
//
//item. Has no error handling cuz I can't be bothered anymore.
coords ripLastItemOff(Circle* circle);

//Raw print array function. Prints the content of the allocation.
void printArray(Circle* circle);

//Sister function to peekCircle(). Prints the tail with its index.
void printTail(Circle* circle);