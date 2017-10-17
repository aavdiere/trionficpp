#include "deck.h"

#include <algorithm>

deck::deck() {
    for (uint8_t i = 0; i < 4; i++)
        for (uint8_t j = 0; j < 8; j++)
            m_data[i * 8 + j] = card(static_cast<suit>(i), 
                                     static_cast<rank>(j));
    std::shuffle(m_data.begin(), m_data.end());
}

void deck::shuffle() {
    std::shuffle(m_data.begin(), m_data.end());
}