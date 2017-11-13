#pragma once
#include <array>
#include <iostream>

#include "card.h"
#include "defines.h"

class table {
public:
    table(const suit& trump) : m_count(0), m_trump(&trump) {};
    ~table() = default;

    void add(const card& played_card);
    void clear();

    uint8_t count() const;
    bool follows_suit(const card& card) const;
    uint8_t winning() const;

    const card& operator[](uint8_t index) const;
    std::array<card, 4>::iterator begin() { return m_data.begin(); }
    std::array<card, 4>::const_iterator begin() const { return m_data.begin(); }
    std::array<card, 4>::const_iterator cbegin() const { return m_data.cbegin(); }
    std::array<card, 4>::iterator end() { return m_data.begin() + m_count; }
    std::array<card, 4>::const_iterator end() const { return m_data.begin() + m_count; }
    std::array<card, 4>::const_iterator cend() const { return m_data.cbegin() + m_count; }

    friend std::ostream& operator<<(std::ostream& stream, const table& table);
private:
    std::array<card, 4> m_data;
    uint8_t m_count;
    const suit *m_trump;
    uint8_t m_winning;
};