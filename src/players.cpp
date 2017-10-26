#include "players.h"

players::players(deck carddeck) : m_players({
                                        player(carddeck.first_hand()),
                                        player(carddeck.second_hand()),
                                        player(carddeck.third_hand()),
                                        player(carddeck.fourth_hand())
                                    }),
                                    m_winner(0) {}

player& players::operator[](uint8_t index) {
    return m_players[(m_winner + index) % 4];
}