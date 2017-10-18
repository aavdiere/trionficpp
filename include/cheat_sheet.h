#pragma once
#include <array>

#include "card.h"

class cheat_sheet {
public:
    cheat_sheet();

    void remove_card(const card& card_to_remove);
    void remove_card(const card& card_to_remove, const uint8_t player_id);
    void remove_suit(const suit& suit_to_remove);
    void remove_suit(const suit& suit_to_remove, const uint8_t player_id);
    void remove_all_higher(const card& minimum_rank, const uint8_t player_id);

    const card& has_higher(const card& minimum_rank) const;
    const card& has_higher(const card& minimum_rank, const uint8_t player_id) const;
private:
    std::array<std::array<card, 32>, 4> m_data;
    std::array<uint8_t, 4> m_count;
};