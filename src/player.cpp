#include <random>
#include <algorithm>

#include "player.h"
#include "deck.h"

player::player(card *cards) : m_hand(cards) {}
bool player::will_tap(const suit& trump) const {
    return false;
}
bool player::will_retap(const suit& trump) const {
    return false;
}
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
std::ostream& operator<<(std::ostream& stream, player& player) {
    if (player.m_hand.count() != 0) {
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

        std::sort(player.m_hand.begin(), player.m_hand.end(), custom_comperator);

        for (uint8_t i = 0; i < player.m_hand.count(); i++) {
            stream << ".----";
            if (i == player.m_hand.count() - 1) stream << "----";
        }
        stream << "." << "\n";
        for (uint8_t i = 0; i < player.m_hand.count(); i++) {
            const card& card = player.m_hand[i];
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
            if (i == player.m_hand.count() - 1) stream << "    ";
        }
        stream << "|" << "\n";
        for (uint8_t i = 0; i < 4; i++) {
            for (uint8_t j = 0; j < player.m_hand.count(); j++) {
                const card& card = player.m_hand[j];
                stream << "|";
                switch (card.suit) {
                case suit::spades:
                    if (i == 0) { if (j != player.m_hand.count() - 1) {      stream << "   ."; } else { stream << "   .    "; } }
                    else if (i == 1) { if (j != player.m_hand.count() - 1) { stream << "  / "; } else { stream << "  / \\   "; } }
                    else if (i == 2) { if (j != player.m_hand.count() - 1) { stream << " (_,"; } else { stream << " (_,_)  "; } }
                    else { if (j != player.m_hand.count() - 1) {             stream << "   I"; } else { stream << "   I    "; } }
                    break;
                case suit::hearts:
                    if (i == 0) { if (j != player.m_hand.count() - 1) {      stream << "  _ "; } else { stream << "  _  _  "; } }
                    else if (i == 1) { if (j != player.m_hand.count() - 1) { stream << " ( \\"; } else { stream << " ( \\/ ) "; } }
                    else if (i == 2) { if (j != player.m_hand.count() - 1) { stream << "  \\ "; } else { stream << "  \\  /  "; } }
                    else { if (j != player.m_hand.count() - 1) {             stream << "   \\"; } else { stream << "   \\/   "; } }
                    break;
                case suit::clubs:
                    if (i == 0) { if (j != player.m_hand.count() - 1) {      stream << "   _"; } else { stream << "   _    "; } }
                    else if (i == 1) { if (j != player.m_hand.count() - 1) { stream << "  ( "; } else { stream << "  ( )   "; } }
                    else if (i == 2) { if (j != player.m_hand.count() - 1) { stream << " (_x"; } else { stream << " (_x_)  "; } }
                    else { if (j != player.m_hand.count() - 1) {             stream << "   Y"; } else { stream << "   Y    "; } }
                    break;
                case suit::diamonds:
                    if (i == 0) { if (j != player.m_hand.count() - 1) {      stream << "   /"; } else { stream << "   /\\   "; } }
                    else if (i == 1) { if (j != player.m_hand.count() - 1) { stream << "  / "; } else { stream << "  /  \\  "; } }
                    else if (i == 2) { if (j != player.m_hand.count() - 1) { stream << "  \\ "; } else { stream << "  \\  /  "; } }
                    else { if (j != player.m_hand.count() - 1) {             stream << "   \\"; } else { stream << "   \\/   "; } }
                    break;
                default:
                    break;
                }
            }
            stream << "|" << "\n";
        }
        for (uint8_t i = 0; i < player.m_hand.count(); i++) {
            const card& card = player.m_hand[i];
            stream << "|    ";
            if (i == player.m_hand.count() - 1) stream << "    ";
        }
        stream << "|" << "\n";
        stream << "`----";
        if (player.m_hand.count() == 1) stream << "----";
        for (uint8_t i = 1; i < player.m_hand.count(); i++) {
            stream << "^----";
            if (i == player.m_hand.count() - 1) stream << "----";
        }
        stream << "'";
    }
    return stream;
}