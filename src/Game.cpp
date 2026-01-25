#include "Game.h"
#include "GameManager.h"
#include "Utils.h" 
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using std::cout;
using std::string; 

Game::Game() : m_currentSession(nullptr), m_runCounter(0) {}

/**
 * @brief The main entry point of the application logic.
 * * 1. Seeds the random number generator.
 * 2. Enters the main application loop.
 * 3. Allocates a new GameManager (Starts a new RPG session).
 * 4. Waits for the session to finish.
 * 5. Cleans up memory (deletes the session).
 * 6. Asks the user if they want to restart or exit.
 */
void Game::mainLoop() {
    std::srand(std::time(0)); // initiating the randomness for this run.
    bool isRunning = true;

    while (isRunning) {
        m_runCounter++;
        m_currentSession = new GameManager();
        m_currentSession->run();
        
        delete m_currentSession;
        m_currentSession = nullptr;

        while(true) { 
            cout << "\n--- MAIN MENU ---\n";
            
            string input = get_string("The session has ended. Do you want to start a NEW GAME? (y/n): ");
            
            char choice = input[0]; 

            if (choice == 'n' || choice == 'N') {
                cout << "Exiting application. Bye!\n";
                isRunning = false;
                break;
            }
            else if (choice == 'y' || choice == 'Y') {
                cout << "Starting fresh... Good luck (you'll need it).\n\n";
                break; 
            }
            else {
                cout << "It's a simple yes or no question...\n";
            }
        }
    }
}

int main() {
    Game::getInstance().mainLoop();
    return 0;
}