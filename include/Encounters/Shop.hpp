#ifndef SHOP_HPP
#define SHOP_HPP

#include "Encounter.h"
#include "Utils.h"
#include "Character.h"
#include "HealthPotion.hpp"
#include "ManaPotion.hpp"
#include <memory>
#include <vector>

// Weapons Includes
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

using std::cout;
using std::unique_ptr;
using std::vector;

class Shop : public Encounter {
private:
    unique_ptr<Item> create_weapon_by_id(int id) {
        switch (id) {
            case 0: return std::make_unique<Sword>();
            case 1: return std::make_unique<Hammer>();
            case 2: return std::make_unique<Bow>();
            case 3: return std::make_unique<Crossbow>();
            case 4: return std::make_unique<Staff>();
            case 5: return std::make_unique<Wand>();
            case 6: return std::make_unique<Dagger>();
            case 7: return std::make_unique<ThrowingStars>();
            case 8: return std::make_unique<FryingPan>();
            case 9: return std::make_unique<Marbles>();
            case 10: return std::make_unique<Flipflops>();
            default: return std::make_unique<Sword>();
        }
    }

public:
    void run(unique_ptr<Character>& player) override {
        cout << "\n--- WANDERING MERCHANT ---\n";
        cout << "Merchant: 'Oh, look who survived.'\n";

        vector<int> weaponIds;
        while (weaponIds.size() < 3) {
            int r = random_int(0, 10);
            bool exists = false;
            for (int id : weaponIds) if (id == r) exists = true;
            if (!exists) weaponIds.push_back(r);
        }

        bool isShopping = true;
        while (isShopping) {
            cout << "\n----------------------------------\n";
            cout << "YOUR GOLD: " << player->get_coins() << "\n";
            cout << "----------------------------------\n";

            vector<unique_ptr<Item>> displayWeapons;
            for (int id : weaponIds) {
                displayWeapons.push_back(create_weapon_by_id(id));
            }

            cout << "1. Health Potion (Heal 50) - 20 Coins\n";
            cout << "2. Mana Potion (Restore 40) - 30 Coins\n";
            
            for (size_t i = 0; i < displayWeapons.size(); i++) {
                cout << (i + 3) << ". " << displayWeapons[i]->get_name() 
                     << " (" << displayWeapons[i]->get_tier() << ") - " 
                     << displayWeapons[i]->get_price() << " Coins [Weight: " << displayWeapons[i]->get_weight() << "]\n";
            }
            
            cout << "6. Leave\n";

            int choice = get_int("> ");

            if (choice == 1) { 
                int cost = 20;
                if (player->get_coins() >= cost) {
                    unique_ptr<Item> potion = std::make_unique<HealthPotion>(50);
                    if (player->pick_up_item(std::move(potion))) {
                        player->new_coins(-cost);
                        cout << "Merchant: 'Good. Anything else?'\n";
                    } else {
                        cout << "Merchant: 'Your bag is full.'\n";
                    }
                } else {
                    cout << "Merchant: 'No gold? Then bleed somewhere else.'\n";
                }
            }
            else if (choice == 2) { 
                int cost = 30;
                if (player->get_coins() >= cost) {
                    unique_ptr<Item> potion = std::make_unique<ManaPotion>(40);
                    if (player->pick_up_item(std::move(potion))) {
                        player->new_coins(-cost);
                        cout << "Merchant: 'Another one? Sure.'\n";
                    } else {
                        cout << "Merchant: 'Make space first.'\n";
                    }
                } else {
                    cout << "Merchant: 'Mana isn't free.'\n";
                }
            }
            else if (choice >= 3 && choice <= 5) { 
                int index = choice - 3;
                int cost = displayWeapons[index]->get_price();

                if (player->get_coins() >= cost) {
                    unique_ptr<Item> newWeapon = create_weapon_by_id(weaponIds[index]);

                    if (player->pick_up_item(std::move(newWeapon))) {
                        player->new_coins(-cost);
                        cout << "Merchant: 'Solid choice. Want to buy another?'\n";
                    } else {
                        cout << "Merchant: 'You can't carry that.'\n";
                    }
                } else {
                    cout << "Merchant: 'Come back when you're rich.'\n";
                }
            }
            else if (choice == 6) {
                cout << "You leave the shop.\n";
                isShopping = false;
            }
            else {
                cout << "Merchant: 'Stop wasting my time.'\n";
            }

            if (isShopping) {
                wait_for_enter();
            }
        }

        cout << "\n--- Encounter finished ---\n";
    }
};

#endif