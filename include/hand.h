#pragma once
#include <array>

#include "card.h"
#include "defines.h"

class hand {
public:
    hand(card *data);
    hand(card *data, uint8_t count);

    void reset();

    const uint8_t count() const;
    bool has_suit(suit suit_to_have) const;
    bool has_higher(const card& baseline_card) const;
    bool has_other(suit suit_to_not_have) const;
    const card& remove_at_index(uint8_t index);
    /*const unsigned int value(const suit& s) const;
    const unsigned int value_special(const suit& s) const;*/

    const card& operator[](uint8_t index) const;
    std::array<card, 8>::iterator begin() { return std::array<card, 8>::iterator(m_data); }
    std::array<card, 8>::const_iterator begin() const { return std::array<card, 8>::const_iterator(m_data); }
    std::array<card, 8>::const_iterator cbegin() const { return std::array<card, 8>::const_iterator(m_data); }
    std::array<card, 8>::iterator end() { return std::array<card, 8>::iterator(m_data + m_count); }
    std::array<card, 8>::const_iterator end() const { return std::array<card, 8>::const_iterator(m_data + m_count); }
    std::array<card, 8>::const_iterator cend() const { return std::array<card, 8>::const_iterator(m_data + m_count); }
private:
    card *m_data;
    uint8_t m_count;
    uint8_t m_init_count;
};