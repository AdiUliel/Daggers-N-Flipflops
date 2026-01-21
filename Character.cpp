#include "Character.h"
#include "Utils.h"

void Character::add_item(Item* item) {
    m_inventory.push_back(item);
    cout << "You obtained: " << item->get_name() << "!\n";
}

void Character::equip(Weapon* newWeapon) {
    if (m_weapon != nullptr) {
        cout << "You put " << m_weapon->get_name() << " back in your bag.\n";
        m_inventory.push_back(m_weapon); 
    }
    
    m_weapon = newWeapon;
}

void Character::open_inventory() {
    if (m_inventory.empty()) {
        cout << "Your bag is empty. Just lint and sadness.\n";
        return;
    }

    bool browsing = true;
    while (browsing) {
        cout << "\n--- INVENTORY ---\n";
        cout << "1. Wearables (Weapons)\n";
        cout << "2. Usables (Potions)\n";
        cout << "3. Close Bag\n";
        
        int choice = get_int("> ");

        if (choice == 3) {
            browsing = false;
            break;
        }
        
        string filterType = "";
        if (choice == 1) filterType = "Wearable";
        else if (choice == 2) filterType = "Usable";
        else {
            cout << "Invalid choice.\n";
            continue;
        }

        vector<int> realIndices; 
        int displayIndex = 1;

        cout << "\n--- " << filterType << "s ---\n";
        
        for (size_t i = 0; i < m_inventory.size(); i++) {
            if (m_inventory[i]->get_type() == filterType) {
                cout << displayIndex << ". " << m_inventory[i]->get_name() 
                     << " (" << m_inventory[i]->get_tier() << ")\n";
                
                realIndices.push_back(i);
                displayIndex++;
            }
        }

        if (realIndices.empty()) {
            cout << "No " << filterType << "s found.\n";
            continue;
        }

        cout << "0. Back\n";
        int itemChoice = get_int("Choose item to use: ");

        if (itemChoice == 0) continue;

        if (itemChoice > 0 && itemChoice <= (int)realIndices.size()) {
            int realIndex = realIndices[itemChoice - 1];
            Item* itemToUse = m_inventory[realIndex];


            bool destroy = itemToUse->use(this);

            m_inventory.erase(m_inventory.begin() + realIndex);

            if (destroy) {
                delete itemToUse; 
            }
            
            cout << "Done.\n";
        } else {
            cout << "Invalid item selection.\n";
        }
    }
}