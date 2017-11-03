#include "table.h"

void table::add(const card& played_card) {
    if (m_count < 4)
        m_data[m_count++] = played_card;
    else
        throw std::out_of_range("Tying to add more elements to the table than it can handle.");
}
void table::clear() {
    m_count = 0;
}
uint8_t table::count() const {
    return m_count;
}
bool table::follows_suit(const card& card) const {
    if (m_count == 0) return true;
    else return card.suit == m_data[0].suit;
}
const card& table::operator[](uint8_t index) const {
    if (index < m_count)
        return m_data[index];
    else
        throw std::out_of_range("Trying to access index out of range.");
}