#pragma once
#include <array>

#include "card.h"
#include "defines.h"

class table {
public:
    table() : m_count(0) {};
    ~table() = default;

    void add(const card& played_card);
    void clear();

    uint8_t count() const;

    const card& operator[](uint8_t index) const;
private:
    std::array<card, 4> m_data;
    uint8_t m_count;
};