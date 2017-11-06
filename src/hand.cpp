#include <algorithm>
#include <stdexcept>

#include "hand.h"

hand::hand(card *data) : 
                    m_data(data),
                    m_count(8) {};

const uint8_t hand::count() const { return m_count; };
/*const unsigned int hand::value(const suit& s) const {
    unsigned int result = 0;
    for (uint8_t i = 0; i < m_count; i++) {
        if (m_data[i].suit == s) {
            switch (m_data[i].rank) {
            case rank::seven:
            case rank::eight:
            case rank::nine:
                break;

            case rank::jack:
                result += 1;
            case rank::queen:
                result += 1;
            case rank::king:
                result += 1;
            case rank::ace:
                result += 1;
            case rank::manille:
                result += 1;
                break;
            }
        }
    }
    return result;
}
const unsigned int hand::value_special() const {
    unsigned int result = 0;
    for (uint8_t i = 0; i < m_count; i++) {

    }
    return result;
}*/
bool hand::has_suit(suit suit_to_have) const {
    for (auto& card : *this) {
        if (card.suit == suit_to_have)
            return true;
    }
    return false;
}
bool hand::has_higher(card& baseline_card) const {
    for (auto& card : *this) {
        if (card > baseline_card)
            return true;
    }
    return false;
}
const card& hand::remove_at_index(uint8_t index) {
    std::swap(m_data[index], m_data[--m_count]);
    return m_data[m_count];
}
const card& hand::operator[](uint8_t index) const {
    if (index < m_count)
        return m_data[index];
    else
        throw std::out_of_range("Trying to access index out of range.");
}