#pragma once
#include <array>

#include "models.h"
#include "player.h"
#include "deck.h"

class players {
public:
    players(deck& carddeck);

    void set_winner(uint8_t winner);
    void reset();

    team get_team(uint8_t winner) const;
    const uint8_t& get_winner() const;
    
    player& operator[](uint8_t index);
private:
    std::array<player, 4> m_players;
    uint8_t m_winner;
};