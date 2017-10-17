#include "player.h"

player::player(card * const cards) : m_hand(cards) {

}

suit player::choose_trump() const {
    return suit::hearts;
}

const card& player::make_move(const state& current_state) {
    return m_hand.remove_at_index(0);
}