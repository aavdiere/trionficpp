#include "hand.h"

#include <algorithm>

hand::hand(card *data) : m_data(data), m_count(8) {};

uint8_t hand::count() { return m_count; };

card& remove_at_index(uint8_t index) {
    std::swap(data[index], data[--m_count]);
    return data[m_count];
}