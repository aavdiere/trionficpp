#pragma once
#include "card.h"
#include "defines.h"

class hand {
public:
    hand(card *data);

    const uint8_t count() const;
    const card& remove_at_index(uint8_t index);
    /*const unsigned int value(const suit& s) const;
    const unsigned int value_special(const suit& s) const;*/

    const card& operator[](uint8_t index) const;
private:
    card *m_data;
    uint8_t m_count;
};