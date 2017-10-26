#include <algorithm>

#include "deck.h"

bool deck::generator_is_set = false;
std::mt19937 deck::generator;

deck::deck() {
    if (!generator_is_set) {
        std::random_device rd;
        std::mt19937 g(rd());
        generator = std::move(g);
    }

    for (uint8_t i = 0; i < 4; i++)
        for (uint8_t j = 0; j < 8; j++)
            m_data[i * 8 + j] = card(static_cast<suit>(i), 
                                     static_cast<rank>(j));
    std::shuffle(m_data.begin(), m_data.end(), generator);
};

void deck::shuffle() {
    std::shuffle(m_data.begin(), m_data.end(), generator);
};

card *deck::first_hand() {
    return &m_data[0];
};
card *deck::second_hand() {
    return &m_data[8];
};
card *deck::third_hand() {
    return &m_data[16];
};
card *deck::fourth_hand() {
    return &m_data[24];
};