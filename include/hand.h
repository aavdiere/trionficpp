#pragma once
#include "defines.h"
#include "card.h"

class hand {
public:
    hand(card * const data);

    uint8_t count();
    const card& remove_at_index(uint8_t index);
    const card& operator[](uint8_t index);
private:
    card * const m_data;
    uint8_t m_count;
};