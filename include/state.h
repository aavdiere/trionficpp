#pragma once
#include "models.h"
#include "table.h"
#include "card.h"
#include "hand.h"
#include "cheat_sheet.h"
#include "defines.h"

class state {
public:
    suit trump;
    table table;
    cheat_sheet possible_cards;
    
    state();

    bool valid_move(const card& possible_move, const hand& hand) const;
private:
};