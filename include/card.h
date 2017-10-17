#pragma once
#include "models.h"

class card {
public:
    bool empty;
    suit suit;
    rank rank;

    card() : empty(true) {};
    card(enum suit suit, enum rank rank) : suit(suit), rank(rank), empty(false) {};

    void set_card(enum suit suit, enum rank rank) {
        empty = false;
        this->suit = suit;
        this->rank = rank;
    }
};