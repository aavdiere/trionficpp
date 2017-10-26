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
    return m_hand.remove_at_index(0);
}