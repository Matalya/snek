#include <stddef.h>
#include "maybe.h"

MaybeInt some_int(int integer) {
    MaybeInt maybeInt = {
        .item = integer,
        .validity = 1
    };
    return maybeInt;
}

MaybeInt none_int() {
    MaybeInt maybeInt = {
        .item = 0,
        .validity = 0
    };
    return maybeInt;
}

MaybeSize_t some_size_t(size_t size) {
    MaybeSize_t maybeSizeT = {
        .item = size,
        .validity = 1
    };
    return maybeSizeT;
}

MaybeSize_t none_size_t() {
    MaybeSize_t maybeSizeT = {
        .item = 0,
        .validity = 0
    };
    return maybeSizeT;
}