#include "Character.h"
#include "Utils.h"
#include <memory>

void Character::add_item(unique_ptr<Item> item) {
    cout << "You obtained: " << item->get_name() << "!\n";
    m_inventory.push_back(std::move(item));
}

void Character::equip(unique_ptr<Weapon> newWeapon) {
    if (m_weapon != nullptr) {
        cout << "You put " << m_weapon->get_name() << " back in your bag.\n";
        m_inventory.push_back(std::move(m_weapon));
    }
    m_weapon = std::move(newWeapon);
    cout << "Equipped " << m_weapon->get_name() << ".\n";

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
            Item* rawItem = m_inventory[realIndex].get();
            Weapon* weaponPtr = dynamic_cast<Weapon*>(rawItem);

            if (weaponPtr != nullptr) {
                unique_ptr<Item> itemMoved = std::move(m_inventory[realIndex]);
                unique_ptr<Weapon> weaponUnique(static_cast<Weapon*>(itemMoved.release()));
                equip(std::move(weaponUnique));
                m_inventory.erase(m_inventory.begin() + realIndex);
            }
            else {
                bool destroy = rawItem->use(this);
                if (destroy) {
                    m_inventory.erase(m_inventory.begin() + realIndex);
                }
            }
            cout << "Done.\n";
        } else {
            cout << "Invalid item selection.\n";
        }
    }
}