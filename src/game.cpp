#include <iostream>

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
        
        switch (m_state.trump) {
        case suit::clubs:
            std::cout << "trump: clubs" << "\n";
            break;
        case suit::diamonds:
            std::cout << "trump: diamonds" << "\n";
            break;
        case suit::hearts:
            std::cout << "trump: hearts" << "\n";
            break;
        case suit::spades:
            std::cout << "trump: spades" << "\n";
            break;
        case suit::none:
            std::cout << "trump: none" << "\n";
            break;
        default:
            throw std::range_error("Trump is undefined, this should not happen.");
            break;
        }

        for (uint8_t i = 0; i < 8; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                m_state.table.add(m_players[1 + j].make_move(m_state));
                std::cout << m_state.table << std::endl;
            }
            m_state.table.clear();
        }
    }
};