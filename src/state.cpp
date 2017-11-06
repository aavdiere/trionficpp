#include "state.h"

state::state() : trump(suit::undefined), table(trump) {}

bool state::valid_move(const card& possible_move, const hand& hand) const {
    if (this->table.count() == 0) {
        return true;
    } else {
        if (!this->table.follows_suit(possible_move)) {
            if (hand.has_suit(this->table[0].suit))
                return false;
            if (this->trump != suit::none) {
                if (hand.has_suit(this->trump)) {
                    return true; // temp
                } else {
                    return true;
                }
            }
            return true;
        } else {
            return true; // temp
        }
    }
}