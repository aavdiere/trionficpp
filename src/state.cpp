#include "state.h"

state::state() : trump(suit::undefined), table(trump) {}

bool state::valid_move(const card& possible_move, const hand& hand) const {
    if (this->table.count() == 0) {
        // first player always makes valid move
        return true;
    } else {
        // other players don't necessarily make a valid move
        if (!this->table.follows_suit(possible_move)) {
            // didn't follow suit
            if (hand.has_suit(this->table[0].suit))
                return false;
            // doesn't have suit
            if (this->trump != suit::none) {
                // there is trump
                if (hand.has_suit(this->trump)) {
                    // player has trump
                    if (this->table[this->table.winning()].suit == this->trump) {
                        // the winning card is trump
                        if (this->table.count() % 2 != this->table.winning() % 2) {
                            // partner is not winning
                            if (hand.has_higher(this->table[this->table.winning()])) {
                                return possible_move > this->table[this->table.winning()];
                            } else {
                                // has no higher trump than winning trump
                                if (hand.has_other(this->trump)) {
                                    return possible_move.suit != this->trump;
                                } else {
                                    return true;
                                }
                            }
                        } else {
                            // partner is winning
                            return true;
                        }
                    } else {
                        // the winning card is not trump
                        return possible_move.suit == this->trump;
                    }
                } else {
                    // payer has no trump
                    return true;
                }
            }
            // no trump was chosen
            return true;
        } else {
            // did follow suit
            if (this->table.count() % 2 != this->table.winning() % 2) {
                // partner is not winning
                if (hand.has_higher(this->table[this->table.winning()])) {
                    // has a higher card than the card that is winning
                    return possible_move > this->table[this->table.winning()];
                } else {
                    // has no higher card than the card that is winning
                    return true;
                }
            } else {
                // partner is winning
               return true;
            }
        }
    }
}