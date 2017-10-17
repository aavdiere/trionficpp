#pragma once

#include "models.h"
#include "card.h"
#include "state.h"
#include "hand.h"

class player {
public:
    player(card * const cards);
    
    suit choose_trump() const;
    const card& make_move(const state& current_state);
private:
    hand m_hand;
};