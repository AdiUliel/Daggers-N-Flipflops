#include "Utils.h"
#include "Classes.h"
#include <random>
#include <iostream>
#include <limits>
#include <vector>
#include <cctype>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::unique_ptr;
using std::make_unique;
using std::vector;

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void print_stats(const Character* player) {
    if (player == nullptr) return;

    cout << "\n----------------------------------------\n";
    cout << "    PLAYER STATS (Mediocre at best)  \n";
    cout << "----------------------------------------\n";
    cout << "Name:  " << player->get_name() << "\n";
    cout << "Class: " << player->get_class_name() << "\n";
    cout << "Level: " << player->get_level() << "\n";
    cout << "HP:    " << player->get_HP() << " (Try to keep this above 0)\n";
    cout << "MP:    " << player->get_MP() << "\n";
    cout << "Power: " << player->get_power() << "\n";
    cout << "Gold:  " << player->get_coins() << "\n";
    cout << "EXP:   " << player->get_exp() << " / " << player->get_exp_to_next_level() << "\n";
    cout << "----------------------------------------\n";
}

void print_tutorial() {
    cout << "\n================================================================\n";
    cout << "               DAGGERS & FLIPFLOPS: SURVIVAL GUIDE          \n";
    cout << "================================================================\n";
    
    cout << "\n[ OBJECTIVE ]\n";
    cout << "Climb the Endless Tower. Every floor gets harder.\n";
    cout << "If you die, you restart from Floor 1. No mercy.\n";

    cout << "\n[ CONTROLS ]\n";
    cout << " > Type the NUMBER next to the option and press ENTER.\n";
    cout << " > Example: If you see '1. Attack', type '1' and hit Enter.\n";

    cout << "\n[ CLASSES - KNOW YOUR HERO ]\n";
    cout << " * Warrior: High HP & Defense. Can STUN enemies.\n";
    cout << " * Mage:    Low HP, High Magic. Can HEAL self. Needs Mana Potions!\n";
    cout << " * Archer:  Usually acts FIRST. High Critical Hit chance.\n";
    cout << " * Thief:   High DODGE chance. Better chance to escape battles.\n";
    cout << " * Normie:  Starts weak, but has HUGE INVENTORY (Big Pockets).\n";
    cout << "            Can call 'The Boys' for backup (big damage after a delay).\n";

    cout << "\n[ MECHANICS ]\n";
    cout << " * WEIGHT SYSTEM: You cannot carry everything! Stronger weapons are heavy.\n";
    cout << "                  If your bag is full, you must drop items to pick up new ones.\n";
    cout << " * COMBAT:        Turn-based. You go, they go. Use 'Special' wisely (costs MP/Cooldown).\n";
    cout << " * SHOPS:         Spend Gold on Potions and Weapons. Don't be stingy.\n";

    cout << "\n[ PRO TIPS ]\n";
    cout << " 1. Don't hoard potions if you're about to die. DRINK THEM.\n";
    cout << " 2. Different weapons fit different playstyles (e.g., Daggers are light, Hammers are heavy).\n";
    cout << " 3. Pay attention to your MP. No MP = No Special Ability.\n";

    cout << "================================================================\n\n";
    
    wait_for_enter(); 
}

void change_player_class(unique_ptr<Character>& player) {
    
    string currentClass = player->get_class_name();
    
    vector<string> candidates;
    for (const string& className : all_classes) {
        if (className != currentClass) {
            candidates.push_back(className);
        }
    }

    if (candidates.empty()) {
        cout << "Error: No other classes available to switch to.\n";
        return;
    }
    
    int randomIndex = random_int(0, candidates.size() - 1);
    string newClassName = candidates[randomIndex];

    unique_ptr<Character> newPlayer;

    if (newClassName == "Warrior") newPlayer = make_unique<Warrior>(player->get_name());
    else if (newClassName == "Mage") newPlayer = make_unique<Mage>(player->get_name());
    else if (newClassName == "Thief") newPlayer = make_unique<Thief>(player->get_name());
    else if (newClassName == "Archer") newPlayer = make_unique<Archer>(player->get_name());
    else if (newClassName == "Normie") newPlayer = make_unique<Normie>(player->get_name());
    else {
        cout << "Error: Unknown class generated: " << newClassName << ".\n";
        return;
    }

    cout << "\n*** TRANSFORMING INTO " << newClassName << " ***\n";
    newPlayer->transfer_player(*player); 
    player = move(newPlayer);
    
    cout << "Transformation complete! Check your new stats.\n";
    cout << "...\n";
    cout << "..\n";
    cout << "You are still ugly though.\n";
    print_class_details(player->get_class_name());
}

void wait_for_enter() {
    cout << "\n[Press ENTER to continue...]";
    cin.get(); 
}

void print_class_details(const string& className) {
    cout << "\n==================================================\n";
    
    if (className == "Warrior") {
        cout << " [ WARRIOR ] - The Unstoppable Force\n";
        cout << " | Role:       Tank / Crowd Control\n";
        cout << " | Difficulty: Easy\n";
        cout << " | \n";
        cout << " | [STATS]\n";
        cout << " |  > HP:    160 (Highest base HP)\n";
        cout << " |  > MP:    25  (Low)\n";
        cout << " | \n";
        cout << " | [ABILITIES]\n";
        cout << " |  > Active:  BATTLE ROAR (Cost: 10 MP)\n";
        cout << " |             Deals damage (Power/2) and stuns the enemy for 1 turn.\n";
        cout << " |  > Passive: IRON SKIN (Planned)\n";
        cout << " |             (Not implemented yet)\n";
    }
    else if (className == "Mage") {
        cout << " [ MAGE ] - The Glass Cannon\n";
        cout << " | Role:       Magic Damage / Sustain\n";
        cout << " | Difficulty: Hard\n";
        cout << " | \n";
        cout << " | [STATS]\n";
        cout << " |  > HP:    105 (Low)\n";
        cout << " |  > MP:    80  (Highest)\n";
        cout << " | \n";
        cout << " | [ABILITIES]\n";
        cout << " |  > Active:  HEAL (Cost: 20 MP)\n";
        cout << " |             Restores HP equal to Power*2.\n";
        cout << " |  > Passive: MANA REGEN\n";
        cout << " |             Fully restores MP after every battle.\n";
    }
    else if (className == "Archer") {
        cout << " [ ARCHER ] - The Sniper\n";
        cout << " | Role:       Burst Damage\n";
        cout << " | Difficulty: Medium\n";
        cout << " | \n";
        cout << " | [STATS]\n";
        cout << " |  > HP:    115 (Balanced)\n"; 
        cout << " |  > MP:    25  (Low-Mid)\n"; 
        cout << " | \n";
        cout << " | [ABILITIES]\n";
        cout << " |  > Active:  HEADSHOT (Cost: 15 MP)\n";
        cout << " |             Deals damage equal to Power*2.\n";
        cout << " |  > Passive: QUICK DRAW\n";
        cout << " |             Often attacks first (handled in Battle logic).\n";
    }
    else if (className == "Thief") {
        cout << " [ THIEF ] - The Gambler\n";
        cout << " | Role:       Evasion / Utility\n";
        cout << " | Difficulty: Medium\n";
        cout << " | \n";
        cout << " | [STATS]\n";
        cout << " |  > HP:    110 (Low-Mid)\n";
        cout << " |  > MP:    30  (Balanced)\n"; 
        cout << " | \n";
        cout << " | [ABILITIES]\n";
        cout << " |  > Active:  SHADOWFIGHT (Cost: 15 MP)\n";
        cout << " |             Increases dodge chance for the next 2 turns.\n";
        cout << " |  > Passive: ESCAPE ARTIST\n";
        cout << " |             High chance to escape battles (75%).\n";
    }
    else if (className == "Normie") {
        cout << " [ NORMIE ] - The Hoarder\n";
        cout << " | Role:       Resource Management / Late Game\n";
        cout << " | Difficulty: VERY HARD (Early Game)\n";
        cout << " | \n";
        cout << " | [STATS]\n";
        cout << " |  > HP:    90  (Low)\n";  
        cout << " |  > MP:    0   (None)\n";
        cout << " | \n";
        cout << " | [ABILITIES]\n";
        cout << " |  > Active:  CALL THE BOYS\n";
        cout << " |             Backup arrives in 3 turns.\n";
        cout << " |  > Passive: BIG POCKETS\n";
        cout << " |             Inventory capacity increases by +10 every level up.\n";
    }

    cout << "==================================================\n";
}

/// the input protectors:

string get_string(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;  
        if (!getline(cin, line)) {
            cin.clear();
            continue; 
        }
        if (line.empty()) {
            continue; 
        }
        return line;
    }
}

int get_int(const string& prompt) {
    while (true) {
        string input = get_string(prompt);

        try {
            int result = stoi(input);
            return result;
        } 
        catch (const std::invalid_argument&) {
            cout << "Error: That's not a number. Try again.\n";
        }
        catch (const std::out_of_range&) {
            cout << "Error: Number too large (or small). Be reasonable.\n";
        }
    }
}

string lowercase(string& str){
    for (auto& x : str) {
        x = tolower(x);
    }
    return str;
}
