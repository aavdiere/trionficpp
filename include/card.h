#pragma once
#include "models.h"

#include <utility>

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

    void swap(card& rhs) noexcept {
        std::swap(empty, rhs.empty);
        std::swap(suit, rhs.suit);
        std::swap(rank, rhs.rank);
    }

    constexpr bool operator==(const card& rhs) const noexcept {
        return (empty == rhs.empty) && (suit == rhs.suit) && (rank == rhs.rank);
    }
    constexpr bool operator>(const card& rhs) const noexcept {
        return (empty == rhs.empty) && (suit == rhs.suit) && (rank > rhs.rank);
    }
    constexpr bool operator>=(const card& rhs) const noexcept {
        return (*this > rhs) || (*this == rhs);
    }
    constexpr bool operator<(const card& rhs) const noexcept {
        return !(*this >= rhs);
    }
    constexpr bool operator<=(const card& rhs) const noexcept {
        return !(*this > rhs);
    }
};