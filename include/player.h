#pragma once

#include "models.h"
#include "card.h"
#include "state.h"
#include "hand.h"

class player {
public:
    player(card *cards);
    
    suit choose_trump() const;
    const card& make_move(const state& current_state);

    friend std::ostream& operator<<(std::ostream& stream, player& player);
private:
    hand m_hand;
};