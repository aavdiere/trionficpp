#pragma once
#include <array>

#include "player.h"
#include "state.h"
#include "tree.h"
#include "deck.h"

class game {
public:
    game();

    void play();
private:
    std::array<player, 4> m_players;
    state m_state;
    tree m_tree;
    deck m_deck;

    bool ongoing();
    void shuffle_cards();
};