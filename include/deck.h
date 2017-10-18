#pragma once
#include <array>
#include <random>

#include "defines.h"
#include "card.h"

class deck {
public:
    deck();

    void shuffle();
    card * const first_hand();
    card * const second_hand();
    card * const third_hand();
    card * const fourth_hand();
private:
    std::array<card, 32> m_data;
    std::mt19937 m_generator;
};