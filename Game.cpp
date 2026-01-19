#include "Game.h"
#include "GameManager.h"
#include "Utils.h" 
#include <cstdlib> 
#include <ctime> 
#include <iostream>

using std::cout;
using std::string; 

Game::Game() : m_currentSession(nullptr), m_runCounter(0) {}

void Game::run() {
    std::srand(std::time(0));
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
    Game::getInstance().run();
    return 0;
}