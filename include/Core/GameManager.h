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

class GameManager {
private:
    unique_ptr<Character> m_player;
    int m_currentFloor;
    bool m_isGameActive;

    void init_player();           
    void play_turn();             

public:
    GameManager();
    ~GameManager(); 

    void run(); 
    void reset_game();
};

#endif