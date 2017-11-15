#include "table.h"

void table::add(const card& played_card) {
    if (m_count < 4) {
        m_score = played_card + m_score;
        m_data[m_count++] = played_card;
        if (m_count == 1) {
            m_winning = 0;
        } else {
            if (m_data[m_count - 1] > m_data[m_winning]) {
                m_winning = m_count - 1;
            } else if (m_data[m_count - 1].suit == m_trump && m_data[m_winning].suit != m_trump) {
                m_winning = m_count - 1;
            }
        }
    } else throw std::out_of_range("Tying to add more elements to the table than it can handle.");
}
void table::clear() {
    m_count = 0;
    m_score = 0;
}
uint8_t table::count() const {
    return m_count;
}
uint8_t table::score() const {
    return m_score;
}
bool table::follows_suit(const card& card) const {
    if (m_count == 0) return true;
    else return card.suit == m_data[0].suit;
}
uint8_t table::winning() const {
    return m_winning;
}
const card& table::operator[](uint8_t index) const {
    if (index < m_count)
        return m_data[index];
    else
        throw std::out_of_range("Trying to access index out of range.");
}
std::ostream& operator<<(std::ostream& stream, const table& table) {
    if (table.m_count != 0) {
        for (uint8_t i = 0; i < table.m_count; i++)
            stream << ".--------";
        stream << "." << "\n";
        for (auto& card : table) {
            stream << "|";
            uint8_t r = 7;
            switch (card.rank) {
            case rank::manille:
                stream << "10";
                break;
            case rank::ace:
                stream << "A ";
                break;
            case rank::king:
                stream << "K ";
                break;
            case rank::queen:
                stream << "Q ";
                break;
            case rank::jack:
                stream << "J ";
                break;
            case rank::nine:
                r++;
            case rank::eight:
                r++;
            case rank::seven:
                stream << r << " ";
                break;
            }
            stream << "      ";
        }
        stream << "|" << "\n";
        for (uint8_t i = 0; i < 4; i++) {
            for (auto& card : table) {
                stream << "|";
                switch (card.suit) {
                case suit::spades:
                    if (i == 0)      stream << "   .    ";
                    else if (i == 1) stream << "  / \\   ";
                    else if (i == 2) stream << " (_,_)  ";
                    else             stream << "   I    ";
                    break;
                case suit::hearts:
                    if (i == 0)      stream << "  _  _  ";
                    else if (i == 1) stream << " ( \\/ ) ";
                    else if (i == 2) stream << "  \\  /  ";
                    else             stream << "   \\/   ";
                    break;
                case suit::clubs:
                    if (i == 0)      stream << "   _    ";
                    else if (i == 1) stream << "  ( )   ";
                    else if (i == 2) stream << " (_x_)  ";
                    else             stream << "   Y    ";
                    break;
                case suit::diamonds:
                    if (i == 0)      stream << "   /\\   ";
                    else if (i == 1) stream << "  /  \\  ";
                    else if (i == 2) stream << "  \\  /  ";
                    else             stream << "   \\/   ";
                    break;
                default:
                    break;
                }
            }
            stream << "|" << "\n";
        }
        for (auto& card : table) {
            stream << "|      ";
            uint8_t r = 7;
            switch (card.rank) {
            case rank::manille:
                stream << "10";
                break;
            case rank::ace:
                stream << " A";
                break;
            case rank::king:
                stream << " K";
                break;
            case rank::queen:
                stream << " Q";
                break;
            case rank::jack:
                stream << " J";
                break;
            case rank::nine:
                r++;
            case rank::eight:
                r++;
            case rank::seven:
                stream << " " << r;
                break;
            }
        }
        stream << "|" << "\n";
        if (table.m_count != 0) {
            stream << "`--------";
            for (uint8_t i = 1; i < table.m_count; i++) {
                stream << "^--------";
            }
            stream << "'";
        }
    }
    return stream;
}    