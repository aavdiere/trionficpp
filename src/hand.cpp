#include "hand.h"

#include <algorithm>
#include <stdexcept>

hand::hand(card * const data) : m_data(data), m_count(8) {};

uint8_t hand::count() { return m_count; };

const card& hand::remove_at_index(uint8_t index) {
    std::swap(m_data[index], m_data[--m_count]);
    return m_data[m_count];
}

const card& hand::operator[](uint8_t index) {
    if (index < m_count)
        return m_data[index];
    else
        throw std::out_of_range("Trying to access index out of range.");
}