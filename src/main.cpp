#ifdef DEBUG
#include <iostream>
#include "cheat_sheet.h"
#endif // DEBUG

#include "game.h"

int main() {
    #ifdef DEBUG
    if (cheat_sheet_test()) {
        std::cout << "[failed] cheat sheet\n";
    } else {
        std::cout << "[success] cheat sheet\n";
    }
    std::cout << std::flush;
    #endif // DEBUG

    game current_game;

    current_game.play();

    return 0;
}