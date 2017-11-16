#include <algorithm>
#include <vector>
#include <sstream>

#include "cheat_sheet.h"
#include "state.h"

cheat_sheet::cheat_sheet() : m_hands({hand(&m_data[0][0], 32), hand(&m_data[1][0], 32), hand(&m_data[2][0], 32), hand(&m_data[3][0], 32)}) {
    for (uint8_t i = 0; i < 32; i++)
        for (uint8_t j = 0; j < 4; m_data[j++][i] = card(static_cast<suit>(i / 8), static_cast<rank>(i % 8)));
}
void cheat_sheet::reset() {
    for (auto& hand : m_hands)
        hand.reset();
}
void cheat_sheet::analyse(const state& state) {
    static enum class analyse_state {
        from_valid_moves, followed, trump_exists, trump_played, trump_has_been_played, partner_winning, lower_trump, shouldve_played_trump, done
    } s;
    uint8_t current_player = (state.get_table().player_offset + state.get_table().count() - 1) % 4;
    hand& possible_cards = m_hands[current_player];
    const card& current_card = state.get_table()[state.get_table().count() - 1];
    const card& winning_card = state.get_table()[state.get_table().winning()];
    while (s != analyse_state::done) {
        switch(s) {
        case analyse_state::from_valid_moves:
            for (card& c : possible_cards)
                if (state.valid_move(c, possible_cards))
                    if (c == current_card)
                        s = analyse_state::done;
            if (s == analyse_state::from_valid_moves)
                s = analyse_state::followed;
            break;
        case analyse_state::followed:
            if (current_card.suit == state.get_table()[0].suit) {
                remove_all_higher(winning_card, current_player);
                s = analyse_state::done;
            } else {
                remove_suit(state.get_table()[0].suit, current_player);
                s = analyse_state::trump_exists;
            }
            break;
        case analyse_state::trump_exists:
            if (state.trump() == suit::none)
                s = analyse_state::done;
            else
                s = analyse_state::trump_played;
            break;
        case analyse_state::trump_played:
            if (current_card.suit == state.trump())
                s = analyse_state::trump_has_been_played;
            else
                s = analyse_state::shouldve_played_trump;
            break;
        case analyse_state::trump_has_been_played:
            if (winning_card.suit == state.trump())
                s = analyse_state::partner_winning;
            else
                s = analyse_state::done;
            break;
        case analyse_state::partner_winning:
            if (state.get_table().count() - 1 % 2 == state.get_table().winning() % 2)
                s = analyse_state::done;
            else
                s = analyse_state::lower_trump;
            break;
        case analyse_state::lower_trump:
            if (current_card < winning_card) {
                if (state.trump() != suit::clubs)
                    remove_suit(suit::clubs, current_player);
                if (state.trump() != suit::diamonds)
                    remove_suit(suit::diamonds, current_player);
                if (state.trump() != suit::hearts)
                    remove_suit(suit::hearts, current_player);
                if (state.trump() != suit::spades)
                    remove_suit(suit::spades, current_player);
            }
            s = analyse_state::done;
            break;
        case analyse_state::shouldve_played_trump:
            if (state.get_table().count() - 1 % 2 != state.get_table().winning() % 2) {
                if (winning_card.suit == state.trump()) {
                    remove_all_higher(winning_card, current_player);
                } else {
                    remove_suit(state.trump(), current_player);
                }
            }
            s = analyse_state::done;
            break;
        case analyse_state::done:
            break;
        }
    }
}
void cheat_sheet::remove_card(const card& card_to_remove) {
    for (uint8_t i = 0; i < 4; i++)
        remove_card(card_to_remove, i);
}
void cheat_sheet::remove_card(const card& card_to_remove, const uint8_t player_id) {
    auto el = std::find(m_hands[player_id].begin(), m_hands[player_id].end(), card_to_remove);
    if (el != m_hands[player_id].end()) {
        m_hands[player_id].remove_at_index(el - m_hands[player_id].begin());
    }
}
void cheat_sheet::remove_suit(const suit& suit_to_remove) {
    for (uint8_t i = 0; i < 4; i++)
        remove_suit(suit_to_remove, i);
}
void cheat_sheet::remove_suit(const suit& suit_to_remove, const uint8_t player_id) {
    uint8_t count = m_hands[player_id].count();
    for (uint8_t i = count - 1; i < 0xff; i--) {
        if (m_hands[player_id][i].suit == suit_to_remove) {
            m_hands[player_id].remove_at_index(i);
        }
    }
}
void cheat_sheet::remove_all_higher(const card& minimum_rank, const uint8_t player_id) {
    uint8_t count = m_hands[player_id].count();
    for (uint8_t i = count - 1; i < 0xff; i--) {
        if (m_hands[player_id][i] >= minimum_rank) {
            m_hands[player_id].remove_at_index(i);
        }
    }
}

const bool cheat_sheet::has_higher(const card& minimum_rank) const {
    bool result = false;
    for (uint8_t i = 0; i < 4; i++) {
        result |= has_higher(minimum_rank, i);
    }
    return result;
}
const bool cheat_sheet::has_higher(const card& minimum_rank, const uint8_t player_id) const {
    bool result = false;
    for (auto& card : m_hands[player_id])
        result |= (card > minimum_rank);
    return result;
}

const bool cheat_sheet::has_any(const suit& suit_to_have) const {
    bool result = false;
    for (uint8_t i = 0; i < 4; i++) {
        result |= has_any(suit_to_have, i);
    }
    return result;
}
const bool cheat_sheet::has_any(const suit& suit_to_have, const uint8_t player_id) const {
    bool result = false;
    for (auto& card : m_hands[player_id])
        result |= (card.suit == suit_to_have);
    return result;
}
std::string cheat_sheet::print(uint8_t player) const {
    std::stringstream stream;
    if (m_hands[player].count() != 0) {
        struct {
            bool operator()(card& a, card& b) const {   
                if (a.suit < b.suit) {
                    return true;
                } else if (a.suit == b.suit) {
                    if (a.rank < b.rank) {
                        return true;
                    } else if (a.rank == b.rank) {
                        return false;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }   
        } custom_comperator;

        //std::sort(m_hands[player].begin(), m_hands[player].end(), custom_comperator);

        for (uint8_t i = 0; i < m_hands[player].count(); i++) {
            stream << ".----";
            if (i == m_hands[player].count() - 1) stream << "----";
        }
        stream << "." << "\n";
        for (uint8_t i = 0; i < m_hands[player].count(); i++) {
            const card& card = m_hands[player][i];
            stream << "|";
            uint8_t r = 7;
            switch (card.rank) {
            case rank::manille:
                stream << "10";
                break;
            case rank::ace:
                stream << "A ";
                break;
            case rank::king:
                stream << "K ";
                break;
            case rank::queen:
                stream << "Q ";
                break;
            case rank::jack:
                stream << "J ";
                break;
            case rank::nine:
                r++;
            case rank::eight:
                r++;
            case rank::seven:
                stream << r << " ";
                break;
            }
            stream << "  ";
            if (i == m_hands[player].count() - 1) stream << "    ";
        }
        stream << "|" << "\n";
        for (uint8_t i = 0; i < 4; i++) {
            for (uint8_t j = 0; j < m_hands[player].count(); j++) {
                const card& card = m_hands[player][j];
                stream << "|";
                switch (card.suit) {
                case suit::spades:
                    if (i == 0) { if (j != m_hands[player].count() - 1) {      stream << "   ."; } else { stream << "   .    "; } }
                    else if (i == 1) { if (j != m_hands[player].count() - 1) { stream << "  / "; } else { stream << "  / \\   "; } }
                    else if (i == 2) { if (j != m_hands[player].count() - 1) { stream << " (_,"; } else { stream << " (_,_)  "; } }
                    else { if (j != m_hands[player].count() - 1) {             stream << "   I"; } else { stream << "   I    "; } }
                    break;
                case suit::hearts:
                    if (i == 0) { if (j != m_hands[player].count() - 1) {      stream << "  _ "; } else { stream << "  _  _  "; } }
                    else if (i == 1) { if (j != m_hands[player].count() - 1) { stream << " ( \\"; } else { stream << " ( \\/ ) "; } }
                    else if (i == 2) { if (j != m_hands[player].count() - 1) { stream << "  \\ "; } else { stream << "  \\  /  "; } }
                    else { if (j != m_hands[player].count() - 1) {             stream << "   \\"; } else { stream << "   \\/   "; } }
                    break;
                case suit::clubs:
                    if (i == 0) { if (j != m_hands[player].count() - 1) {      stream << "   _"; } else { stream << "   _    "; } }
                    else if (i == 1) { if (j != m_hands[player].count() - 1) { stream << "  ( "; } else { stream << "  ( )   "; } }
                    else if (i == 2) { if (j != m_hands[player].count() - 1) { stream << " (_x"; } else { stream << " (_x_)  "; } }
                    else { if (j != m_hands[player].count() - 1) {             stream << "   Y"; } else { stream << "   Y    "; } }
                    break;
                case suit::diamonds:
                    if (i == 0) { if (j != m_hands[player].count() - 1) {      stream << "   /"; } else { stream << "   /\\   "; } }
                    else if (i == 1) { if (j != m_hands[player].count() - 1) { stream << "  / "; } else { stream << "  /  \\  "; } }
                    else if (i == 2) { if (j != m_hands[player].count() - 1) { stream << "  \\ "; } else { stream << "  \\  /  "; } }
                    else { if (j != m_hands[player].count() - 1) {             stream << "   \\"; } else { stream << "   \\/   "; } }
                    break;
                default:
                    break;
                }
            }
            stream << "|" << "\n";
        }
        for (uint8_t i = 0; i < m_hands[player].count(); i++) {
            const card& card = m_hands[player][i];
            stream << "|    ";
            if (i == m_hands[player].count() - 1) stream << "    ";
        }
        stream << "|" << "\n";
        stream << "`----";
        if (m_hands[player].count() == 1) stream << "----";
        for (uint8_t i = 1; i < m_hands[player].count(); i++) {
            stream << "^----";
            if (i == m_hands[player].count() - 1) stream << "----";
        }
        stream << "'";
    }
    return stream.str();
}

bool cheat_sheet_test() {
    bool result = false;
    
    {
        cheat_sheet cs;

        for (uint8_t i = 0; i < 4; i++)
            result |= (cs.m_hands[i].count() != 32);

        for (uint8_t i = 0; i < 8; i++) {
            rank r = static_cast<rank>(i);
            cs.remove_card(card(suit::diamonds, r));
        }
        for (uint8_t i = 0; i < 4; i++) {
            result |= (cs.m_hands[i].count() != 24);
            result |= !cs.has_higher(card(suit::spades, rank::nine));
            result |= cs.has_higher(card(suit::diamonds, rank::nine));
            result |= cs.has_any(suit::diamonds);
            result |= !cs.has_any(suit::hearts);
        }

        cs.reset();

        cs.remove_suit(suit::hearts);
        cs.remove_suit(suit::hearts);
        cs.remove_suit(suit::spades);
        cs.remove_all_higher(card(suit::clubs, rank::nine), 0);
        cs.remove_all_higher(card(suit::clubs, rank::nine), 1);
        cs.remove_all_higher(card(suit::clubs, rank::nine), 2);
        cs.remove_all_higher(card(suit::clubs, rank::nine), 3);
        for (uint8_t i = 0; i < 4; i++) {
            result |= (cs.m_hands[0].count() != 10);
            result |= cs.has_higher(card(suit::spades, rank::nine));
            result |= !cs.has_higher(card(suit::diamonds, rank::nine));
            result |= cs.has_higher(card(suit::clubs, rank::nine));
            result |= !cs.has_any(suit::diamonds);
            result |= cs.has_any(suit::hearts);
        }
    }

    return result;
}