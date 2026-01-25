#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Classes.h" 
#include "Enemy.h"
#include "Encounter.h" 
#include "Battle.hpp"
#include "Shop.hpp"
#include "WildCard.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::string;
using std::endl;

/**
 * @class GameManager
 * @brief The Controller for a single game session.
 * * This class handles the specific logic of one run through the tower.
 * It manages:
 * 1. The Player object (creation, lifecycle, death).
 * 2. Floor progression.
 * 3. Generating random encounters (Battles, Shops, Wildcards).
 * 4. The interaction loop between turns (Inventory management, stats).
 */
class GameManager {
private:
    unique_ptr<Character> m_player;
    int m_currentFloor;
    bool m_isGameActive;

    void init_player(); 
    void play_turn();     // Factory         

public:
    GameManager();
    ~GameManager(); 

    void run(); // Current session's main loop
};

#endif