#include "players.h"

players::players(deck& carddeck) : m_players({
                                        player(carddeck.first_hand()),
                                        player(carddeck.second_hand()),
                                        player(carddeck.third_hand()),
                                        player(carddeck.fourth_hand())
                                    }),
                                    m_winner(1) {}
void players::set_winner(uint8_t winner) {
    m_winner = (m_winner + winner) % 4;
}
void players::reset() {
    for (auto& player : m_players) {
        player.reset_cards();
    }
}
const uint8_t& players::get_winner() const {
    return m_winner;
}
team players::get_team(uint8_t winner) const {
    return team((m_winner + winner) % 2);
}
player& players::operator[](uint8_t index) {
    return m_players[(m_winner + index) % 4];
}