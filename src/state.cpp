#include "state.h"

state::state(const uint8_t& player_offset) : m_trump(suit::undefined), m_table(m_trump, player_offset) {}
void state::add(const card& played_card) {
    m_possible_cards.analyse(*this, played_card);
    m_table.add(played_card);
}
void state::clear_table() {
    m_table.clear();
}
void state::clear_hand() {
    m_possible_cards.reset();
}
bool state::valid_move(const card& possible_move, const hand& hand) const {
    if (m_table.count() == 0) {
        // first player always makes valid move
        return true;
    } else {
        // other players don't necessarily make a valid move
        if (!m_table.follows_suit(possible_move)) {
            // didn't follow suit
            if (hand.has_suit(m_table[0].suit))
                return false;
            // doesn't have suit
            if (m_trump != suit::none) {
                // there is trump
                if (hand.has_suit(m_trump)) {
                    // player has trump
                    if (m_table[m_table.winning()].suit == m_trump) {
                        // the winning card is trump
                        if (m_table.count() % 2 != m_table.winning() % 2) {
                            // partner is not winning
                            if (hand.has_higher(m_table[m_table.winning()])) {
                                return possible_move > m_table[m_table.winning()];
                            } else {
                                // has no higher trump than winning trump
                                if (hand.has_other(m_trump)) {
                                    return possible_move.suit != m_trump;
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
                        return possible_move.suit == m_trump;
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
            if (m_table.count() % 2 != m_table.winning() % 2) {
                // partner is not winning
                if (m_table[m_table.winning()].suit == m_trump) {
                    // winning card is trump
                    if (possible_move.suit == m_trump) {
                        // current suit is trump
                        if (hand.has_higher(m_table[m_table.winning()])) {
                            // has a higher card than the card that is winning
                            return possible_move > m_table[m_table.winning()];
                        } else {
                            // has no higher card than the card that is winning
                            return true;
                        }
                    } else {
                        // current suit is not trump
                        return true;
                    }
                } else {
                    // winning card is not trump
                    if (hand.has_higher(m_table[m_table.winning()])) {
                        // has a higher card than the card that is winning
                        return possible_move > m_table[m_table.winning()];
                    } else {
                        // has no higher card than the card that is winning
                        return true;
                    }
                }
            } else {
                // partner is winning
               return true;
            }
        }
    }
}
const cheat_sheet& state::get_cheat_sheet() const {
    return m_possible_cards;
}