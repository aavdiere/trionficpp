#pragma once
#include "defines.h"
#include "models.h"
#include "table.h"
#include "card.h"

class state {
public:
    suit trump;
    table table;
    
    state();
private:
    // write container for this
    card possible_cards[4][4][8];
    uint8_t player_map[4];
};