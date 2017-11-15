#include "tree.h"

tree::tree() : m_score{0, 0}, m_hand_score{0, 0}, m_rounds(0), m_multiplier(1) {}
void tree::clear() {
    m_score = { 0, 0 };
    m_hand_score = { 0, 0 };
    m_rounds = 0;
    m_multiplier = 1;
}
void tree::finish_hand() {
    int8_t s0 = m_hand_score[0] - 30;
    int8_t s1 = m_hand_score[1] - 30;
    m_score[0] += s0 >= 0 ? s0 * m_multiplier : 0;
    m_score[1] += s1 >= 0 ? s1 * m_multiplier : 0;
    m_hand_score = { 0, 0 };
    m_multiplier = 1;
}
void tree::add(team team, uint8_t score) {
    m_hand_score[static_cast<uint8_t>(team)] += score;
}
void tree::up_multiplier() {
    m_multiplier *= 2;
}
uint8_t tree::multiplier() const {
    return m_multiplier;
}
std::ostream& operator<<(std::ostream& stream, tree& tree) {
    stream << "black: " << tree.m_score[0] << "\n";
    stream << "white: " << tree.m_score[1];
    return stream;
}