#include "Character.h"
#include "Utils.h"
#include <memory>

int Character::get_current_load() const {
    int totalWeight = 0;
    for (const auto& item : m_inventory) {
        totalWeight += item->get_weight();
    }
    return totalWeight;
}

bool Character::pick_up_item(std::unique_ptr<Item> newItem) {
    int newWeight = newItem->get_weight();

    while (true) {
        int currentLoad = get_current_load();
        int freeSpace = m_bagCapacity - currentLoad;

        if (newWeight <= freeSpace) {
            cout << "You picked up " << newItem->get_name() << " (" << newWeight << "kg).\n";
            m_inventory.push_back(std::move(newItem));
            return true;
        }
        
        // if bag is full
        cout << "\n!!! INVENTORY FULL !!!\n";
        cout << "Capacity: " << currentLoad << " / " << m_bagCapacity << " kg.\n";
        cout << "Found: " << newItem->get_name() << " (Weight: " << newWeight << " kg)\n";
        cout << "You need " << (newWeight - freeSpace) << " kg more space.\n";
        
        cout << "1. Discard new item (" << newItem->get_name() << ")\n";
        cout << "2. Throw away something from bag\n";
        
        int choice = get_int("> ");

        if (choice == 1) {
            cout << "You left the " << newItem->get_name() << " on the ground.\n";
            return false;
        }
        else if (choice == 2) {
            cout << "\n--- THROW AWAY WHAT? ---\n";
            for (size_t i = 0; i < m_inventory.size(); i++) {
                cout << (i + 1) << ". " << m_inventory[i]->get_name() 
                     << " (" << m_inventory[i]->get_weight() << "kg)\n";
            }
            cout << "0. Cancel\n";
            
            int tossIndex = get_int("Choose item to drop: ");
            if (tossIndex > 0 && tossIndex <= (int)m_inventory.size()) {
                cout << "Threw away " << m_inventory[tossIndex - 1]->get_name() << ".\n";
                m_inventory.erase(m_inventory.begin() + (tossIndex - 1));
            }
        }
    }
}

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

void Character::unequip() {
    if (m_weapon == nullptr) {
        cout << "You are already using your Bare Hands.\n";
        return;
    }

    int weaponWeight = m_weapon->get_weight();
    int currentLoad = get_current_load();
    int freeSpace = m_bagCapacity - currentLoad;

    if (weaponWeight > freeSpace) {
        cout << "You try to put away " << m_weapon->get_name() << "...\n";
        cout << "But your bag is too full! (Needs " << weaponWeight << "kg, Free: " << freeSpace << "kg)\n";
        return;
    }

    cout << "You strapped " << m_weapon->get_name() << " to your back.\n";
    m_inventory.push_back(std::move(m_weapon));
    
    m_weapon = nullptr; 
    cout << "You are now fighting with Bare Hands.\n";
}

void Character::take_damage(int amount) {
    // Dodge check - Thief
    if (m_dodgeDuration > 0 && random_int(1, 100) <= 50) {
        cout << m_name << " dodged the attack from the shadows!\n";
        return;
    }

    if (m_isDefending) {
        amount /= 2;
        cout << "Defensive stance reduced damage!\n";
    }

    m_currentHP -= amount;
    if (m_currentHP < 0) m_currentHP = 0;
    cout << m_name << " took " << amount << " damage!\n";
}

bool Character::try_run() {
    return random_int(1, 100) <= 50;
}

void Character::open_inventory() {
    if (m_inventory.empty()) {
        cout << "Your bag is empty. Just lint and sadness.\n";
        return;
    }

    bool browsing = true;
    while (browsing) {
        if (m_weapon != nullptr) {
            cout << "[Equipped: " << m_weapon->get_name() << "]\n";
        } else {
            cout << "[Equipped: Bare Hands]\n";
        }
        cout << "1. Wearables (Weapons)\n";
        cout << "2. Usables (Potions)\n";
        cout << "3. Unequip Weapon (Switch to Bare Hands)\n";
        cout << "4. Close Bag\n";
        int choice = get_int("> ");

        if (choice == 4) {
            browsing = false;
            break;
        }
        else if (choice == 3) {
            unequip();
            continue;
        }
        
        string filterType = "";
        if (choice == 1) filterType = "Wearable";
        else if (choice == 2) filterType = "Consumable";
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