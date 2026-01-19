#include "GameManager.h"
#include "Game.h"
#include "Utils.h" 
#include "Battle.hpp"   
#include "Shop.hpp"     
#include "WildCard.hpp" 

#include <cstdlib> 
#include <ctime>   
#include <iostream>

using std::cout;
using std::cin;
using std::string; 

GameManager::GameManager() : m_player(nullptr), m_currentFloor(1), m_isGameActive(true) {}

GameManager::~GameManager() {
    if (m_player != nullptr) {
        delete m_player;
    }
}

void GameManager::run() {
    init_player();

    while (m_isGameActive) {
        
        if (!m_player->isKnockedOut()) {
            cout << "\n========================================\n";
            cout << "      DRAGGING YOU TO FLOOR " << m_currentFloor << "\n";
            cout << "========================================\n";
            
            play_turn();
        }

        if (m_player->isKnockedOut()) {
            cout << "\n\nFinally. YOU DIED. I knew you wouldn't make it past floor " << m_currentFloor << ".\n";
            cout << "Humanity is so fragile. Pathetic.\n";
            m_isGameActive = false;
        }
        
        else {
            bool movingOn = false;
            
            cout << "\nFloor cleared. Take a breath, you look terrible.\n";

            while (!movingOn) {
                cout << "\n--- PAUSE MENU ---\n";
                string input = get_string("OPTIONS: (i)nfo, (n)ext floor, (q)uit\n> ");
                char choice = input[0];

                if (choice == 'i' || choice == 'I') {
                    cout << "Stats: HP " << m_player->get_HP() << " | Gold " << m_player->get_coins() << "\n";
                }
                else if (choice == 'n' || choice == 'N') {
                    cout << "Marching on. Try not to trip.\n";
                    m_currentFloor++;
                    movingOn = true;
                }
                else if (choice == 'q' || choice == 'Q') {
                    cout << "I have to ask...\n";
                    while(true) {
                        
                        string confirmInput = get_string("Are you sure? (y/n)\n> ");
                        char confirm = confirmInput[0]; 

                        if (confirm == 'n' || confirm == 'N') {
                            cout << "Stay with me then. We're having fun, aren't we?\n";
                            break;
                        }
                        else if (confirm == 'y' || confirm == 'Y') {
                            cout << "Every time someone quits this game, my ego grows bigger. IT HURTS!!\n\n";
                            m_isGameActive = false; 
                            movingOn = true;
                            break; 
                        }
                        else {
                            cout << "It's a simple yes or no question...\n";
                        }
                    }                    
                }
                else {
                    cout << "Unknown command.\n";
                }
            }
        }
    }
}

void GameManager::init_player() {
    int count = Game::getInstance().getRunCount();
    if (count == 1) {
        cout << "Oh look, another 'hero'. Welcome to the Endless Tower, I guess.\n";
    } else {
        cout << "Back again? You really don't learn, do you? (Attempt #" << count << ")\n";
    }

    string name = get_string("Let's get this over with. What do you call yourself, mortal? ");
    
    string pick;
    cout << "Choose a class (Warrior / Mage / Archer / Thief / Normie). Try to pick something useful.\n";
    
    while (true) {
        pick = get_string("> "); 

        if (pick == "Warrior") { m_player = new Warrior(name); break; }
        if (pick == "Mage") { m_player = new Mage(name); break; }
        if (pick == "Archer") { m_player = new Archer(name); break; }
        if (pick == "Thief") { m_player = new Thief(name); break; }
        if (pick == "Normie") { m_player = new Normie(name); break; } 
        
        cout << "That's not even a class. Are you illiterate? Try again: ";
    }
    
    cout << "Ugh, a " << pick << ". How original. \nStats: HP: " << m_player->get_HP() << " | Power: " << m_player->get_power() << ". Try not to die in five minutes.\n";
}

void GameManager::play_turn() {
    Encounter* currentEncounter = nullptr;

    if (m_currentFloor % 15 == 0) {
        cout << "!!! BOSS DETECTED !!!\n";
        currentEncounter = new Battle(m_currentFloor + 5);
    }
    else {
        int roll = random_int(1, 100);

        if (roll <= 50) {
            currentEncounter = new Battle(m_currentFloor);
        } 
        else if (roll <= 80) {
            currentEncounter = new WildCard();
        } 
        else {
            currentEncounter = new Shop();
        }
    }

    if (currentEncounter != nullptr) {
        currentEncounter->run(m_player);
        delete currentEncounter;
    }
}