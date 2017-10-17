#pragma once
#include "defines.h"
#include "models.h"
#include "table.h"
#include "card.h"

class state {
public:
    suit trump;
    table table;
    uint8_t table_count;
    card possible_cards[4][4][8];
    uint8_t player_map[4];
};