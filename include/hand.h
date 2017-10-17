#pragma once
#include "defines.h"
#include "card.h"

class hand {
public:
    hand(card *data);

    uint8_t count();
    card& remove_at_index(uint8_t index);
private:
    card *m_data;
    uint8_t m_count;
};