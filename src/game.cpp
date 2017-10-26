#include "game.h"

game::game() : m_players(m_deck) {};

bool game::ongoing() {
    static bool running = false;
    running = !running;
    return running;
};

void game::play() {
    while (this->ongoing()) {
        m_deck.shuffle();

        m_state.trump = m_players[0].choose_trump();
        for (uint8_t i = 0; i < 8; i++) {
            for (uint8_t j = 0; j < 4; m_state.table.add(m_players[1 + j++].make_move(m_state)));
            m_state.table.clear();
        }
    }
};