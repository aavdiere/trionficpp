#pragma once
#include <iostream>

enum class suit {
    spades, hearts, clubs, diamonds, none, undefined
};

std::ostream& operator<<(std::ostream& stream, const suit& suit);

enum class rank {
    seven, eight, nine, jack, queen, king, ace, manille
};