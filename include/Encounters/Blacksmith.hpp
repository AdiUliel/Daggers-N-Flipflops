#ifndef BLACKSMITH_HPP
#define BLACKSMITH_HPP

#include "Encounter.h"
#include "Crafting.h"
#include "Utils.h"
#include <iostream>
#include <algorithm> 

using std::cout;
using std::endl;

class Blacksmith : public Encounter {
public:
    void run(unique_ptr<Character>& player) override {
        cout << "\n--- THE BLACKSMITH'S FORGE ---\n";
        cout << "The anvil is hot. 'Bring me metal!'\n";
        
        int totalItems = player->get_inventory_size();
        if (player->get_equipped_weapon() != nullptr) {
            totalItems++;
        }

        if (totalItems < 2) {
            cout << "Blacksmith: 'You don't have enough items. Come back when you're loaded.'\n";
            wait_for_enter();
            cout << "\n--- Encounter finished ---\n";
            return;
        }

        bool crafting = true;
        while (crafting) {
            cout << "\n[ FORGE MENU ]\n";
            
            if (player->get_equipped_weapon() != nullptr) {
                cout << "0. [EQUIPPED] " << player->get_equipped_weapon()->get_name() 
                     << " (Damage: " << player->get_power() << ")\n";
            } else {
                cout << "0. [EQUIPPED] (Bare Hands - Cannot craft)\n";
            }

            cout << "--- INVENTORY ---\n";
            for (int i = 0; i < player->get_inventory_size(); i++) {
                Item* item = player->get_item_at(i);
                cout << (i + 1) << ". " << item->get_name() << "\n";
            }
            
            cout << "\nType -1 to Leave.\n";
            
            int choice1 = get_int("Select FIRST item ID: ");
            if (choice1 == -1) { crafting = false; break; }

            int choice2 = get_int("Select SECOND item ID: ");
            if (choice2 == -1) { crafting = false; break; }

            if (choice1 == choice2) {
                cout << "Blacksmith: 'You need TWO different items, genius.'\n";
                continue;
            }

            Item* item1 = nullptr;
            Item* item2 = nullptr;

            if (choice1 == 0) {
                item1 = player->get_equipped_weapon();
                if (!item1) { cout << "Invalid selection (No weapon equipped).\n"; continue; }
            } else {
                item1 = player->get_item_at(choice1 - 1);
            }

            if (choice2 == 0) {
                item2 = player->get_equipped_weapon();
                if (!item2) { cout << "Invalid selection (No weapon equipped).\n"; continue; }
            } else {
                item2 = player->get_item_at(choice2 - 1);
            }

            if (item1 == nullptr || item2 == nullptr) {
                cout << "Blacksmith: 'Invalid ID selected.'\n";
                continue;
            }

            cout << "Combining " << item1->get_name() << " + " << item2->get_name() << "...\n";
            unique_ptr<Item> result = Crafting::try_craft(item1, item2);

            if (result != nullptr) {
                cout << "SUCCESS! Created: " << result->get_name() << "\n";
                cout << "Desc: " << result->get_description() << "\n";

                player->add_item(std::move(result));

                
                if (choice1 > 0 && choice2 > 0) {
                    int idx1 = choice1 - 1;
                    int idx2 = choice2 - 1;
                    player->remove_item(std::max(idx1, idx2));
                    player->remove_item(std::min(idx1, idx2));
                }
                else if (choice1 == 0 || choice2 == 0) {
                    player->destroy_equipped(); 
                    
                    int inventoryIdx = (choice1 == 0) ? (choice2 - 1) : (choice1 - 1);
                    player->remove_item(inventoryIdx);
                    
                    cout << "(Your equipped weapon was consumed. You are now unarmed.)\n";
                }

            } else {
                cout << "FAILURE! Incompatible items.\n";
            }
            
            wait_for_enter();
        }

        cout << "\n--- Encounter finished ---\n";
    }
};

#endif