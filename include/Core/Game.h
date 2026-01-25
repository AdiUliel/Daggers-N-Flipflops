#ifndef GAME_H
#define GAME_H

//#include "GameManager.h"
#include "Utils.h"
#include <cstdlib>
#include <ctime> 
#include <iostream>

using std::cout;
using std::cin;

class GameManager; // Forward declaration - we promise our compiler that we will handle a class with this name

/**
 * @class Game
 * @brief The Application Wrapper (Singleton).
 * * This class manages the application's lifecycle. It is responsible for:
 * 1. Initializing the random seed.
 * 2. Creating and destroying Game Sessions (GameManager instances).
 * 3. Handling the "Play Again" loop.
 * * It uses the Singleton pattern to ensure only one application instance exists.
 */
class Game {
private:
    Game(); // private c'tor - standard singleton - cannot create an instance from outside
    
    GameManager* m_currentSession; 
    int m_runCounter; // amount of games played in a row since program started

public:
    // standard singleton - deleting operators to prevent copying our singleton
    Game(const Game&) = delete;
    void operator=(const Game&) = delete;

    // standard singleton - "getInstance"
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    void mainLoop(); // our main loop

    int getRunCount() const { return m_runCounter; }
};

#endif