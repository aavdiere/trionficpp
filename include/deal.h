#pragma once
#include "defines.h"
#include "trick.h"

struct Deal {
    trick tricks[8];
    uint8_t score : 7;
    uint8_t group : 1;
};