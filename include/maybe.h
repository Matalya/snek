#pragma once

#include <stddef.h>

typedef struct {
    int item;
    int validity;
} MaybeInt;

typedef struct {
    size_t item;
    int validity;
} MaybeSize_t;

MaybeInt some_int(int integer);

MaybeInt none_int();

MaybeSize_t some_size_t(size_t size);

MaybeSize_t none_size_t();