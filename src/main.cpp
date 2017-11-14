#include <chrono>
#include <ratio>
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

    auto start = std::chrono::high_resolution_clock::now();
    game current_game;
    current_game.play();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start);

    std::cout << "Passed time [us]: " << duration.count() << "\n";

    return 0;
}