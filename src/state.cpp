#include "state.h"

state::state() : trump(suit::undefined) {}

bool state::valid_move(const card& possible_move, const hand& hand) const {
    if (table.count() == 0) {
        return true;
    } else {
        if (!table.follows_suit(possible_move)) {
            
        }
    }
}