#pragma once
#include "models.h"
#include "table.h"
#include "card.h"
#include "hand.h"
#include "cheat_sheet.h"
#include "defines.h"

class state {
public:
    state(const uint8_t& player_offset);

    void add(const card& played_card);
    void set_trump(suit trump) { m_trump = trump; }
    void clear_table();

    suit trump() const { return m_trump; }
    const table& get_table() const { return m_table; }
    bool valid_move(const card& possible_move, const hand& hand) const;
private:
    suit m_trump;
    table m_table;
    cheat_sheet m_possible_cards;
};