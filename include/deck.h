#pragma once
#include <array>

#include "defines.h"
#include "card.h"

class deck {
public:
    deck();

    void shuffle();
private:
    std::array<card, 32> m_data;
};