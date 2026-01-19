#ifndef GAME_H
#define GAME_H

//#include "GameManager.h"
#include "Utils.h"
#include <cstdlib> // עבור srand
#include <ctime>   // עבור time
#include <iostream>

using std::cout;
using std::cin;

class GameManager;

class Game {
private:
    Game(); // private c'tor
    
    GameManager* m_currentSession;
    int m_runCounter;

public:
    Game(const Game&) = delete;
    void operator=(const Game&) = delete;

    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    void run();

    int getRunCount() const { return m_runCounter; }
};

#endif