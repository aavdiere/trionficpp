#pragma once
#include <array>

#include "card.h"
#include "table.h"
#include "hand.h"

class cheat_sheet {
public:
    cheat_sheet();
    ~cheat_sheet() = default;

    void reset();
    void analyse(const table& table);

    friend bool cheat_sheet_test();
private:
    std::array<std::array<card, 32>, 4> m_data;
    std::array<hand, 4> m_hands;

    void remove_card(const card& card_to_remove);
    void remove_card(const card& card_to_remove, const uint8_t player_id);
    void remove_suit(const suit& suit_to_remove);
    void remove_suit(const suit& suit_to_remove, const uint8_t player_id);
    void remove_all_higher(const card& minimum_rank, const uint8_t player_id);

    const bool has_higher(const card& minimum_rank) const;
    const bool has_higher(const card& minimum_rank, const uint8_t player_id) const;

    const bool has_any(const suit& suit_to_have) const;
    const bool has_any(const suit& suit_to_have, const uint8_t player_id) const;
};

bool cheat_sheet_test();