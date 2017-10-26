#pragma once
#include <array>
#include <random>

#include "card.h"
#include "defines.h"

class deck {
public:
    static std::mt19937 generator;
    static bool generator_is_set;

    deck();

    void shuffle();
    card *first_hand();
    card *second_hand();
    card *third_hand();
    card *fourth_hand();
private:
    std::array<card, 32> m_data;
};