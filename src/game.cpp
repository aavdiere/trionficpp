#include "game.h"

game::game() : m_players({ player(m_deck.first()), player(m_deck.second()), player(m_deck.third()), player(m_deck.fourth()) }) {
    
};

bool game::ongoing() {
    return false;
};

void game::play() {
    while (this->ongoing()) {
        // this->shuffle_cards();

        // this->state.trump = this->players[ this->state.player_map[3] ].choose_trump();

        for (uint8_t i = 0; i < 8; i++) {
            // this->players[ this->state.player_map[0] ].make_move(this->state);
        }
    }
};