#pragma once
#include <array>

#include "players.h"
#include "state.h"
#include "tree.h"
#include "deck.h"

class game {
public:
    game();

    void play();
private:
    deck m_deck;
    players m_players;
    state m_state;
    tree m_tree;

    bool ongoing();
};