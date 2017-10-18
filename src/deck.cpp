#include "deck.h"

#include <algorithm>

deck::deck() {
    std::random_device rd;
    std::mt19937 g(rd());
    m_generator = std::move(g);

    for (uint8_t i = 0; i < 4; i++)
        for (uint8_t j = 0; j < 8; j++)
            m_data[i * 8 + j] = card(static_cast<suit>(i), 
                                     static_cast<rank>(j));
    std::shuffle(m_data.begin(), m_data.end(), m_generator);
};

void deck::shuffle() {
    std::shuffle(m_data.begin(), m_data.end(), m_generator);
};

card * const deck::first_hand() {
    return &m_data[0];
};
card * const deck::second_hand() {
    return &m_data[8];
};
card * const deck::third_hand() {
    return &m_data[16];
};
card * const deck::fourth_hand() {
    return &m_data[24];
};