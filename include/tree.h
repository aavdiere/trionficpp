#pragma once
#include <array>

#include "defines.h"
#include "models.h"

class tree {
public:
    std::array<uint8_t, 2> score;
    uint8_t rounds;

    tree() : score{0, 0}, rounds(0) {};

    void clear() {
        score = { 0, 0 };
        rounds = 0;
    }

    void add(team team, uint8_t new_score) {
        rounds++;
        score[static_cast<uint8_t>(team)] += new_score;
    }
};