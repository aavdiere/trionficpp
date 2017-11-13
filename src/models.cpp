#include "models.h"

std::ostream& operator<<(std::ostream& stream, const suit& suit){
    switch (suit) {
    case suit::clubs:
        stream << "trump: clubs" << "\n";
        break;
    case suit::diamonds:
        stream << "trump: diamonds" << "\n";
        break;
    case suit::hearts:
        stream << "trump: hearts" << "\n";
        break;
    case suit::spades:
        stream << "trump: spades" << "\n";
        break;
    case suit::none:
        stream << "trump: none" << "\n";
        break;
    case suit::undefined:
        stream << "trump: undefined" << "\n";
        break;
    }
    return stream;
}