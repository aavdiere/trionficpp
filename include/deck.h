#pragma once
#include <array>
#include <random>

#include "defines.h"
#include "card.h"

class deck {
public:
    deck();

    void shuffle();
    card * const first();
    card * const second();
    card * const third();
    card * const fourth();
private:
    std::array<card, 32> m_data;
    std::mt19937 m_generator;
};