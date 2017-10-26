#pragma once
#include "trick.h"
#include "defines.h"

struct Deal {
    trick tricks[8];
    uint8_t score : 7;
    uint8_t group : 1;
};