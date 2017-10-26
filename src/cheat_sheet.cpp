#include <algorithm>

#include "cheat_sheet.h"

cheat_sheet::cheat_sheet() : m_count({32, 32, 32, 32}) {
    for (uint8_t i = 0; i < 32; i++)
        for (uint8_t j = 0; j < 4; m_data[j++][i] = card(static_cast<suit>(i / 8), static_cast<rank>(i % 8)));
}

void cheat_sheet::reset() {
    m_count = {32, 32, 32, 32};
}
void cheat_sheet::remove_card(const card& card_to_remove) {
    for (uint8_t i = 0; i < 4; i++)
        remove_card(card_to_remove, i);
}
void cheat_sheet::remove_card(const card& card_to_remove, const uint8_t player_id) {
    auto el = std::find(m_data[player_id].begin(), m_data[player_id].begin() + m_count[player_id], card_to_remove);
    if (el != m_data[player_id].begin() + m_count[player_id])
        std::swap(*el, m_data[player_id][--m_count[player_id]]);
}
void cheat_sheet::remove_suit(const suit& suit_to_remove) {
    for (uint8_t i = 0; i < 4; i++)
        remove_suit(suit_to_remove, i);
}
void cheat_sheet::remove_suit(const suit& suit_to_remove, const uint8_t player_id) {
    for (uint8_t i = m_count[player_id] - 1; i < 0xff; i--)
        if (m_data[player_id][i].suit == suit_to_remove)
            std::swap(m_data[player_id][i], m_data[player_id][--m_count[player_id]]);
}
void cheat_sheet::remove_all_higher(const card& minimum_rank, const uint8_t player_id) {
    for (uint8_t i = m_count[player_id] - 1; i < 0xff; i--)
        if (m_data[player_id][i] >= minimum_rank)
            std::swap(m_data[player_id][i], m_data[player_id][--m_count[player_id]]);
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
    for (uint8_t i = 0; i < m_count[player_id] && !result; i++)
        result |= (m_data[player_id][i] > minimum_rank);
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
    for (uint8_t i = 0; i < m_count[player_id] && !result; i++)
        result |= (m_data[player_id][i].suit == suit_to_have);
    return result;
}

bool cheat_sheet_test() {
    bool result = false;
    
    {
        cheat_sheet cs;

        for (uint8_t i = 0; i < 4; i++)
            result |= (cs.m_count[i] != 32);

        for (uint8_t i = 0; i < 8; i++) {
            rank r = static_cast<rank>(i);
            cs.remove_card(card(suit::diamonds, r));
        }
        for (uint8_t i = 0; i < 4; i++) {
            result |= (cs.m_count[i] != 24);
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
            result |= (cs.m_count[0] != 10);
            result |= cs.has_higher(card(suit::spades, rank::nine));
            result |= !cs.has_higher(card(suit::diamonds, rank::nine));
            result |= cs.has_higher(card(suit::clubs, rank::nine));
            result |= !cs.has_any(suit::diamonds);
            result |= cs.has_any(suit::hearts);
        }
    }

    return result;
}