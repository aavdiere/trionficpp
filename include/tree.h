#pragma once
#include <array>
#include <iostream>

#include "defines.h"
#include "models.h"

class tree {
public:
    tree();

    void clear();
    void finish_hand();
    void add(team team, uint8_t score);
    void up_multiplier();

    uint8_t multiplier() const;
    uint8_t rounds() const;
    uint8_t max_score() const;

    friend std::ostream& operator<<(std::ostream& stream, tree& tree);
private:
    std::array<uint8_t, 2> m_score, m_hand_score;
    uint8_t m_rounds;
    uint8_t m_multiplier;
};