#include <iostream>

#include "game.h"

#if DEBUG
    #define display(x) std::cout << x << "\n"
#else
    #define display(x)
#endif

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
        if (m_players[1].will_tap(m_state.trump) || m_players[3].will_tap(m_state.trump)) {
            m_tree.up_multiplier();
            if (m_players[0].will_retap(m_state.trump) || m_players[2].will_retap(m_state.trump)) {
                m_tree.up_multiplier();
            }
        }
        display(m_state.trump);
        display("multiplier:");
        display(m_tree.multiplier());

        for (uint8_t i = 0; i < 8; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                display(m_players[1 + j]);
                m_state.table.add(m_players[1 + j].make_move(m_state));
                display(m_state.table);
                display("=============================================");
            }
            m_tree.add(m_players.get_team(m_state.table.winning()), m_state.table.score());
            m_players.set_winner(m_state.table.winning());
            m_state.table.clear();
        }
        m_tree.finish_hand();
        display(m_tree);
    }
};