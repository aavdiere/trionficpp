#pragma once
#include <array>

#include "player.h"
#include "deck.h"

class players {
public:
    players(deck& carddeck);

    void set_winner(uint8_t winner) { m_winner = (m_winner + winner) % 4; }

    player& operator[](uint8_t index);
private:
    std::array<player, 4> m_players;
    uint8_t m_winner;
};