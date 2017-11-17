#include <iostream>

#include "game.h"

#if DEBUG
    #define display(x) std::cout << x << "\n"
    #define display_no_new_line(x) std::cout << x
    #define display_division(j) std::cout << "=============================================\n"
#else
    #define display(x)
    #define display_no_new_line(x)
    #define display_division(j)
#endif

game::game() : m_players(m_deck), m_state(m_players.get_winner()) {};

bool game::ongoing() {
    return (m_tree.max_score() < 101 && m_tree.rounds() < 50);
};

void game::play() {
    do {
        display("==========================================================\n _   _ ________          __  _    _          _   _ _____  \n| \\ | |  ____\\ \\        / / | |  | |   /\\   | \\ | |  __ \\ \n|  \\| | |__   \\ \\  /\\  / /  | |__| |  /  \\  |  \\| | |  | |\n| . ` |  __|   \\ \\/  \\/ /   |  __  | / /\\ \\ | . ` | |  | |\n| |\\  | |____   \\  /\\  /    | |  | |/ ____ \\| |\\  | |__| |\n|_| \\_|______|   \\/  \\/     |_|  |_/_/    \\_\\_| \\_|_____/ \n==========================================================");
        m_deck.shuffle();
        m_players.reset();

        m_state.set_trump(m_players[3].choose_trump());
        if (m_players[0].will_tap(m_state.trump()) || m_players[2].will_tap(m_state.trump())) {
            m_tree.up_multiplier();
            if (m_players[1].will_retap(m_state.trump()) || m_players[3].will_retap(m_state.trump())) {
                m_tree.up_multiplier();
            }
        }
        display(m_state.trump());
        display_no_new_line("multiplier: ");
        display(m_tree.multiplier());

        for (uint8_t i = 0; i < 8; i++) {
            for (uint8_t j = 0; j < 4; j++) {
                display(m_players[j]);
                m_state.add(m_players[j].make_move(m_state));
                display(m_state.get_table());
                display(m_state.get_cheat_sheet().print((m_state.get_table().player_offset + j) % 4));
                display_division(j);
            }
            m_tree.add(m_players.get_team(m_state.get_table().winning()), m_state.get_table().score());
            m_players.set_winner(m_state.get_table().winning());
            m_state.clear_table();
        }
        m_tree.finish_hand();
        m_state.clear_hand();
    } while (this->ongoing());
    display("========================================================================\n ______ _____ _   _          _         _____  _____ ____  _____  ______ \n|  ____|_   _| \\ | |   /\\   | |       / ____|/ ____/ __ \\|  __ \\|  ____|\n| |__    | | |  \\| |  /  \\  | |      | (___ | |   | |  | | |__) | |__   \n|  __|   | | | . ` | / /\\ \\ | |       \\___ \\| |   | |  | |  _  /|  __|  \n| |     _| |_| |\\  |/ ____ \\| |____   ____) | |___| |__| | | \\ \\| |____ \n|_|    |_____|_| \\_/_/    \\_\\______| |_____/ \\_____\\____/|_|  \\_\\______|\n========================================================================");
    display(m_tree);
};