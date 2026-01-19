#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Classes.h" 
#include "Enemy.h"
#include "Encounter.h" 
#include <string>

class GameManager {
private:
    Character* m_player;
    int m_currentFloor;
    bool m_isGameActive;

    void init_player();           
    void play_turn();             


public:
    GameManager();
    ~GameManager(); 

    void run(); 
};

#endif