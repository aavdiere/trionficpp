#include "models.h"

std::ostream& operator<<(std::ostream& stream, const suit& suit){
    switch (suit) {
    case suit::clubs:
        stream << "trump: clubs";
        break;
    case suit::diamonds:
        stream << "trump: diamonds";
        break;
    case suit::hearts:
        stream << "trump: hearts";
        break;
    case suit::spades:
        stream << "trump: spades";
        break;
    case suit::none:
        stream << "trump: none";
        break;
    case suit::undefined:
        stream << "trump: undefined";
        break;
    }
    return stream;
}