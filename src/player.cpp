#include <random>

#include "player.h"
#include "deck.h"

player::player(card *cards) : m_hand(cards) {}

suit player::choose_trump() const {
    std::uniform_int_distribution<> dis(0, 3);

    if (!deck::generator_is_set) {
        std::random_device rd;
        std::mt19937 g(rd());
        deck::generator = std::move(g);
    }

    return suit(static_cast<suit>(dis(deck::generator)));
}

const card& player::make_move(const state& current_state) {
    for (uint8_t i = 0; i < m_hand.count(); i++) {
        if (current_state.valid_move(m_hand[i], m_hand)) {
            return m_hand.remove_at_index(i);
        }
    }
    throw std::range_error("No valid move possible, this should not happen.");
}