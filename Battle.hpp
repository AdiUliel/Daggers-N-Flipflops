#ifndef BATTLE_H
#define BATTLE_H

#include "Encounter.h"
#include "Enemy.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::string;

class Battle : public Encounter {
private:
    int m_floor;

public:
    Battle(int floor) : m_floor(floor) {}

    void run(Character* player) override {
        Enemy::MobType type = static_cast<Enemy::MobType>(random_int(0, 2));
        Enemy* enemy = new Enemy(m_floor, type);
        
        cout << "A " << enemy->get_type_name() << " appears! Do try to make this entertaining.\n";

        bool battleOver = false;
        while (!battleOver) {
            cout << "\n[ " << player->get_name() << " HP: " << player->get_HP() << " ] vs [ " << enemy->get_type_name() << " HP: " << enemy->get_HP() << " ]\n";
            
            string attackName = "Flail wildly (Attack)";
            if (player->get_weapon() != nullptr) {
                attackName = player->get_weapon()->get_action_name(player);
            }

            cout << "1. " << attackName << "  2. Cry for help (Heal 20 MP)\n";
            
            int choice = get_int("> ");


            if (choice == 1) {
                if (player->get_weapon() != nullptr) {
                    player->get_weapon()->attack_action(player, enemy);
                } 
                else {
                    int dmg = random_int(player->get_power(), player->get_power() + 5);
                    cout << "You hit with your bare hands for " << dmg << " damage.\n";
                    enemy->damage(dmg);
                }
            } 
            else if (choice == 2) {
                if (player->get_MP() >= 20) {
                    player->set_MP(player->get_MP() - 20);
                    player->heal(30);
                    cout << "Healed. Pathetic.\n";
                } else {
                    cout << "Not enough MP. Fail.\n";
                }
            } 
            else {
                cout << "You just stand there in confusion. (Turn wasted)\n";
            }

            if (enemy->isKnockedOut()) {
                cout << "Target destroyed. You gained loot.\n";
                player->gain_exp(enemy->get_xp_reward());
                player->new_coins(enemy->get_gold_reward());
                battleOver = true;
            } else {
                int dmg = enemy->attack();
                cout << "Enemy hits you for " << dmg << ".\n";
                player->damage(dmg);
                
                if (player->isKnockedOut()) {
                    battleOver = true;
                }
            }
        }
        delete enemy;
    }
};

#endif