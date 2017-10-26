#pragma once
#include "defines.h"
#include "models.h"
#include "table.h"
#include "card.h"
#include "cheat_sheet.h"

class state {
public:
    suit trump;
    table table;
    cheat_sheet possible_cards;
    
    state();
private:
};