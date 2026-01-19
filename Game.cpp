#include "GameManager.h"
#include <ctime>
#include <cstdlib>

int main(){
    std::srand(std::time(0));

    GameManager game;
    game.run();
    return 0;
}