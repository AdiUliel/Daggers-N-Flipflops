#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Encounter.h"
#include "Enemy.h"
#include "Utils.h"
#include <iostream>
#include <memory>

using std::cout;
using std::string;
using std::unique_ptr;

/**
 * @class Battle
 * @brief Handles turn-based combat logic.
 * * Creates a random enemy based on the current floor.
 * * Manages the initiative (who attacks first).
 * * Runs the loop: Player Action -> Enemy Action -> Repeat until death or flee.
 * * Handles special class interactions (Archer's speed, Normie's backup).
 */
class Battle : public Encounter {
private:
    int m_floor;

public:
    Battle(int floor) : m_floor(floor) {}

    void run(unique_ptr<Character>& player) override {
        // Initialize Enemy
        Enemy::MobType type = static_cast<Enemy::MobType>(random_int(0, 2));
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(m_floor, type);
        
        cout << "A " << enemy->get_type_name() << " appears! Do try to make this entertaining.\n";

        bool battleOver = false;
        
        // Determine Initiative
        bool playerTurn = true;
        
        cout << "\n--- BATTLE START ---\n";
        
        if (player->get_class_name() != "Archer") {
             if (random_int(0, 1) == 0) playerTurn = false;
        } else {
             cout << "[Passive] Archer Quick Draw active! You shoot first.\n";
        }

        if (playerTurn) cout << ">> " << player->get_name() << " goes first!\n";
        else cout << ">> " << enemy->get_type_name() << " attacks first!\n";
        
        wait_for_enter(); 

        // Main Battle Loop
        while (!battleOver) {
            
            if (playerTurn) {
                player->tick_turn(); 

                // Normie Logic
                if (player->get_backup_timer() > 0) {
                    player->decrease_backup_timer();
                    
                    if (player->get_backup_timer() == 0) {
                        cout << "\n*** THE BOYS HAVE ARRIVED! ***\n";
                        cout << "A van pulls up and beats the enemy!\n";
                        enemy->damage(player->get_power() * 10);
                        player->reset_backup_timer();

                        if (enemy->isKnockedOut()) {
                            cout << "Target destroyed by the boys.\n";
                            player->gain_exp(enemy->get_xp_reward());
                            player->new_coins(enemy->get_gold_reward());
                            battleOver = true;
                            wait_for_enter();
                            break; 
                        }
                    } else {
                        cout << "(Backup arriving in " << player->get_backup_timer() << " turns...)\n";
                    }
                }

                // not yet needed - MP changes for enemy
                cout << "\n[ " << player->get_name() << " | HP: " << player->get_HP() << " MP: " << player->get_MP() << " ]"
                     << " VS "
                     << "[ " << enemy->get_type_name() << " | HP: " << enemy->get_HP() << " MP: " << enemy->get_MP() << " ]\n";
                // -------------------------------------
                
                string attackName = "Flail wildly (Attack)";
                if (player->get_weapon() != nullptr) {
                    attackName = player->get_weapon()->get_action_name(player.get());
                }

                cout << "1. " << attackName << "\n";
                cout << "2. Special Ability\n";
                cout << "3. Defend\n";
                cout << "4. Run\n";
                
                int choice = get_int("> ");

                if (choice == 1) {
                    if (player->get_weapon() != nullptr) {
                        player->get_weapon()->attack_action(player.get(), enemy.get());
                    } 
                    else {
                        int dmg = random_int(player->get_power(), player->get_power() + 5);
                        cout << "You hit with your bare hands for " << dmg << " damage.\n";
                        enemy->damage(dmg);
                    }
                } 
                else if (choice == 2) {
                    player->use_special_ability(enemy.get());
                } 
                else if (choice == 3) {
                    player->defend();
                }
                else if (choice == 4) {
                    if (player->try_run()) {
                        cout << "You escaped successfully!\n";
                        battleOver = true;
                        cout << "\n--- Encounter finished ---\n";
                        return;
                    } else {
                        cout << "Failed to escape!\n";
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
                }
                
                if (!battleOver) wait_for_enter();

            } else {
                // Enemy's turn
                if (enemy->is_stunned()) {
                    cout << "Enemy is STUNNED and cannot move this turn!\n";
                    enemy->apply_stun(0); 
                } else {
                    int dmg = enemy->attack();
                    cout << "Enemy hits you for " << dmg << ".\n";
                    player->take_damage(dmg); 
                    
                    if (player->isKnockedOut()) {
                        battleOver = true;
                    }
                }
                
                if (!battleOver) wait_for_enter();
            }

            playerTurn = !playerTurn;
        }
        
        player->apply_passive_end_battle();
        cout << "\n--- Encounter finished ---\n";
    }
};

#endif