#ifndef SHOP_H
#define SHOP_H

#include "Encounter.h"
#include "Utils.h"
#include "Character.h"
#include "HealthPotion.hpp"
#include "ManaPotion.hpp"

#include "Sword.hpp"
#include "Hammer.hpp"
#include "Bow.hpp"
#include "Crossbow.hpp"
#include "Staff.hpp"
#include "Wand.hpp"
#include "Dagger.hpp"
#include "ThrowingStars.hpp"
#include "FryingPan.hpp"
#include "Marbles.hpp"
#include "Flipflops.hpp"

#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::unique_ptr;
using std::vector;

class Shop : public Encounter {
private:
    unique_ptr<Item> create_weapon_by_id(int id) {
        switch (id) {
            case 0: return unique_ptr<Item>(new Sword());
            case 1: return unique_ptr<Item>(new Hammer());
            case 2: return unique_ptr<Item>(new Bow());
            case 3: return unique_ptr<Item>(new Crossbow());
            case 4: return unique_ptr<Item>(new Staff());
            case 5: return unique_ptr<Item>(new Wand());
            case 6: return unique_ptr<Item>(new Dagger());
            case 7: return unique_ptr<Item>(new ThrowingStars());
            case 8: return unique_ptr<Item>(new FryingPan());
            case 9: return unique_ptr<Item>(new Marbles());
            case 10: return unique_ptr<Item>(new Flipflops());
            default: return unique_ptr<Item>(new Sword());
        }
    }

public:
    void run(unique_ptr<Character>& player) override {
        cout << "\n--- WANDERING MERCHANT ---\n";
        cout << "Merchant: 'Oh, look who survived.' (Coins: " << player->get_coins() << ")\n";

        vector<int> weaponIds;
        while (weaponIds.size() < 3) {
            int r = random_int(0, 10);
            bool exists = false;
            for (int id : weaponIds) if (id == r) exists = true;
            if (!exists) weaponIds.push_back(r);
        }

        vector<unique_ptr<Item>> shopItems;
        for (int id : weaponIds) {
            shopItems.push_back(create_weapon_by_id(id));
        }

        cout << "1. Health Potion (Heal 50) - 20 Coins\n";
        cout << "2. Mana Potion (Restore 40) - 30 Coins\n";
        
        for (size_t i = 0; i < shopItems.size(); i++) {
            cout << (i + 3) << ". " << shopItems[i]->get_name() 
                 << " (" << shopItems[i]->get_tier() << ") - " 
                 << shopItems[i]->get_price() << " Coins\n";
        }
        
        cout << "6. Leave\n";

        int choice = get_int("> ");

        if (choice == 1) { 
            if (player->get_coins() >= 20) {
                player->new_coins(-20);
                player->add_item(unique_ptr<Item>(new Potion(50)));
                cout << "Merchant: 'Try not to choke on it.'\n";
            } else {
                cout << "Merchant: 'No gold? Then bleed somewhere else.'\n";
            }
        }
        else if (choice == 2) { 
            if (player->get_coins() >= 30) {
                player->new_coins(-30);
                player->add_item(unique_ptr<Item>(new ManaPotion(40)));
                cout << "Merchant: 'Magic in a bottle. Don't ask how it's made.'\n";
            } else {
                cout << "Merchant: 'Knowledge isn't free, and neither is mana.'\n";
            }
        }
        else if (choice >= 3 && choice <= 5) { 
            int index = choice - 3;
            Item* selectedItem = shopItems[index].get();
            int cost = selectedItem->get_price();

            if (player->get_coins() >= cost) {
                player->new_coins(-cost);
                int originalId = weaponIds[index];
                player->add_item(create_weapon_by_id(originalId));
                cout << "Merchant: 'Good choice. Pointy end goes into the enemy.'\n";
            } else {
                cout << "Merchant: 'Come back when you're rich.'\n";
            }
        }
        else if (choice == 6) {
            cout << "You leave. The merchant counts his money and ignores you.\n";
        }
        else {
            cout << "Merchant: 'Stop wasting my time.'\n";
        }
    }
};

#endif