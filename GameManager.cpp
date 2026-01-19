#include "GameManager.h"
#include "Utils.h" 

#include "Battle.hpp"
#include "Shop.hpp"
#include "WildCard.hpp"

#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

GameManager::GameManager() : m_player(nullptr), m_currentFloor(1), m_isGameActive(true) {
}

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
            
            cout << "\nDo you want to embarrass yourself again? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                cout << "Sigh. Glutton for punishment. Fine. Resetting the simulation...\n\n";
                delete m_player;
                m_player = nullptr;
                m_currentFloor = 1;
                init_player();
            } 
            else {
                cout << "Wise choice. Stay dead. Goodbye.\n";
                m_isGameActive = false;
            }

        } else {
            bool movingOn = false;
            
            cout << "\nFloor cleared. Take a breath, you look terrible.\n";

            while (!movingOn) {
                cout << "\n--- PAUSE MENU ---\n";
                cout << "OPTIONS: (i)nfo, (n)ext floor, (q)uit\n> ";
                char choice;
                cin >> choice;

                if (choice == 'i' || choice == 'I') {
                    print_stats(m_player); 
                }
                else if (choice == 'q' || choice == 'Q') {
                    cout << "Coward. I expected nothing less. Leaving the tower...\n";
                    m_isGameActive = false;
                    movingOn = true;
                }
                else {
                    cout << "Marching on. Try not to trip.\n";
                    m_currentFloor++;
                    movingOn = true;
                }
            }
        }
    }
}

void GameManager::init_player() {
    string name, cls;
    cout << "Oh look, another 'hero'. Welcome to the Endless Tower, I guess.\n";
    cout << "Let's get this over with. What do you call yourself, mortal? ";
    cin >> name;
    
    cout << "Choose a class (Warrior / Mage / Archer / Thief / Normie). Try to pick something useful: ";
    while (true) {
        cin >> cls;
        if (cls == "Warrior") { m_player = new Warrior(name); break; }
        if (cls == "Mage") { m_player = new Mage(name); break; }
        if (cls == "Archer") { m_player = new Archer(name); break; }
        if (cls == "Thief") { m_player = new Thief(name); break; }
        if (cls == "Normie") { m_player = new Normie(name); break; } 
        cout << "That's not even a class. Are you illiterate? Try again: ";
    }
    cout << "Ugh, a " << cls << ". How original. \nStats: HP: " << m_player->get_HP() << " | Power: " << m_player->get_power() << ". Try not to die in five minutes.\n";
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
