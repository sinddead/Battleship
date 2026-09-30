#include <iostream>

#include "Battlelib.h"

int main() {
    Player p1("Player 1");
    Player p2("Player 2");

    Battle game(std::move(p1), std::move(p2));
    game.run();

    return 0;
}