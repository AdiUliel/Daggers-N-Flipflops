#include "GameManager.h"
#include "Game.h"
#include "Utils.h" 
#include "Battle.hpp"   
#include "Shop.hpp"     
#include "WildCard.hpp" 

#include <cstdlib> 
#include <ctime>   
#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::string; 
using std::unique_ptr;
using std::make_unique;

GameManager::GameManager() : m_player(nullptr), m_currentFloor(1), m_isGameActive(true) {}

GameManager::~GameManager() {}

void GameManager::run() {
    print_tutorial();
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
            
            cout << "\nFloor cleared.\n";

            while (!movingOn) {
                cout << "\n--- PAUSE MENU ---\n";
                string input = get_string("OPTIONS: (i)nfo, (e)quipment, (n)ext floor, (q)uit\n> ");
                if (input.empty()) continue;
                char choice = input[0];

                if (choice == 'i' || choice == 'I') {
                    print_stats(m_player.get());
                }
                else if (choice == 'e' || choice == 'E') {
                    m_player->open_inventory();
                }
                else if (choice == 'n' || choice == 'N') {
                    cout << "Marching on. Try not to trip.\n";
                    m_currentFloor++;
                    movingOn = true;
                }
                else if (choice == 'q' || choice == 'Q') {
                    cout << "I have to ask...\n";
                    while(true) {
                        string confirmInput = get_string("Are you sure you want to QUIT THIS GAME? (y/n)\n> ");
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

/**
 * @brief Initializes the player character.
 * * Uses the Factory pattern to create a specific child class of Character
 * based on user string input (Warrior, Mage, etc).
 * Stores the result in m_player (unique_ptr).
 */
void GameManager::init_player() {
    int count = Game::getInstance().getRunCount();
    if (count == 1) {
        cout << "Oh look, another 'hero'. Welcome to the Endless Tower, I guess.\n";
    } else {
        cout << "Back again? You really don't learn, do you? (Attempt #" << count << ")\n";
    }

    string name = get_string("Let's get this over with. What do you call yourself, mortal? ");
    
    string pick;
    cout << "Choose a class (Warrior / Mage / Archer / Thief / Normie). No " << name <<", Mayonaise is not class.\n";
    
    while (true) {
        pick = get_string("> "); 
        pick = lowercase(pick);

        if (pick == "warrior") { m_player = make_unique<Warrior>(name); break; }
        if (pick == "mage") { m_player = make_unique<Mage>(name); break; }
        if (pick == "archer") { m_player = make_unique<Archer>(name); break; }
        if (pick == "thief") { m_player = make_unique<Thief>(name); break; }
        if (pick == "normie") { m_player = make_unique<Normie>(name); break; } 
        
        cout << "That's not even a class. Are you illiterate? Try again: ";
    }
    
    cout << "Ugh, a " << pick << ". How original. \nStats: HP: " << m_player->get_HP() << " | Power: " << m_player->get_power() << ". Try not to die in five minutes.\n";
    print_class_details(m_player->get_class_name());
}

/**
 * @brief Generates a random encounter for the current floor.
 * * Logic:
 * - Every 15th floor: BOSS BATTLE (Level + 5).
 * - Otherwise:
 * - 50% Battle
 * - 30% WildCard Event
 * - 20% Shop
 * * Uses Polymorphism to run the encounter via the base Encounter class.
 */
void GameManager::play_turn() {
    unique_ptr<Encounter> currentEncounter = nullptr;

    if (m_currentFloor % 15 == 0) {
        cout << "!!! BOSS DETECTED !!!\n";
        currentEncounter = make_unique<Battle>(m_currentFloor + 5);
    }
    else {
        int roll = random_int(1, 100);

        if (roll <= 50) {
            currentEncounter = make_unique<Battle>(m_currentFloor);
        } 
        else if (roll <= 80) {
            currentEncounter = make_unique<WildCard>();
        } 
        else {
            currentEncounter = make_unique<Shop>();
        }
    }

    if (currentEncounter != nullptr) {
        currentEncounter->run(m_player);
    }
}